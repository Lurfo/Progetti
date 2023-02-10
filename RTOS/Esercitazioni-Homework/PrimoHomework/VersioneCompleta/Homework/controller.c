//------------------- CONTROLLER.C ----------------------
#define _GNU_SOURCE
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

//***************************************VARIABILI***********************************************************
//Imposto il riferimento come variabile globale
//Posso anche non usare un semaforo per proteggere tale variabile in quanto viene usata solo nel caso in cui ricevo un particolare messaggio!
unsigned int reference = 110;

//Variabile usata per fare in modo che i thread continuano a ciclare!
static int keep_on_running = 1;

//La struct mantiene i valori medi e di controllo
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

//Imposto delle variabili che mi occorrono per il calcolo del WCET per i tre task
float filterWCET;
float controlWCET;
float actuatorWCET;

//Variabili per il calcolo del fattore di utilizzazione!!! (riferito al WCET)
float uFilter; 
float uControl; 
float uActuator;
//*************************************************************************************************************

//*************************************FUNZIONI DI UTILITA'**************************************************************************
void initAttr(pthread_attr_t *attr, pthread_mutexattr_t *mAttr, cpu_set_t *cpu){
	
	//Inizializzazione dell'attributo del thread
	pthread_attr_init(attr); 
	pthread_attr_setschedpolicy(attr, SCHED_FIFO);
	pthread_attr_setinheritsched(attr, PTHREAD_EXPLICIT_SCHED);

	//Inizializzazione dell'attributo del semaforo
	pthread_mutexattr_init(mAttr); 
	pthread_mutexattr_setprotocol(mAttr, PTHREAD_PRIO_INHERIT);

	//Inizializzazione della CPU
	CPU_ZERO(cpu); 
	//Imposto la cpu (o le cpu) a cui corrisponde il secondo argomento
	CPU_SET(0, cpu);

	//Imposto l'attributo in modo che mantenga la CPU sulla quale eseguire il thread
	pthread_attr_setaffinity_np(attr, sizeof(cpu_set_t), cpu);

	/*UNA NOTA: 
		L'affinity del controller viene impostata correttamente, contrariamente a quanto avviene con i task di backup (leggere nota nella stessa funzione del file backup.c)
	*/
}

//Funzione di inizializzazione dei thread
void initThread(pthread_t *thread, periodic_thread *th, int prio, int period, struct sched_param *myparam, pthread_attr_t *attr, void *startingRoutine, cpu_set_t *cpu){

	static int i=0;
	//Definizione dei valori nella struct
	th->index=i++;
	th->period=period; 
	th->priority=prio; 

	//Impostazione della priorità
	myparam->sched_priority=th->priority;
	pthread_attr_setschedparam(attr, myparam);

	//Creazione del thread
	pthread_create(thread, attr, startingRoutine, (void *)th);

}

//**************************************************************************************************************************************


