//------------------- CONTROLLER.C ---------------------- 
//Parte che mantiene il controllore e gli altri task
//Controller.c e plant.c comunicano con code di messaggi


//Fare in modo che un task esterno possa interagire con questo con un deferrable server
//Il task esterno viene visto come uno che interagisce con il deferrable server, che esegue ad un periodo t/2, il più veloce, legge tutti i buffer e lo rinvia
//alla coda del task esterno
//Col deferrable devo andare a cambiare i semafori per utilizzare un protocollo di PI, devo anche andare a proteggere il buffer usando un lock apposito


//Fare in modo di introdurre un controllore che esegue una replica
//In questo caso, devo creare un task che attende un segnale da parte del controllore ad ogni ciclo (devo aggiungere una parte che va ad inviare questo segnale)
//Il task che sta in attesa esegue poi il controllore (attiva la replica solo quando muore il primary)
//Con questo modo, non posso tollerare eventuali errori sui task
//un'idea sarebbe quello di mandare al processo che controlla lo stato del valore di riferimento!

//Potrei anche eseguire i due controllori in parallelo per poter prevenire eventuali errori (Il problema è che non posso sapere quale dei due ha sbagliato)
//per una migliore tolleranza, potrei aggiungere 3 controllori, almeno due valori devono essere uguali, in modo che poi il terzo, che da un valore errato, viene eliminato


//L'ideale sarebbe che i task eseguano tutti sulla medesima CPU, in modo che posso anche usare RM

#include <time.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <fcntl.h>
#include <string.h>
#include "rt-lib.h"
#include "parameters.h"

//emulates the controller

static int keep_on_running = 1;

struct shared_int {
	int value;
	pthread_mutex_t lock;
};
static struct shared_int shared_avg_sensor;
static struct shared_int shared_control;

//Contiene i valori intermedi
int buffer[BUF_SIZE];
//Gestisce il buffer
int head = 0;

//Esegue la media degli ultimi 5 valori estratti
//Apre la coda in lettura, ad ogni ciclo legge e accumula 5 elementi
//Quando li ha raggiunti, esegue una megia e la inserisce nel parametro

//Questo poteva essere implementato come il l'attuatore dell'impianto, invece viene eseguito come un task periodico
//questo indica che se non vado ad eseguire questo prima dell'impianto, ho un ritardo fisso che non posso recuperare, leggendo dei dati che mi arrivano in ritardo
//(proprio perchè vado ad eseguire una lettura ad ogni ciclo)
//Quindi potrei scegliere di fare l'implementazione simile all'altro caso, per aver un funzionamento duale
//All'inizio però avrò un treno di acquisizioni che potrei anche non usare

//Eliminando la wait e lo start periodic timer, posso andare a rendere il task come un task ciclico ma non periodico!
void * acquire_filter_loop(void * par) {
	
	periodic_thread *th = (periodic_thread *) par;
	start_periodic_timer(th,TICK_TIME);

	// Messaggio da prelevare dal driver
	char message [MAX_MSG_SIZE];

	/* Coda */
	struct mq_attr attr;

	attr.mq_flags = 0;				
	attr.mq_maxmsg = MAX_MESSAGES;	
	attr.mq_msgsize = MAX_MSG_SIZE; 
	attr.mq_curmsgs = 0;
	
	// Apriamo la coda sensor del plant in lettura 
	mqd_t sensor_qd;
	if ((sensor_qd = mq_open (SENSOR_QUEUE_NAME, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS,&attr)) == -1) {
		perror ("acquire filter loop: mq_open (sensor)");
		exit (1);
	}
	unsigned int sum = 0;
	int cnt = BUF_SIZE;


	while (keep_on_running)
	{
		wait_next_activation(th);

		// PRELIEVO DATI dalla coda del PLANT
		//Eseguo una receive bloccante, se non ricevo messaggi non devo fare niente
		if (mq_receive(sensor_qd, message,MAX_MSG_SIZE,NULL) == -1){
			perror ("acquire filter loop: mq_receive (actuator)");	
			break;						//DEBUG
		}
		else{ 
			buffer[head] = atoi(message);
			sum += buffer[head];
			head = (head+1)%BUF_SIZE;
			cnt--;

			//printf("\t\t\t\tbuffer[%d]=%d, sum=%d\n",head,buffer[head],sum); //DEBUG

			// calcolo media sulle ultime BUF_SIZE letture
			//Esegue solo quando raggiungo 5 accumuli
			if (cnt == 0) {
				cnt = BUF_SIZE;
				pthread_mutex_lock(&shared_avg_sensor.lock);
				shared_avg_sensor.value = sum/BUF_SIZE;
				//printf("\t\t\t\tavg_sensor.value=%d\n",shared_avg_sensor.value); //DEBUG
				pthread_mutex_unlock(&shared_avg_sensor.lock);
				sum = 0;
			}	
		}
	}		

	/* Clear */
    if (mq_close (sensor_qd) == -1) {
        perror ("acquire filter loop: mq_close sehsor_qd");
        exit (1);
    }

	return 0;
}


