//------------------- CONTROLLER.C ---------------------- 

//Tale file, copia del semplice file originale, contiene anche un thread "watch dog", il cui compito è quello di controllare che il task "primario" esegua senza problemi
//altrimenti provvede a far eseguire i task di backup per verificare che la struttura continui ad eseguire correttamente
//il task che vado ad instanziare, che esegue con un periodo pari al doppio di quello del controller precedente, riceve su una coda di messaggi, il valore a cui si 
//trovava precedentemente il controllore e lo imposta in modo che i vari task possano usarlo 


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

int buffer[BUF_SIZE];
int head = 0;

//IMPOSTO UNA VARIABILE GLOBALE CHE FA ATTIVARE IL TASK DA METTERE SUBITO DOPO IL WHILE, IN OGNI TASK PERIODICO
static int start = 0;

//Mi definisco la variabile globale di riferimento
unsigned int reference = 110;

//Imposto il valore di riferimento del sistema come un valore globale (DA IMPLEMENTARE!!!)


void * acquire_filter_loop(void * par) {
	
	periodic_thread *th = (periodic_thread *) par;
	//start_periodic_timer(th,TICK_TIME);

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

		//wait_next_activation(th);

		//Faccio in modo di attendere il segnale di partenza dalla guardia
		if(start){

		// PRELIEVO DATI dalla coda del PLANT
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

	}		

	/* Clear */
    if (mq_close (sensor_qd) == -1) {
        perror ("acquire filter loop: mq_close sehsor_qd");
        exit (1);
    }

	return 0;
}


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


	unsigned int plant_state = 0;
	int error = 0;
	unsigned int control_action = 0;
	
	while (keep_on_running)
	{

		wait_next_activation(th);

		//Faccio in modo di attendere il segnale di partenza dalla guardia
		if(start){

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

		if (error > 0) control_action = 1;
		else if (error < 0) control_action = 2;
		else control_action = 3;

		// aggiorna la control action
		pthread_mutex_lock(&shared_control.lock);
		shared_control.value = control_action;
		pthread_mutex_unlock(&shared_control.lock);

		}
	
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

		//Faccio in modo di attendere il segnale di partenza dalla guardia
		if(start){

		// prelievo della control action
		pthread_mutex_lock(&shared_control.lock);
		control_action = shared_control.value;
		pthread_mutex_unlock(&shared_control.lock);
		
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

	}
	/* Clear */
    if (mq_close (actuator_qd) == -1) {
        perror ("Actuator loop: mq_close actuator_qd");
        exit (1);
    }
	return 0;
}

//Definizione della funzione del thread di guardia, che deve essere impostato comunque come un thread periodico
void *guard(void *par){

	//Casting inverso della struttura che riceve come parametro di ingresso
	periodic_thread  *th = (periodic_thread *) par;

	//Avvio del timer periodico
	start_periodic_timer(th, TICK_TIME);

	//Variabile che mantengo per la receive temporizzata, in modo che il task non si blocchi sulla receive e in caso di un messaggio non ricevuto
	//posso far arrivare i task
	struct timespec temp;
	
	//Definizione del messaggio da prelevare
	char mess[MAX_MSG_SIZE];

	char risp[MAX_MSG_SIZE];

	//Impostazioni dei parametri della coda
	struct mq_attr attr;

	attr.mq_flags=0; 
	attr.mq_curmsgs=0;
	attr.mq_msgsize=MAX_MSG_SIZE; 
	attr.mq_maxmsg=MAX_MESSAGES;

	//Creo la coda sulla quale in controllore principale deve inviare il messaggio
	//La coda deve essere specificata come non bloccante in modo che la receive non sia bloccante, la creo sia in lettura che in scrittura, in modo da
	//rispedire il valore quando questo viene interrotto!
	mqd_t idCoda = mq_open(GUARD_QUEUE_NAME, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr);

	//Eseguo un controllo se la coda sia stata correttamente creata
	if(idCoda==-1){
		perror("GUARD: Errore creazione coda GUARD_QUEUE_NAME\n"); 
		exit(1);
	}

	//Mi definisco una coda sulla quale devo andare ad inviare il mio reference al controllore
	//La coda non è bloccante in modo che il controllore non attenda quando esegue la receive
	mqd_t idCodaRisposta = mq_open(GUARDIA_QUEUE_RESPONSE, O_WRONLY | O_CREAT | O_NONBLOCK, QUEUE_PERMISSIONS, &attr);

	//Eseguo un controllo se la coda sia stata correttamente creata
	if(idCodaRisposta==-1){
		perror("GUARD: Errore creazione coda del responso\n"); 
		exit(1);
	}

	int invio=1;

	//Avvio il ciclo, regolato in base al thread principale
	while(keep_on_running){
		
		//Eseguo una wait next activation, perchè è sempre un task periodico che sta eseguendo
		wait_next_activation(th); 

		//Clock gettime, per eseguire la receive temporizzata
		clock_gettime(CLOCK_MONOTONIC, &temp);

		//Vado a sommare i secondi di attesa, pari a due volte il periodo del controllore
		timespec_add_us(&temp, 2*TICK_TIME*BUF_SIZE);

		//Eseguo la receive temporizzata
		if(mq_timedreceive(idCoda, mess, MAX_MSG_SIZE, NULL, &temp)==-1){
			
			printf("ATTIVO, HO PERSO IL SEGNALE\n");

			//printf("valore reference in uso: %d\n", reference);

			//Vado a modificare la variabile di avvio, in modo da far partire i thread
			start=1;

			//printf("Valore reference: %d\n", reference);

			//Devo impostare l'invio ad 1, in modo che appena vengo disattivato posso inviare la reference
			//L'incremento avviene solo quando la variabile di invio è 0!
			invio=1;
		}
		
		else{	

			//Se il messaggio è ricevuto allora non sono attivo
			printf("NON ATTIVO, CONTROLLORE IN BUONO STATO\n");

			//printf("Ricevuto messaggio: %d\n", reference);
			start=0;


			//Quando vengo disattivato, perchè si riattiva il controllore, gli comunico l'ultimo valore della reference a cui sono arrivato
			//devo verificare che non ho già eseguito questo invio
			//Prima però di vedere il messaggio che mi è stato mandato, vado ad inviare al controller il valore della mia reference
			if(invio){

				sprintf(risp, "%d", reference);

				if(mq_send(idCodaRisposta, risp, sizeof(risp), 0)==-1){
					perror("GUARD: Non sono riuscito ad inviare la reference\n"); 
						exit(1);
				}

				//Riduco la variabile per determinare se eseguire l'invio o meno
				invio=0;

				//printf("Valore reference inviato: %d\n", reference);
			}

			reference = atoi(mess);

			//printf("valore reference backup: %d\n", reference);

		}
		
	}

	//Dopo il while, devo chiudere la coda, l'unlink viene fatto dal main
	if(mq_close(idCoda)==-1){
		perror("GUARD: Errore chiusura della coda\n"); 
		exit(1);
	}

	//Chiudo la coda dove invio la reference
	if(mq_close(idCodaRisposta)==-1){
		perror("GUARD: Errore chiusura della coda risposta\n"); 
		exit(1);
	}

	return 0;

}