//------------------------------------------------TASK DELL'IMPIANTO-------------------------------------------------------------------------
//NOTA:Il task di seguito è periodico, la sua periodicità viene scandita dall'invio dei messaggi da parte del sensore!
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

	//Imposto due timespec per il calcolo del WCET, una prende il valore all'inizio e l'altra alla fine!
	struct timespec inizio;
	struct timespec fine;
	//Inizializzazione del WCET e definizione di una variabile temporanea che mantiene il valore temporaneo, usato per un confronto!
	filterWCET=0;
	float tempWCET=0;
		
	
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

		//Calcolo del tempo iniziale, usando un particolare tipo di clock che conta il tempo solo quando il task sta effettivamente eseguendo sulla cpu
		//se viene sospeso, non si controlla
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &inizio);

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

		//Dopo il job calcolo il tempo finale, usando sempre il medesimo clock precedente
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &fine);

		//Calcolo il WCET, come una differenza tra il valore finale e il valore iniziale
		//(espresso in microsecondi)
		tempWCET=(float)difference_ns(&fine, &inizio)/1000;

		//Mi vado a salvare il massimo valore del WCET!
		if(filterWCET==0 || tempWCET>filterWCET){
			filterWCET=tempWCET;
			uFilter=tempWCET/TICK_TIME;
		}


	}		

	/* Clear */
    if (mq_close (sensor_qd) == -1) {
        perror ("acquire filter loop: mq_close sehsor_qd");
        exit (1);
    }

	pthread_exit(NULL);
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

	//Valori usati dal controllo
	unsigned int plant_state = 0;
	int error = 0;
	unsigned int control_action = 0;

	//Mi definisci i valori principali che mi occorrono per il calcolo del WCET (simili a quelli del task precedenti)
	struct timespec inizio; 
	struct timespec fine;
	
	//Inizializzazione dei valori appositi
	controlWCET=0;
	float tempWCET=0;

	while (keep_on_running)
	{

		wait_next_activation(th);

		//Calcolo del tempo iniziale (con clock apposito)
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &inizio);

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

		//Calcolo del tempo finale
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &fine);

		//Calcolo del WCET
		tempWCET= (float)difference_ns(&fine, &inizio)/1000; 

		//Imposto il valore massimo
		if(controlWCET==0 || tempWCET>controlWCET){
			controlWCET=tempWCET;
			uControl = tempWCET/th->period;
		}
		
	}

	/* Clear */
    if (mq_close (reference_qd) == -1) {
        perror ("control loop: mq_close reference_qd");
        exit (1);
    }

	pthread_exit(NULL);
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

	//Valori usati dall'attuatore
	unsigned int control_action = 0;
	unsigned int control = 0;

	//Imposto i valori usati per il calcolo del WCET
	struct timespec inizio; 
	struct timespec fine; 

	actuatorWCET=0; 
	float tempWCET=0; 

	while (keep_on_running)
	{
		wait_next_activation(th);

		//Prendo il tempo iniziale
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &inizio);

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

		//Prendo il tempo finale
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &fine); 

		//Calcolo il valore temporaneo del WCET
		tempWCET=(float)difference_ns(&fine, &inizio)/1000; 

		//Imposto il valore massimo
		if(actuatorWCET==0 || tempWCET>actuatorWCET){
			actuatorWCET=tempWCET;
			uActuator = tempWCET/th->period;
		}

	}


	/* Clear */
    if (mq_close (actuator_qd) == -1) {
        perror ("Actuator loop: mq_close actuator_qd");
        exit (1);
    }

	pthread_exit(NULL);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------


//***********************TASK AGGIUNTIVI DEL CONTROLLER**********************************************************************************************************
//Task che invia heartbeat al backup
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


	//Variabile che mi occorre all'avvio per vedere se il backup mi ha inviato qualche dato!
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

	pthread_exit(NULL);

}