//Questo deve leggere dalla coda del reference, che scrive solo quando viene lanciato
//le receive devono quindi essere non bloccanti, andando a controllare ogni volta se c'è qualche messaggio nella coda
void * control_loop(void * par) {

	periodic_thread *th = (periodic_thread *) par;
	start_periodic_timer(th,TICK_TIME);
	
	// Messaggio da prelevare dal reference
	char message [MAX_MSG_SIZE];
	
	/* Coda */
	struct mq_attr attr;

	attr.mq_flags = 0;				
	attr.mq_maxmsg = MAX_MESSAGES;	
	attr.mq_msgsize = MAX_MSG_SIZE; 
	attr.mq_curmsgs = 0;
	
	// Apriamo la coda per il reference, in lettura e non bloccante
	mqd_t reference_qd;
	if ((reference_qd = mq_open (REFERENCE_QUEUE_NAME, O_RDONLY | O_CREAT | O_NONBLOCK, QUEUE_PERMISSIONS,&attr)) == -1) {
		perror ("control loop: mq_open (reference)");
		exit (1);
	}

	unsigned int reference = 110;

	//Variabili che vengono usate dal controllore
	unsigned int plant_state = 0;
	int error = 0;
	unsigned int control_action = 0;
	while (keep_on_running)
	{
		wait_next_activation(th);

		// legge il plant state 
		pthread_mutex_lock(&shared_avg_sensor.lock);
		plant_state = shared_avg_sensor.value;
		pthread_mutex_unlock(&shared_avg_sensor.lock);

		// riceve la reference (in modo non bloccante)
		if (mq_receive(reference_qd, message,MAX_MSG_SIZE,NULL) == -1){
			//printf ("No reference ...\n");							//DEBUG
		}
		else{
			//printf ("Reference received: %s.\n",message);			//DEBUG
			reference = atoi(message);
		}

		// calcolo della legge di controllo
		error = reference - plant_state;

		//Eseguo un controllo in base al al risultato dell'operazione
		//Il controllo viene utilizzato per andare a mandare un messaggio all'attuatore
		if (error > 0) control_action = 1;
		else if (error < 0) control_action = 2;
		else control_action = 3;

		// aggiorna la control action
		pthread_mutex_lock(&shared_control.lock);
		shared_control.value = control_action;
		pthread_mutex_unlock(&shared_control.lock);
	}


	/* Clear */
    if (mq_close (reference_qd) == -1) {
        perror ("control loop: mq_close reference_qd");
        exit (1);
    }
	return 0;
}


