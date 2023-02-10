#define _GNU_SOURCE
#include "rt-lib.h"
#include "parameters.h"

static float wcet_filter = 0;
static float wcet_control = 0;
static float wcet_actuator = 0;
static float U_filter = 0;
static float U_control = 0;
static float U_actuator = 0;

static int keep_on_running = 1;
static int start = 0;
static unsigned int reference = 110;

static struct shared_int shared_avg_sensor;
static struct shared_int shared_control;

pthread_mutex_t buffer_lock;
pthread_mutexattr_t mutex_attr;

int buffer[BUF_SIZE];
int head = 0;

void *acquire_filter_loop(void *par)
{
	/*int ret;
	ret = pthread_setaffinity_np(pthread_self(), sizeof(cpu), &cpu);
	if (ret != 0)
	{
		perror(" Cannot set backup filter thread CPU affinity ");
		exit(-1);
	}*/
	struct timespec start_time, end_time;
	float tempWCET = 0;

	// periodic_thread *th = (periodic_thread *)par;
	// start_periodic_timer(th, TICK_TIME);

	// Messaggio da prelevare dal driver
	char message[MAX_MSG_SIZE];

	/* Coda */
	struct mq_attr attr;

	attr.mq_flags = 0;
	attr.mq_maxmsg = MAX_MESSAGES;
	attr.mq_msgsize = MAX_MSG_SIZE;
	attr.mq_curmsgs = 0;

	// Apriamo la coda sensor del plant in lettura
	mqd_t sensor_qd;
	if ((sensor_qd = mq_open(SENSOR_QUEUE_NAME, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1)
	{
		perror("acquire filter loop: mq_open (sensor)");
		exit(-1);
	}
	unsigned int sum = 0;
	int cnt = BUF_SIZE;
	while (keep_on_running)
	{
		// wait_next_activation(th);

		if (start)
		{
			clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start_time);

			// PRELIEVO DATI dalla coda del PLANT
			if (mq_receive(sensor_qd, message, MAX_MSG_SIZE, NULL) == -1)
			{
				perror("acquire filter loop: mq_receive (actuator)");
				break; // DEBUG
			}
			else
			{
				pthread_mutex_lock(&buffer_lock);
				buffer[head] = atoi(message);
				sum += buffer[head];
				pthread_mutex_unlock(&buffer_lock);
				head = (head + 1) % BUF_SIZE;
				cnt--;

				// printf("\t\t\t\tbuffer[%d]=%d, sum=%d\n",head,buffer[head],sum); //DEBUG

				// calcolo media sulle ultime BUF_SIZE letture
				if (cnt == 0)
				{
					cnt = BUF_SIZE;
					pthread_mutex_lock(&shared_avg_sensor.lock);
					shared_avg_sensor.value = sum / BUF_SIZE;
					// printf("\t\t\t\tavg_sensor.value=%d\n",shared_avg_sensor.value); //DEBUG
					pthread_mutex_unlock(&shared_avg_sensor.lock);
					sum = 0;
				}
			}
			clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end_time);

			tempWCET = (float)(difference_ns(&end_time, &start_time) / 1000);
			if (tempWCET > wcet_filter)
			{
				wcet_filter = tempWCET;
				U_filter = wcet_filter / TICK_TIME;
			}
		}
	}

	/* Clear */
	if (mq_close(sensor_qd) == -1)
	{
		perror("acquire filter loop: mq_close sehsor_qd");
		exit(-1);
	}

	pthread_exit(NULL);
}