//Impostazione del DS
void *DefSer(void *par){

	periodic_thread *th = (periodic_thread *)par;

	//Imposto il timer in modo che parta da subito!
	start_periodic_timer(th, 0);

	struct timespec time;

	char mess[MAX_MSG_SIZE];

	char risp[MAX_MSG_SIZE*20];

	//Imposto i valori temporanei che mi occorono per prendere i valori
	int tempAvg, tempControl, tempBuff[5], tempRef;

	//Valore del fattore di utilizzazione
	float uTot;

	//Imposto attributo per la coda di richiesta, in modo da usare un messaggio con una dimensione minore rispetto a quello di responso
	struct mq_attr attrReq; 
	attrReq.mq_flags=0;
	attrReq.mq_curmsgs=0;
	attrReq.mq_maxmsg=10;
	attrReq.mq_msgsize=MAX_MSG_SIZE;

	//imposto attributo per la coda di responso
	struct mq_attr attrRes; 
	attrRes.mq_flags=0; 
	attrRes.mq_curmsgs=0; 
	attrRes.mq_maxmsg=100; 
	attrRes.mq_msgsize=MAX_MSG_SIZE*20;

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
		if(mq_timedreceive(idCodaRequest, mess, sizeof(mess), NULL, &time)==-1){
			//printf("DS: Messaggio non Ricevuto!\n");
		}

		else if(strcmp(mess, "Invio")==0){
			printf("MESSAGGIO RICEVUTO!!!\n");

			//Vado a prelevare tutti i parametri per inviare il messaggio corrispondente
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

			//Calcolo del fattore di utilizzazione
			uTot=(uFilter+uActuator+uControl)*100;

			sprintf(risp, "------------CONTROLLER------------\nAvg:%d\nControl:%d\nBuffer:%d, %d, %d, %d, %d\nReference:%d\nFilterWCET: %fus\nActuatorWCET: %fus\nControlWCET: %fus\nFattore di Utilizzo: %f%\n", tempAvg, tempControl, tempBuff[0], tempBuff[1], tempBuff[2], tempBuff[3], tempBuff[4], tempRef, filterWCET, actuatorWCET, controlWCET, uTot);

			if(mq_send(idCodaResponse, risp, strlen(risp)+1, 0)==-1){
				perror("DS: Errore invio messaggio!\n");
			}

		}

		//Imposto un controllo se ho ricevuto un messaggio con una priorità più alta, che viene inserito direttamente all'inizio della coda!
		else if(strcmp(mess, "InvioWCET")==0){
			printf("RICHIESTA PRIORITARIA RICEVUTA!!!\n");

			sprintf(risp, "------------CONTROLLER------------\nValori WCET:\nFilterWCET: %fus\nControlWCET: %fus\nActuatorWCET: %fus\n", filterWCET, controlWCET, actuatorWCET);

			//Invio il messaggio sulla coda!
			if(mq_send(idCodaResponse, risp, strlen(risp)+1, 1)==-1){
				perror("DIAG: Errore invio messaggio prioritario\n"); 
					exit(1);
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

	pthread_exit(NULL);

}
//***************************************************************************************************************************************************************


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
	pthread_mutexattr_t mAttr;

	//Passo alla definizione dell'attributo dei thread e della struttura che imposta la loro priorità
	pthread_attr_t myattr;
	struct sched_param myparam;

	//Dichiaro la variabile della cpu
	cpu_set_t cpu;

	//Funzione di inizializzazione degli attributi di thread e semaforo
	initAttr(&myattr, &mAttr, &cpu);

	//Inizializzazione dei semafori che vengono usati
	pthread_mutex_init(&shared_avg_sensor.lock, &mAttr);
	pthread_mutex_init(&shared_control.lock, &mAttr);
	pthread_mutex_init(&lockBuffer, &mAttr);

	//******IMPOSTAZIONE THREAD*******
	//I thread vengono inizializzati usando la funzione apposita sopra definita
	// ACQUIRE FILTER THREAD
	periodic_thread acquire_filter_th;
	initThread(&acquire_filter_thread, &acquire_filter_th, 50, TICK_TIME, &myparam, &myattr, acquire_filter_loop, &cpu);

	// CONTROL THREAD
	periodic_thread control_th;
	initThread(&control_thread, &control_th, 45, TICK_TIME*BUF_SIZE, &myparam, &myattr, control_loop, &cpu);

	// ACTUATOR THREAD
	periodic_thread actuator_th;
	initThread(&actuator_thread, &actuator_th, 45, TICK_TIME*BUF_SIZE, &myparam, &myattr, actuator_loop, &cpu);

	//ATTIVAZIONE DEL THREAD SEGNALATORE---------------------------------
		periodic_thread segnalatore_th;
		initThread(&segnalatore, &segnalatore_th, 40, 2*TICK_TIME*BUF_SIZE, &myparam, &myattr, segnalo, &cpu);
	//--------------------------------------------------------------------

	//ATTIVAZIONE DEL THREAD DS-------------------------------------------
		periodic_thread ds_thread; 
		initThread(&ds, &ds_thread, 60, TICK_TIME/2, &myparam, &myattr, DefSer, &cpu);
	//--------------------------------------------------------------------

	pthread_attr_destroy(&myattr);
	pthread_mutexattr_destroy(&mAttr);
	
	
	/* Wait user exit commands*/
	while (1) {
   		if (getchar() == 'q') break;
  	}
	keep_on_running = 0;


	//Scelgo di non eseguire qui l'unlink della coda del response in modo che possa continuare ad essere usata anche dal backup, se il controller dovesse crashare
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