int main(void)
{
	printf("The controller is STARTED! [press 'q' to stop]\n");
 	
	pthread_t acquire_filter_thread;
    pthread_t control_thread;
    pthread_t actuator_thread;

	//Thread di guardia
	pthread_t guardia;

	pthread_mutex_init(&shared_avg_sensor.lock, NULL);
	pthread_mutex_init(&shared_control.lock, NULL);


	pthread_attr_t myattr;
	struct sched_param myparam;

	pthread_attr_init(&myattr);
	pthread_attr_setschedpolicy(&myattr, SCHED_FIFO);
	pthread_attr_setinheritsched(&myattr, PTHREAD_EXPLICIT_SCHED); 

	// ACQUIRE FILTER THREAD
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

	//CREAZIONE DEL THREAD DI GUARDIA--------------------------------------
		periodic_thread guardia_th; 
		//Impostazione dei valori della struttura
		guardia_th.period = 2*TICK_TIME*BUF_SIZE; //Ha il periodo più grande rispetto a tutti gli altri task
		guardia_th.priority = 40; //Ha la priorità più bassa secondo RM; 

		//Modifico la priorità nella struttura
		myparam.sched_priority=guardia_th.priority;

		//Modifico la priorità dell'attributo
		pthread_attr_setschedparam(&myattr, &myparam); 

		//Vado a creare il thread
		pthread_create(&guardia, &myattr, guard, (void *) &guardia_th);
	//--------------------------------------------------------------------

	pthread_attr_destroy(&myattr);
	
	
	/* Wait user exit commands*/
	while (1) {
   		if (getchar() == 'q') break;
  	}
	keep_on_running = 0;


	//NOTA: Scelgo di eseguire l'unlink della coda reference nel backup, in modo che se il controllore dovesse disattivarsi, allora posso comunque andare a
	//modificare la reference mediante apposito task, anche se sto eseguendo questo backup
	if (mq_unlink (REFERENCE_QUEUE_NAME) == -1) {
        perror ("Main: mq_unlink reference queue");
        exit (1);
    }

	//Nel main, eseguo l'unlink della coda del thread guardia, in una struttura di controllo, in caso di errori
	if(mq_unlink(GUARD_QUEUE_NAME)==-1){
		perror("Main: Unlink guard queue error\n");
		exit(1);
	}

	//Eseguo unlink della coda di risposta
	if(mq_unlink(GUARDIA_QUEUE_RESPONSE)==-1){
		perror("Main: Unlink coda responso error\n");
		exit(1);
	}


 	printf("The controller is STOPPED\n");
	return 0;
}