void *control_loop(void *par)
{
	/*int ret;
	ret = pthread_setaffinity_np(pthread_self(), sizeof(cpu), &cpu);
	if (ret != 0)
	{
		perror(" Cannot set backup control thread CPU affinity ");
		exit(-1);
	}*/
	struct timespec start_time, end_time;
	float tempWCET = 0;

	periodic_thread *th = (periodic_thread *)par;
	start_periodic_timer(th, TICK_TIME);

	// Messaggio da prelevare dal reference
	char message[MAX_MSG_SIZE];

	/* Coda */
	struct mq_attr attr;

	attr.mq_flags = 0;
	attr.mq_maxmsg = MAX_MESSAGES;
	attr.mq_msgsize = MAX_MSG_SIZE;
	attr.mq_curmsgs = 0;

	// Apriamo la coda per il reference, in lettura e non bloccante
	mqd_t reference_qd;
	if ((reference_qd = mq_open(REFERENCE_QUEUE_NAME, O_RDONLY | O_CREAT | O_NONBLOCK, QUEUE_PERMISSIONS, &attr)) == -1)
	{
		perror("control loop: mq_open (reference)");
		exit(-1);
	}

	unsigned int plant_state = 0;
	int error = 0;
	unsigned int control_action = 0;

	while (keep_on_running)
	{
		wait_next_activation(th);

		if (start)
		{
			clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start_time);

			// legge il plant state
			pthread_mutex_lock(&shared_avg_sensor.lock);
			plant_state = shared_avg_sensor.value;
			pthread_mutex_unlock(&shared_avg_sensor.lock);

			// riceve la reference (in modo non bloccante)
			if (mq_receive(reference_qd, message, MAX_MSG_SIZE, NULL) == -1)
			{
				// printf ("No reference ...\n");							//DEBUG
			}
			else
			{
				// printf ("Reference received: %s.\n",message);			//DEBUG
				reference = atoi(message);
			}

			// calcolo della legge di controllo
			error = reference - plant_state;

			if (error > 0)
				control_action = 1;
			else if (error < 0)
				control_action = 2;
			else
				control_action = 3;

			// aggiorna la control action
			pthread_mutex_lock(&shared_control.lock);
			shared_control.value = control_action;
			pthread_mutex_unlock(&shared_control.lock);

			clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end_time);
			tempWCET = (float)(difference_ns(&end_time, &start_time) / 1000);
			if (tempWCET > wcet_control)
			{
				wcet_control = tempWCET;
				U_control = wcet_control / TICK_TIME * BUF_SIZE;
			}
		}
	}
	/* Clear */
	if (mq_close(reference_qd) == -1)
	{
		perror("control loop: mq_close reference_qd");
		exit(-1);
	}
	pthread_exit(NULL);
}

void *actuator_loop(void *par)
{
	/*int ret;
	ret = pthread_setaffinity_np(pthread_self(), sizeof(cpu), &cpu);
	if (ret != 0)
	{
		perror(" Cannot set backup actuator thread CPU affinity ");
		exit(-1);
	}*/
	struct timespec start_time, end_time;
	float tempWCET = 0;

	periodic_thread *th = (periodic_thread *)par;
	start_periodic_timer(th, TICK_TIME);

	// Messaggio da prelevare dal driver
	char message[MAX_MSG_SIZE];

	/* Coda */
	struct mq_attr attr;

	attr.mq_flags = 0;
	attr.mq_maxmsg = MAX_MESSAGES;
	attr.mq_msgsize = MAX_MSG_SIZE;
	attr.mq_curmsgs = 0;

	// Apriamo la coda actuator del plant in scrittura
	mqd_t actuator_qd;
	if ((actuator_qd = mq_open(ACTUATOR_QUEUE_NAME, O_WRONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1)
	{
		perror("actuator  loop: mq_open (actuator)");
		exit(-1);
	}

	unsigned int control_action = 0;
	unsigned int control = 0;
	while (keep_on_running)
	{
		wait_next_activation(th);

		if (start)
		{
			clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start_time);

			// prelievo della control action
			pthread_mutex_lock(&shared_control.lock);
			control_action = shared_control.value;
			pthread_mutex_unlock(&shared_control.lock);

			switch (control_action)
			{
			case 1:
				control = 1;
				break;
			case 2:
				control = -1;
				break;
			case 3:
				control = 0;
				break;
			default:
				control = 0;
			}
			printf("Control: %d\n", control); // DEBUG
			sprintf(message, "%d", control);
			// invio del controllo al driver del plant
			if (mq_send(actuator_qd, message, strlen(message) + 1, 0) == -1)
			{
				perror("Sensor driver: Not able to send message to controller");
				continue;
			}

			clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end_time);
			tempWCET = (float)(difference_ns(&end_time, &start_time) / 1000);
			if (tempWCET > wcet_actuator)
			{
				wcet_actuator = tempWCET;
				U_actuator = wcet_actuator / TICK_TIME * BUF_SIZE;
			}
		}
	}
	/* Clear */
	if (mq_close(actuator_qd) == -1)
	{
		perror("Actuator loop: mq_close actuator_qd");
		exit(-1);
	}
	pthread_exit(NULL);
}

