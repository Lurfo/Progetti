//------------------- CONTROLLER.C ---------------------- 

//Tale file, copia del semplice file originale, contiene anche un thread "watch dog", il cui compito è quello di controllare che il task "primario" esegua senza problemi
//altrimenti provvede a far eseguire i task di backup per verificare che la struttura continui ad eseguire correttamente
//il task che vado ad instanziare, che esegue con un periodo pari al doppio di quello del controller precedente, riceve su una coda di messaggi, il valore a cui si 
//trovava precedentemente il controllore e lo imposta in modo che i vari task possano usarlo 
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

//**********************VIARIABILI********************************************************************************
//Variabile che permette l'esecuzione dei task
static int keep_on_running = 1;

struct shared_int {
	int value;
	pthread_mutex_t lock;
};
static struct shared_int shared_avg_sensor;
static struct shared_int shared_control;

pthread_mutex_t lockBuffer;
int buffer[BUF_SIZE];
int head = 0;

//IMPOSTO UNA VARIABILE GLOBALE CHE FA ATTIVARE I TASK (in base a che il controller sia attivo o meno) DA METTERE SUBITO DOPO IL WHILE, IN OGNI TASK PERIODICO
static int start = 0;

//Mi definisco la variabile globale di riferimento
unsigned int reference = 110;
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
	CPU_SET(0, cpu);

	//Imposto l'attributo in modo che contenga la cpu sulla quale deve eseguire il thread
	if(pthread_attr_setaffinity_np(attr, sizeof(*cpu), cpu)!=0){
		perror("ERORRE IMPOSTAZIONE SCHEDULING NEL BACKUP\n"); 
			exit(1);
	}
	printf("AFFINITY IMPOSTATA\n");

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

//******************************************TASK CHE SIMULANO L'IMPIANTO*********************************************************
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
	pthread_exit(NULL);
}
//**********************************************************************************************************************************************************************

//************************************************TASK AGGIUNTIVI*******************************************************************************************************
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

	pthread_exit(NULL);

}

//Definisco anche nel backup il DS, in modo che esegue quando il controller viene interrotto!
void *DefSer(void *par){

	periodic_thread *th = (periodic_thread *)par;

	//Imposto il timer in modo che parta da subito!
	start_periodic_timer(th, 0);

	struct timespec time;

	char mess[MAX_MSG_SIZE];

	char risp[MAX_MSG_SIZE*20];

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

		if(start){//Prendo il tempo attuale e gli sommo il periodo del server
			clock_gettime(CLOCK_MONOTONIC, &time);

			timespec_add_us(&time, th->period);

			//Eseguo la receive temporizzata del messaggio
			if(mq_timedreceive(idCodaRequest, mess, sizeof(mess), NULL, &time)==-1){
				//printf("DS: Messaggio non Ricevuto!\n");
			}

			else if(strcmp(mess, "Invio")==0){
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

				sprintf(risp, "------------BACKUP------------\nAvg:%d\nControl:%d\nBuffer:%d, %d, %d, %d, %d\nReference:%d\n", tempAvg, tempControl, tempBuff[0], tempBuff[1], tempBuff[2], tempBuff[3], tempBuff[4], tempRef);

				if(mq_send(idCodaResponse, risp, strlen(risp)+1, 0)==-1){
					perror("DS: Errore invio messaggio responso!\n");
				}
			
			}

			else if(strcmp(mess, "InvioWCET")==0){

				printf("MESSAGGIO PRIORITARIO RICEVUTO \n");

				sprintf(risp, "------------BACKUP------------\nERRORE: Calcolo del WCET non disponibile nel backup, ripristinare il controllore principale\n"); 
				
				if(mq_send(idCodaResponse, risp, strlen(risp)+1, 1)==-1){
					perror("DS: Errore invio messaggio responso!\n");
					exit(1);
				}

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
//**********************************************************************************************************************************************************************

int main(void)
{
	printf("The BACKUP is STARTED! [press 'q' to stop]\n");
 	
	pthread_t acquire_filter_thread;
    pthread_t control_thread;
    pthread_t actuator_thread;

	//Thread di guardia
	pthread_t guardia;

	//Definizione del thread sel DS
	pthread_t ds;

	//Attributo per i thread e per i semafori
	pthread_mutexattr_t mAttr;
	pthread_attr_t myattr;
	struct sched_param myparam;

	//Valore della cpu
	cpu_set_t cpu;
	
	//Inizializzazione degli attributi tramite apposita funzione
	initAttr(&myattr, &mAttr, &cpu);

	//Inizializzazione dei semafori, impostando attributi
	pthread_mutex_init(&shared_avg_sensor.lock, &mAttr);
	pthread_mutex_init(&shared_control.lock, &mAttr);
	pthread_mutex_init(&lockBuffer, &mAttr);

	//***********IMPOSTAZIONE THREAD*************
	//Usiamo la funzione apposita sopra definita

	// ACQUIRE FILTER THREAD
	periodic_thread acquire_filter_th;
	initThread(&acquire_filter_thread, &acquire_filter_th, 50, TICK_TIME, &myparam, &myattr, acquire_filter_loop, &cpu);

	// CONTROL THREAD
	periodic_thread control_th;
	initThread(&control_thread, &control_th, 45, TICK_TIME*BUF_SIZE, &myparam, &myattr, control_loop, &cpu);

	// ACTUATOR THREAD
	periodic_thread actuator_th;
	initThread(&actuator_thread, &actuator_th, 45, TICK_TIME*BUF_SIZE, &myparam, &myattr, actuator_loop, &cpu);

	//CREAZIONE DEL THREAD DI GUARDIA--------------------------------------
		periodic_thread guardia_th; 
		initThread(&guardia, &guardia_th, 40, 2*TICK_TIME*BUF_SIZE, &myparam, &myattr, guard, &cpu);
		//NOTA: Ha il periodo più grande quindi, secondo RM, ha la priorità minore!
	//--------------------------------------------------------------------

	//ATTIVAZIONE DEL THREAD DS-------------------------------------------
		periodic_thread ds_thread; 
		initThread(&ds, &ds_thread, 60, TICK_TIME/2, &myparam, &myattr, DefSer, &cpu);
		//Impostato come il task che ha la massima priorità, quindi il periodo più piccolo!!!
	//--------------------------------------------------------------------

	pthread_attr_destroy(&myattr);
	pthread_mutexattr_destroy(&mAttr);
	
	
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

	//Unlink delle code del DS
	if(mq_unlink(DS_QUEUE_REQUEST)==-1){
		perror("MAIN: Errore unlink coda RichiestaDS\n"); 
			exit(1);
	}

	if(mq_unlink(DS_QUEUE_RESPONSE)==-1){
		perror("MAIN: Errore unlink coda RispostaDS\n");
		exit(1);
	}

 	printf("The controller is STOPPED\n");
	return 0;
}




