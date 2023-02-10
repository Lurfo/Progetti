//------------------- CONTROLLER.C ---------------------- 
//Imposto la define che occorre al compilatore per impostare la priorità
#define _GNU_SOURCE
//Includo la libreria che contiene le funzioni per impostare l'affinity
#include <sched.h>

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

//Devo modificare il controllore in modo che ogni tot, vada ad inviare un messaggio all processo di backup per evitare che si attivi e che prenda lui il controllo dei task
//Aggiungo un nuovo thread che mi va a segnalare il task guardia

//Imposto il riferimento come variabile globale
//Posso anche non usare un semaforo per proteggere tale variabile in quanto viene usata solo nel caso in cui ricevo un particolare messaggio!
unsigned int reference = 110;


static int keep_on_running = 1;

struct shared_int {
	int value;
	pthread_mutex_t lock;
};
static struct shared_int shared_avg_sensor;
static struct shared_int shared_control;

//Definizione di un semaforo per il buffer in modo che quando il DS va a leggere i suoi valori non entra in conflitto con il filtro
pthread_mutex_t lockBuffer;
int buffer[BUF_SIZE];
int head = 0;


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

		// PRELIEVO DATI dalla coda del PLANT
		if (mq_receive(sensor_qd, message,MAX_MSG_SIZE,NULL) == -1){
			perror ("acquire filter loop: mq_receive (actuator)");	
			break;						//DEBUG
		}
		else{ 
			
			//Imposto il lock all'acquire filter, in modo che non vada in conflitto
			pthread_mutex_lock(&lockBuffer);
			buffer[head] = atoi(message);
			sum += buffer[head];
			pthread_mutex_unlock(&lockBuffer);
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

	char risp[MAX_MSG_SIZE];
	
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

void *segnalo(void *par){

	periodic_thread *th = (periodic_thread *)par; 

	//Definisco lo start del timer periodico
	start_periodic_timer(th, TICK_TIME);

	//Messaggio inviato dal segnalatore
	char messaggio[MAX_MSG_SIZE];

	//Messaggio di risposta
	char resp[MAX_MSG_SIZE];

	//Vado ad aprire la coda in scrittura dei dati, faccio in modo di creare la coda, in modo che se non è stata creata dal thread di guardia, la vado a creare io
	mqd_t idCoda = mq_open(GUARD_QUEUE_NAME, O_WRONLY);

	if(idCoda==-1){
		perror("SIGNAL: Errore creazione Coda\n"); 
		exit(1);
	}

	mqd_t idCodaRisposta = mq_open(GUARDIA_QUEUE_RESPONSE, O_RDONLY);
	
	if(idCodaRisposta==-1){
		perror("SIGNAL: Errore coda responso\n"); 
			exit(1);
	}


	int start=1;

	//Se la creazione va a buon fine, avvio il loop
	while(keep_on_running){
		
		wait_next_activation(th);

		sprintf(messaggio, "%d", reference);

		//Eseguo l'invio del messaggio sulla coda!
		if(mq_send(idCoda, messaggio, sizeof(messaggio), 0)==-1){
			perror("SIGNAL: Errore invio messaggio\n");
			exit(1);
		}

		//Eseguito un'unica volta all'avvio
		if(start){

			//Eseguo una ricezione del valore del responso
			if(mq_receive(idCodaRisposta, resp, sizeof(resp), 0)==-1){
				//printf("Reference backup non ricdvuta\n");

			}	

			else{

				reference = atoi(resp);

				//printf("Ricevuto valore: %d\n", reference);
			}	

			start=0;	

		}


	}

	//Eseguo la close della coda
	if(mq_close(idCoda)==-1){
		perror("SIGNAL: Errore Chiusura coda\n");
		exit(1);
	}

	if(mq_close(idCodaRisposta)==-1){
		perror("SIGNAL: Errore chiusura coda risposta\n"); 
		exit(1);
	}

}


//Impostazione della funzione del DS
void *DefSer(void *par){

	periodic_thread *th = (periodic_thread *)par;

	//Imposto il timer in modo che parta da subito!
	start_periodic_timer(th, 0);

	struct timespec time;

	char mess[MAX_MSG_SIZE];

	char risp[MAX_MSG_SIZE*10];

	//Imposto i valori temporanei che mi occorono per prendere i valori
	int tempAvg, tempControl, tempBuff[5], tempRef;


	//Imposto attributo per la coda di richiesta, in modo da usare un messaggio con una dimensione minore rispetti a quello di responso
	struct mq_attr attrReq; 

	attrReq.mq_flags=0;
	attrReq.mq_curmsgs=0;
	attrReq.mq_maxmsg=10;
	attrReq.mq_msgsize=MAX_MSG_SIZE;

	//imposto attributo per la coda di responso
	struct mq_attr attrRes; 

	attrRes.mq_flags=0; 
	attrRes.mq_curmsgs=0; 
	attrRes.mq_maxmsg=MAX_MESSAGES; 
	attrRes.mq_msgsize=MAX_MSG_SIZE*10;

	//Creo la coda delle richieste, impostandola come bloccante
	mqd_t idCodaRequest = mq_open(DS_QUEUE_REQUEST, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attrReq);

	//Controllo corretta apertura della coda
	if(idCodaRequest==-1){
		perror("DS: Impossibile aprire la coda della richiesta\n"); 
			exit(1);
	}

	mqd_t idCodaResponse = mq_open(DS_QUEUE_RESPONSE, O_WRONLY | O_CREAT, QUEUE_PERMISSIONS, &attrRes);

	if(idCodaResponse==-1){
		perror("DS: Impossibile aprire la coda del responso\n"); 
			exit(1);
	}


	//Imposto il ciclo while
	while(keep_on_running){

		wait_next_activation(th); 

		//Prendo il tempo attuale e gli sommo il periodo del server
		clock_gettime(CLOCK_MONOTONIC, &time);

		timespec_add_us(&time, th->period);

		//Eseguo la receive temporizzata del messaggio
		if(mq_timedreceive(idCodaRequest, mess, sizeof(mess), 0, &time)==-1){
			//printf("DS: Messaggio non Ricevuto!\n");
		}

		else{
			printf("MESSAGGIO RICEVUTO!!!\n");

			//Vado a prelevare tutti i parametri
			pthread_mutex_lock(&shared_avg_sensor.lock); 
			tempAvg = shared_avg_sensor.value;
			pthread_mutex_unlock(&shared_avg_sensor.lock);

			pthread_mutex_lock(&shared_control.lock);
			tempControl=shared_control.value;
			pthread_mutex_unlock(&shared_control.lock);

			tempRef=reference;

			pthread_mutex_lock(&lockBuffer); 
				for(int i=0; i<BUF_SIZE; i++){
					tempBuff[i]=buffer[i];
				}
			pthread_mutex_unlock(&lockBuffer); 

			sprintf(risp, "Avg:%d\nControl:%d\nBuffer:%d, %d, %d, %d, %d\nReference:%d\n", tempAvg, tempControl, tempBuff[0], tempBuff[1], tempBuff[2], tempBuff[3], tempBuff[4], tempRef);

			if(mq_send(idCodaResponse, risp, strlen(risp)+1, 0)==-1){
				perror("DS: Errore invio messaggio!\n");
			}

		}
		
	}

	if(mq_close(idCodaRequest)==-1){
		perror("DS:Errore chiusura della Richiesta!\n");
			exit(1);
	}

	if(mq_close(idCodaResponse)==-1){
		perror("DS:Errore chiusura coda Responso\n");
			exit(1);
	}
}

int main(void)
{
	printf("The controller is STARTED! [press 'q' to stop]\n");
 	
	pthread_t acquire_filter_thread;
    pthread_t control_thread;
    pthread_t actuator_thread;

	//Definisco il thread segnalatore
	pthread_t segnalatore;


	//Nel main, devo anche definire il deferrable server che mi occorre per gestire eventuali richieste aperiodiche che possono esserci
	//da parte di un task che viene creato appoaitamente
	pthread_t ds;


	//In quanto vado ad usare un DS, che è un altro processo che va ad usare le strutture dati di cui sopra e potrei avere dei problemi
	//legati all'uso dei semafori, devo definire l'attributo apposito che va ad impostare il protocollo di PI su questi
	//Inizializzando ed impostando il corretto protocollo per la gestione delle priorità
	pthread_mutexattr_t mAttr;
	pthread_mutexattr_init(&mAttr);
	pthread_mutexattr_setprotocol(&mAttr, PTHREAD_PRIO_INHERIT);

	pthread_mutex_init(&shared_avg_sensor.lock, &mAttr);
	pthread_mutex_init(&shared_control.lock, &mAttr);

	pthread_mutex_init(&lockBuffer, &mAttr);

	//Passo alla definizione dell'attributo dei thread e della struttura che imposta la loro priorità
	pthread_attr_t myattr;
	struct sched_param myparam;

	pthread_attr_init(&myattr);
	pthread_attr_setschedpolicy(&myattr, SCHED_FIFO);
	pthread_attr_setinheritsched(&myattr, PTHREAD_EXPLICIT_SCHED); 

	/*

	//IMPOSTO L'AFFINITY--------------------------------------------
	cpu_set_t numCPU;

	//Iniziliazzo il valore che ho definito
	CPU_ZERO(&numCPU);

	//Imposto la cpu sulla quale deve eseguire
	CPU_SET(0, &numCPU);
	//NOTA:Per ogni thread devo poi impostare l'affinity!!!
	//--------------------------------------------------------------

	*/

	// ACQUIRE FILTER THREAD
	periodic_thread acquire_filter_th;
	acquire_filter_th.period = TICK_TIME;
	acquire_filter_th.priority = 50;

	myparam.sched_priority = acquire_filter_th.priority;
	pthread_attr_setschedparam(&myattr, &myparam); 
	pthread_create(&acquire_filter_thread,&myattr,acquire_filter_loop,(void*)&acquire_filter_th);

	//Imposto l'affinity della cpu
	//pthread_setaffinity_np(acquire_filter_thread, sizeof(numCPU), &numCPU);

	// CONTROL THREAD
	periodic_thread control_th;
	control_th.period = TICK_TIME*BUF_SIZE;
	control_th.priority = 45;

	myparam.sched_priority = control_th.priority;
	pthread_attr_setschedparam(&myattr, &myparam); 
	pthread_create(&control_thread,&myattr,control_loop,(void*)&control_th);

	//pthread_setaffinity_np(control_thread, sizeof(numCPU), &numCPU);

	// ACTUATOR THREAD
	periodic_thread actuator_th;
	actuator_th.period = TICK_TIME*BUF_SIZE;
	actuator_th.priority = 45;

	pthread_attr_setschedparam(&myattr, &myparam); 
	pthread_create(&actuator_thread,&myattr,actuator_loop,(void*)&actuator_th);

	//pthread_setaffinity_np(actuator_thread, sizeof(numCPU), &numCPU);

	//ATTIVAZIONE DEL THREAD SEGNALATORE---------------------------------
		periodic_thread segnalatore_th;

		segnalatore_th.period=2*TICK_TIME*BUF_SIZE;
		segnalatore_th.priority=40; //Imposto la priorità minore in quanto ha il periodo maggiore!

		myparam.sched_priority=segnalatore_th.priority;
		//Avendo la priorità uguale a quella dei thread precedenti, posso andare direttamente ad usare l'attributo che ho usato prima
		pthread_attr_setschedparam(&myattr, &myparam);
		pthread_create(&segnalatore, &myattr, segnalo, (void *)&segnalatore_th);

		//pthread_setaffinity_np(segnalatore, sizeof(numCPU), &numCPU);
	//--------------------------------------------------------------------

	//ATTIVAZIONE DEL THREAD DS-------------------------------------------
		periodic_thread ds_thread; 

		//Lo imposto come task che ha la massima priorità
		ds_thread.period=TICK_TIME/2; 
		ds_thread.priority=60;

		//Imposto la priorità corretta nell'attributo e creo il thread
		myparam.sched_priority=ds_thread.priority; 
		pthread_attr_setschedparam(&myattr, &myparam);

		pthread_create(&ds, &myattr, DefSer, (void *) &ds_thread);

		//pthread_setaffinity_np(ds, sizeof(numCPU), &numCPU);
	//--------------------------------------------------------------------

	pthread_attr_destroy(&myattr);
	pthread_mutexattr_destroy(&mAttr);
	
	
	/* Wait user exit commands*/
	while (1) {
   		if (getchar() == 'q') break;
  	}
	keep_on_running = 0;


	//Scelgo di non eseguire qui l'unlink della coda del response in modo che possa continuare ad essere usata anche dal backup, se il controller dovessere non crashare
	/*
	if (mq_unlink (REFERENCE_QUEUE_NAME) == -1) {
        perror ("Main: mq_unlink reference queue");
        exit (1);
    }
	*/

	//Unlink della coda del DS
	/*if(mq_unlink(DS_QUEUE_REQUEST)==-1){
		perror("MAIN: Errore unlink coda RichiestaDS\n"); 
			exit(1);
	}

	if(mq_unlink(DS_QUEUE_RESPONSE)==-1){
		perror("MAIN: Errore unlink coda RispostaDS\n");
		exit(1);
	}*/

 	printf("The controller is STOPPED\n");

	return 0;
}