void * actuator_loop(void * par) {

	periodic_thread *th = (periodic_thread *) par;
	start_periodic_timer(th,TICK_TIME);

	// Messaggio da prelevare dal driver
	char message [MAX_MSG_SIZE];

	/* Coda */
	struct mq_attr attr;

	attr.mq_flags = 0;				
	attr.mq_maxmsg = MAX_MESSAGES;	
	attr.mq_msgsize = MAX_MSG_SIZE; 
	attr.mq_curmsgs = 0;
	
	// Apriamo la coda actuator del plant in scrittura 
	mqd_t actuator_qd;
	if ((actuator_qd = mq_open (ACTUATOR_QUEUE_NAME, O_WRONLY|O_CREAT, QUEUE_PERMISSIONS,&attr)) == -1) {
		perror ("actuator  loop: mq_open (actuator)");
		exit (1);
	}	

	unsigned int control_action = 0;
	unsigned int control = 0;
	while (keep_on_running)
	{
		wait_next_activation(th);
		// prelievo della control action
		pthread_mutex_lock(&shared_control.lock);
		control_action = shared_control.value;
		pthread_mutex_unlock(&shared_control.lock);
		
		//Eseguo la "traduzione" dell'azione da eseguire
		switch (control_action) {
			case 1: control = 1; break;
			case 2:	control = -1; break;
			case 3:	control = 0; break;
			default: control = 0;
		}

		printf("Control: %d\n",control); //DEBUG
		sprintf (message, "%d", control);
		//invio del controllo al driver del plant
		if (mq_send (actuator_qd, message, strlen (message) + 1, 0) == -1) {
		    perror ("Sensor driver: Not able to send message to controller");
		    continue;
		}
	}
	/* Clear */
    if (mq_close (actuator_qd) == -1) {
        perror ("Actuator loop: mq_close actuator_qd");
        exit (1);
    }
	return 0;
}

int main(void)
{
	printf("The controller is STARTED! [press 'q' to stop]\n");
 	
	pthread_t acquire_filter_thread;
    pthread_t control_thread;
    pthread_t actuator_thread;

	pthread_mutex_init(&shared_avg_sensor.lock, NULL);
	pthread_mutex_init(&shared_control.lock, NULL);

	pthread_attr_t myattr;
	struct sched_param myparam;

	pthread_attr_init(&myattr);
	pthread_attr_setschedpolicy(&myattr, SCHED_FIFO);
	pthread_attr_setinheritsched(&myattr, PTHREAD_EXPLICIT_SCHED); 

	// ACQUIRE FILTER THREAD
	//Il filtro è quello che ha una velocità maggiore, quindi ha una priorità più alta! (schedulando secondo RM)
	periodic_thread acquire_filter_th;
	acquire_filter_th.period = TICK_TIME;
	acquire_filter_th.priority = 50;

	myparam.sched_priority = acquire_filter_th.priority;
	pthread_attr_setschedparam(&myattr, &myparam); 
	pthread_create(&acquire_filter_thread,&myattr,acquire_filter_loop,(void*)&acquire_filter_th);

	// CONTROL THREAD
	periodic_thread control_th;
	control_th.period = TICK_TIME*BUF_SIZE;
	control_th.priority = 45;

	myparam.sched_priority = control_th.priority;
	pthread_attr_setschedparam(&myattr, &myparam); 
	pthread_create(&control_thread,&myattr,control_loop,(void*)&control_th);

	// ACTUATOR THREAD
	periodic_thread actuator_th;
	actuator_th.period = TICK_TIME*BUF_SIZE;
	actuator_th.priority = 45;

	pthread_attr_setschedparam(&myattr, &myparam); 
	pthread_create(&actuator_thread,&myattr,actuator_loop,(void*)&actuator_th);

	pthread_attr_destroy(&myattr);
	
	
	/* Wait user exit commands*/
	while (1) {
   		if (getchar() == 'q') break;
  	}
	keep_on_running = 0;

	if (mq_unlink (REFERENCE_QUEUE_NAME) == -1) {
        perror ("Main: mq_unlink reference queue");
        exit (1);
    }

 	printf("The controller is STOPPED\n");
	return 0;
}