void *watchdog(void *par)
{
	/*int ret;
	ret = pthread_setaffinity_np(pthread_self(), sizeof(cpu), &cpu);
	if (ret != 0)
	{
		perror(" Cannot set watchdog thread CPU affinity ");
		exit(-1);
	}*/
	periodic_thread *th = (periodic_thread *)par;
	start_periodic_timer(th, TICK_TIME);

	struct timespec tempTime;
	char message[MAX_MSG_SIZE];
	char ref_msg[MAX_MSG_SIZE];

	struct mq_attr attr;
	attr.mq_flags = 0;
	attr.mq_maxmsg = MAX_MESSAGES;
	attr.mq_msgsize = MAX_MSG_SIZE;
	attr.mq_curmsgs = 0;

	mqd_t wd_qd;
	if ((wd_qd = mq_open(WATCHDOG_QUEUE_NAME, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1)
	{
		perror("watchdog loop: mq_open (wd_qd)");
		exit(-1);
	}
	// coda per comunicare con il controller e mandare l'ultimo valore di reference
	// in modo che il controller continua l'esecuzione, quando si riattiva
	mqd_t previous_reference;
	if ((previous_reference = mq_open(PREVIUOS_QUEUE_NAME, O_WRONLY | O_CREAT | O_NONBLOCK, QUEUE_PERMISSIONS, &attr)) == -1)
	{
		perror("watchdog loop: mq_open (previous_reference)");
		exit(-1);
	}

	int flag = 1;

	while (keep_on_running)
	{
		wait_next_activation(th);

		clock_gettime(CLOCK_MONOTONIC, &tempTime);

		timespec_add_us(&tempTime, 2 * TICK_TIME * BUF_SIZE);

		if (mq_timedreceive(wd_qd, message, MAX_MSG_SIZE, NULL, &tempTime) == -1)
		{
			// printf("ACTIVE\n");
			start = 1;
			flag = 1;
		}
		else
		{
			printf("NOT ACTIVE\n");
			start = 0;
			// questo flag serve per mandare il valore di reference sulla coda un'unica volta
			if (flag)
			{
				sprintf(ref_msg, "%d", reference);

				if (mq_send(previous_reference, ref_msg, strlen(ref_msg) + 1, 0) == -1)
				{
					perror("Watchdog: Not able to send reference to controller");
					exit(-1);
				}
				flag = 0;
			}
			reference = atoi(message);
		}
	}

	/* Clear */
	if (mq_close(wd_qd) == -1)
	{
		perror("Watchdog loop: mq_close wd_qd");
		exit(-1);
	}
	if (mq_close(previous_reference) == -1)
	{
		perror("Watchdog loop: mq_close previous_reference");
		exit(-1);
	}
	pthread_exit(NULL);
}

void *ds_loop(void *par)
{
	/*int ret;
	ret = pthread_setaffinity_np(pthread_self(), sizeof(cpu), &cpu);
	if (ret != 0)
	{
		perror(" Cannot set backup DS thread CPU affinity ");
		exit(-1);
	}*/
	periodic_thread *th = (periodic_thread *)par;
	start_periodic_timer(th, 0);

	char req_message[MAX_MSG_SIZE * 20];
	char res_message[MAX_MSG_SIZE * 20];

	int tempAVGSensor = 0, tempControl = 0, tempBuffer[5], tempReference = 0;
	float tempU = 0;

	struct timespec tempTime;

	struct mq_attr attr;
	attr.mq_flags = 0;
	attr.mq_maxmsg = MAX_MESSAGES;
	attr.mq_msgsize = MAX_MSG_SIZE * 20;
	attr.mq_curmsgs = 0;

	mqd_t req_ds;
	mqd_t res_ds;

	if ((req_ds = mq_open(DSREQUEST_QUEUE_NAME, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1)
	{
		perror("ds loop: mq_open (req_ds)");
		exit(-1);
	}

	if ((res_ds = mq_open(DSRESPONSE_QUEUE_NAME, O_WRONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1)
	{
		perror("ds loop: mq_open (res_ds)");
		exit(-1);
	}

	while (keep_on_running)
	{
		wait_next_activation(th);
		if (start)
		{
			clock_gettime(CLOCK_MONOTONIC, &tempTime);
			timespec_add_us(&tempTime, th->period);

			if (mq_timedreceive(req_ds, req_message, MAX_MSG_SIZE * 20, NULL, &tempTime) == -1)
			{
				// printf("No diagnostic request\n"); ---DEBUG
			}

			else
			{
				if (strcmp(req_message, "REQUEST WCET") == 0)
				{
					sprintf(res_message, "---------WCET BACKUP--------\nFILTER_WCET: %f microseconds\nCONTROL_WCET: %f microseconds\nACTUATOR_WCET : %f microseconds\n\n", wcet_filter, wcet_control, wcet_actuator);
					if (mq_send(res_ds, res_message, strlen(res_message) + 1, 1) == -1)
					{
						perror("ds_loop: res_ds error on mq_send");
						exit(-1);
					}
				}

				if (strcmp(req_message, "REQUEST DIAGNOSTIC") == 0)
				{
					pthread_mutex_lock(&shared_avg_sensor.lock);
					tempAVGSensor = shared_avg_sensor.value;
					pthread_mutex_unlock(&shared_avg_sensor.lock);

					pthread_mutex_lock(&shared_control.lock);
					tempControl = shared_control.value;
					pthread_mutex_unlock(&shared_control.lock);

					pthread_mutex_lock(&buffer_lock);
					for (int i = 0; i < BUF_SIZE; ++i)
						tempBuffer[i] = buffer[i];
					pthread_mutex_unlock(&buffer_lock);

					tempReference = reference;
					tempU = (U_actuator + U_control + U_filter) * 100;

					sprintf(res_message, "--------DIAGNOSTIC BACKUP--------\nAVGSensor: %d | Control: %d | Buffer: %d - %d - %d - %d - %d | Reference: %d\n\nFILTER_WCET: %f microseconds\nCONTROL_WCET: %f microseconds\nACTUATOR_WCET : %f microseconds\n\nCPU Utilization: %f%s\n\n",
							tempAVGSensor, tempControl, tempBuffer[0], tempBuffer[1], tempBuffer[2], tempBuffer[3], tempBuffer[4], tempReference, wcet_filter, wcet_control, wcet_actuator, tempU, "%");

					if (mq_send(res_ds, res_message, strlen(res_message) + 1, 0) == -1)
					{
						perror("ds_loop: res_ds error on mq_send");
						exit(-1);
					}
				}
			}
		}
	}

	if (mq_close(req_ds) == -1)
	{
		perror("ds_loop: mq_close req_ds");
		exit(-1);
	}

	if (mq_close(res_ds) == -1)
	{
		perror("ds_loop: mq_close res_ds");
		exit(-1);
	}

	pthread_exit(NULL);
}

int main(void)
{
	printf("The backup server is ACTIVE! [press 'q' to stop]\n");

	pthread_t acquire_filter_thread;
	pthread_t control_thread;
	pthread_t actuator_thread;
	pthread_t watchdog_thread;
	pthread_t deferrable_thread;

	pthread_attr_t myattr;
	struct sched_param myparam;

	set_cpu_affinity(&cpu);
	init_policy_and_protocol(&myattr, &myparam, &mutex_attr);

	pthread_mutex_init(&shared_avg_sensor.lock, &mutex_attr);
	pthread_mutex_init(&shared_control.lock, &mutex_attr);
	pthread_mutex_init(&buffer_lock, &mutex_attr);

	// ACQUIRE FILTER THREAD
	periodic_thread acquire_filter_th;
	start_thread(&acquire_filter_th, &myattr, &myparam, TICK_TIME, 50);
	pthread_create(&acquire_filter_thread, &myattr, acquire_filter_loop, (void *)&acquire_filter_th);

	// CONTROL THREAD
	periodic_thread control_th;
	start_thread(&control_th, &myattr, &myparam, TICK_TIME * BUF_SIZE, 45);
	pthread_create(&control_thread, &myattr, control_loop, (void *)&control_th);

	// ACTUATOR THREAD
	periodic_thread actuator_th;
	start_thread(&actuator_th, &myattr, &myparam, TICK_TIME * BUF_SIZE, 45);
	pthread_create(&actuator_thread, &myattr, actuator_loop, (void *)&actuator_th);

	// WATCHDOG THREAD
	periodic_thread wdog_th;
	start_thread(&wdog_th, &myattr, &myparam, 2 * TICK_TIME * BUF_SIZE, 40);
	pthread_create(&watchdog_thread, &myattr, watchdog, (void *)&wdog_th);

	// DEFERRABLE SERVER
	periodic_thread deferrable_th;
	start_thread(&deferrable_th, &myattr, &myparam, TICK_TIME / 2, 71);
	pthread_create(&deferrable_thread, &myattr, ds_loop, (void *)&deferrable_th);

	pthread_attr_destroy(&myattr);
	pthread_mutexattr_destroy(&mutex_attr);

	/* Wait user exit commands*/
	while (1)
	{
		if (getchar() == 'q')
			break;
	}
	keep_on_running = 0;

	if (mq_unlink(REFERENCE_QUEUE_NAME) == -1)
	{
		perror("Main: mq_unlink reference queue");
		exit(-1);
	}

	if (mq_unlink(WATCHDOG_QUEUE_NAME) == -1)
	{
		perror("Main: mq_unlink watchdog queue");
		exit(-1);
	}

	if (mq_unlink(PREVIUOS_QUEUE_NAME) == -1)
	{
		perror("Main: mq_unlink previous queue");
		exit(-1);
	}

	if (mq_unlink(DSREQUEST_QUEUE_NAME) == -1)
	{
		perror("Main: mq_unlink reference queue");
		exit(-1);
	}

	if (mq_unlink(DSRESPONSE_QUEUE_NAME) == -1)
	{
		perror("Main: mq_unlink reference queue");
		exit(-1);
	}

	printf("The backup server is STOPPED\n");

	return 0;
}
