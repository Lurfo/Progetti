#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define TICK_PERIOD 5000
#define NSEC_PER_SEC 1000000000ULL

//Di seguito, faccio una modifica al programma completo in modo da andare a calcolar lo slack time dei vari processi, andando a creare un ultimo thread che ha
//il compito di andare a controllare questi valori e verificare il tempo medio

//Per il calcolo dello slack, mi definisco due strutture che mantengono proprio questa differenza di tempo!
struct slack{
	//Mantiene la differenza tra il finish time e la deadline!
	unsigned long int diff;

	pthread_mutex_t lock;
};
//Mi definisco due variabili globali per le strutture
struct slack slackRT1;
struct slack slackRT2;

/* periodic thread */
struct periodic_thread {

	int index;

	struct timespec r;

	int period;

	int wcet;

	int priority;
};

/* encoder */
struct enc_str
{
	unsigned int slit;		//valori oscillanti tra 0 e 1
	unsigned int home_slit;	//1 se in home, 0 altrimenti
	pthread_mutex_t lock;
};
static struct enc_str enc_data;

struct _rising_edge{
	//Conteggio fronti di salita
	int conteggio;

	//Mutex per mutua esclusione
	pthread_mutex_t lock;
	
};
static struct _rising_edge rising_edge;

struct _round_time{

	//Misura il tempo trascorso in home, uso un valore intero, in quanto esprimo il valore in nanosecondi!
	unsigned long int diff;

	//Mutex per la modifica
	pthread_mutex_t lock;

};
static struct _round_time round_time;


/***************************** Functions ************************************/

static inline void timespec_add_us(struct timespec *t, uint64_t d)
{
    d *= 1000;
    t->tv_nsec += d;
    t->tv_sec += t->tv_nsec / NSEC_PER_SEC;
    t->tv_nsec %= NSEC_PER_SEC;
}

void wait_next_activation(struct periodic_thread * thd)
{
    clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &(thd->r), NULL);
    timespec_add_us(&(thd->r), thd->period);
}

void start_periodic_timer(struct periodic_thread * thd, uint64_t offs)
{
    clock_gettime(CLOCK_REALTIME, &(thd->r));
    timespec_add_us(&(thd->r), offs);
}

// la funzione "difference_ns" calcola la differenza tra due timespec (ts1 - ts2) e restituisce il risultato in nanosecondi (di tipo unsigned long int)
unsigned long int difference_ns(struct timespec *ts1, struct timespec *ts2){
	long int diff_sec, diff_nsec;
	diff_sec =(ts1->tv_sec - ts2->tv_sec);
	diff_nsec = (ts1->tv_nsec - ts2->tv_nsec);
	return diff_sec*NSEC_PER_SEC + diff_nsec;
}


//ATTENZIONE: Per il calcolo dello slack, devo definire una funzione per il confronto dei due valori
//La seguente verifica se il primo valore è maggiore del sedondo
int maggiore(struct timespec *t1, struct timespec *t2){
	//confronto prima i seocndi
	if(t1->tv_sec>t2->tv_sec){
		return 1;
	}
	
	//Se i secondi sono uguali, confronto i nanosecondi!
	if(t1->tv_sec==t2->tv_sec && t1->tv_nsec>t2->tv_nsec){
		return 1;
	}

	//A questo punto se restituisco 0, i confronti di prima sono falliti ed il primo argomento è minore del secondo
	else{
		return 0;
	}

}



/***************************** THREADS ************************************/

void* rt_task1(void* parameter){
	
	// To do...
	// Implementare un task periodico hard real-time
	// Il task deve contare i fronti di salita dell'onda quadra prodotta dall'encoder
	// Selezionare la giusta frequenza del task: 
	//	indipendentemente dalla velocità dell'encoder (75-750 RPM) il task deve contare TUTTI i fronti di salita

	//Casting inverso del parametro
	struct periodic_thread *vals = (struct periodic_thread *) parameter;

	//Imposto la variabile che mantiene il precendete fronte di salita
	int prevFront=0;
	//Mantengo anche una variabile per l'attuale fronte di salita
	int now; 

	//Imposto una variabile che mantiene il tempo di fine del task
	struct timespec finishTime;

	/*
	printf("Ciao, sono il thread che conta i fronti di salita\n"); 
	printf("Ho una priorità: %d, indice: %d, periodo: %d", vals->priority, vals->index, vals->period);
	*/

	//Chiamo la funzione che imposta l'istante iniziale di attivazione del mio thread
	start_periodic_timer(vals, TICK_PERIOD/2);

	//Avvio il ciclo infinito del thread
	while (1){

		//Avvio la funzione che attende la prossima attivazione
		wait_next_activation(vals);

		//A questo punto devo verificare se sono in un fronte di salita o meno!
		//Mi vado prima a salvare il valore in una variabile apposita!
		//Salvandomi il valore attuale del fronte, posso anche lasciare prima il mutex!
		pthread_mutex_lock(&enc_data.lock); 

			now=enc_data.slit;	

			//Vado a varificare se effettuare il conteggio o meno
			if(now!=prevFront && prevFront==0){
				//Solo in questo caso, vado ad aumentare il conteggio della struttura apposita
				pthread_mutex_lock(&rising_edge.lock); 
					rising_edge.conteggio++; 
				pthread_mutex_unlock(&rising_edge.lock);
			}

			//Modifico il valore del precedente valore con quello attualmente letto
			prevFront=now;

		pthread_mutex_unlock(&enc_data.lock);

		//Dopo aver eseguito tutte le funzioni che mi occorrono, vado ad eseguire il calcolo
		//In questo caso, vado ad usare il clock realtime, Poichè conta a partire dal momento di esecuzione del thread!
		clock_gettime(CLOCK_REALTIME, &finishTime);
		//Eseguo una comparazione e vedo se la deadline supera il secondo valore
		if(maggiore(&vals->r, &finishTime)){
			//Se questo è vero, posso andare a calcolare lo slack
			pthread_mutex_lock(&slackRT1.lock); 
				slackRT1.diff = difference_ns(&vals->r, &finishTime);
			pthread_mutex_unlock(&slackRT1.lock);
		}


	}
		
		
}

void* rt_task2(void* parameter){
	// To do...
	// Implementare un task periodico hard real-time
	// Il task deve misurare l'intervallo di tempo intercorso tra due posizioni “home” dell'encoder
	// Selezionare la giusta frequenza del task: 
	//	indipendentemente dalla velocità dell'encoder (75-750 RPM) e dall'istante di avvio del task "rt_task2"
	//	il task deve misurare l'intervallo di tempo TUTTE le volte che l'encoder ritorna in "home"

	struct periodic_thread *vals = (struct periodic_thread *) parameter;

	
	/*
	printf("Ciao, sono il thread che conta il tempo in home!\n"); 
	printf("Ho una priorità: %d, indice: %d, periodo: %d", vals->priority, vals->index, vals->period);
	*/

	//Valoe da cui parte il conteggio e valore di arrivo
	struct timespec start, arrival, finishTime;

	//Valore della differenza
	unsigned long int diff; 

	//valore precedente e attuale
	int prev=0, now=0;
	
	//Utilizzo un valore che mi verifica se sono per la prima volta nella
	//home
	int firstTime=1; 

	//Faccio partire il timer
	start_periodic_timer(vals, TICK_PERIOD/2);

	while (1){
		
		//eseguo attivazione del prossimo periodo
		wait_next_activation(vals);

		//Verifico se sono nella home, salvandomi l'ultimo valore
		pthread_mutex_lock(&enc_data.lock);
			now=enc_data.home_slit;
		

			//Controllo se siamo sul fronte di salita della home
			if(now!=prev && prev==0){
				//Controllo se è la prima misura che sto eseguendo
				if(firstTime){
					//Prendo il tempo
					clock_gettime(CLOCK_MONOTONIC, &start);

					//Non è più la prima misura
					firstTime=0;
				}

				else{
					//Se non è la prima misura, posso eseguire un campione del tempo
					//ed effettuare la differenza
					clock_gettime(CLOCK_MONOTONIC, &arrival);

					diff=difference_ns(&arrival, &start);

					pthread_mutex_lock(&round_time.lock);
						round_time.diff=diff;
					pthread_mutex_unlock(&round_time.lock);

					//Faccio in modo che il valore che ho appena letto, sia corrispondente
					//al nuovo valore di start
					start=arrival;

				}
			}

			//Salvo il valore della precedente lettura del fronte
			prev=now;

		pthread_mutex_unlock(&enc_data.lock);


		//Dopo aver eseguito tutte le funzioni che mi occorrono, vado ad eseguire il calcolo
		clock_gettime(CLOCK_REALTIME, &finishTime);
		//Eseguo una comparazione e vedo se la deadline supera il secondo valore
		if(maggiore(&vals->r, &finishTime)){
			//Se questo è vero, posso andare a calcolare lo slack
			pthread_mutex_lock(&slackRT2.lock); 
				slackRT2.diff = difference_ns(&vals->r, &finishTime);
			pthread_mutex_unlock(&slackRT2.lock);
		}



	}
	
}


//Vado a definire la funzione del thread che mi deve conteggiare i vari slack
void *diagnostic(void *par){

	struct periodic_thread *val = (struct periodic_thread *) par;

	unsigned long int avg;

	int cnt=0;

	//Vado ad impostare la prossima attivazione
	start_periodic_timer(val, TICK_PERIOD*100);

	while(1){
		
		wait_next_activation(val);

		pthread_mutex_lock(&slackRT1.lock); 
			pthread_mutex_lock(&slackRT2.lock);

			avg += (slackRT1.diff+slackRT2.diff)/2000; //Considero il valore in microsecondi

			pthread_mutex_unlock(&slackRT2.lock);
		pthread_mutex_unlock(&slackRT1.lock);

		cnt++;

		if(cnt==100){
			
			avg=avg/cnt;

			printf("***SLACKTIME: %ld****\n", avg);

			cnt = 0;
			
		}

	}


}

void* scope(void* parameter){
	// To do...
	// Implementare un task periodico 
	// 1) Il task legge il valore di conteggio prodotto dal task "rt_task1" e lo stampa a schermo
	// 2) Il task legge l'intervallo di tempo prodotto dal task "rt_task2" e stampa a schermo il valore corrente di RPM dell'encoder

	int conteggio=0; 
	float val=0; 

	//Imposto la  variabile che mi esegue il conteggio in rotazioni per minuto
	unsigned int rmp=0;

	struct periodic_thread  *vals = (struct periodic_thread *) parameter;

	start_periodic_timer(vals, TICK_PERIOD*100);

	while (1){

		wait_next_activation(vals);

		pthread_mutex_lock(&rising_edge.lock);
			conteggio = rising_edge.conteggio;
		pthread_mutex_unlock(&rising_edge.lock);

		pthread_mutex_lock(&round_time.lock);
			val = round_time.diff /1000; //Divido per 1000, in modo da esprimere la differenza in microsecondi
		pthread_mutex_unlock(&round_time.lock);


		//Vado a contare le rotazioni per minuto, andando a considerare il numero di microseocndi che sono presenti in un minuto e li vado poi a dividere per il valore
		//che ho ottenuto
		rmp = (unsigned int)(60*1000000/val);

		printf("Valore di conteggio del thread RT1: %d\n", conteggio); 
		printf("Valore della differenza di tempo di RT2: %u\n", rmp);

	}
	
	
}

void* enc(void* parameter){

	printf("Encoder Start\n");
	
	pthread_mutex_lock(&enc_data.lock);
	
	enc_data.slit = 0;
	enc_data.home_slit = 0;
	
	pthread_mutex_unlock(&enc_data.lock);
	
	
	unsigned int count = 0;
	unsigned int slit_count = 0;		
	unsigned int prev_slit = 0;
	
	/* Randomized period (75-750 RPM) */
	srand(time(NULL));
	unsigned int semi_per = (rand() % 10) + 1;
	
	struct periodic_thread *th = (struct periodic_thread *) parameter;
	
	start_periodic_timer(th,TICK_PERIOD);

	/*printf("Ciao, sono il thread principale\n"); 
	printf("Ho una priorità: %d, indice: %d, periodo: %d", th->priority, th->index, th->period);
	*/

	
	while (1) {
		wait_next_activation(th);
		
		pthread_mutex_lock(&enc_data.lock);
		
		prev_slit = enc_data.slit;
		if (count%semi_per == 0) {
			enc_data.slit++;
			enc_data.slit%=2;	
		}

		if (prev_slit==0&&enc_data.slit==1) 					//fronte di salita
			slit_count=(++slit_count)%8;

		if (slit_count==0) enc_data.home_slit=enc_data.slit;
		else enc_data.home_slit=0;

		//printf("%d:\t\t %d %d\n",count,enc_data.slit,enc_data.home_slit);	//DEBUG encoder
		count++;
		
		pthread_mutex_unlock(&enc_data.lock);

	}   
	
}

void init(pthread_attr_t * attr, pthread_mutexattr_t *mutex_attr){

	//Inizializzazione dell'attributo
	pthread_attr_init(attr);
	pthread_attr_setschedpolicy(attr, SCHED_FIFO);
	pthread_attr_setinheritsched(attr, PTHREAD_EXPLICIT_SCHED);
	
	/*Mutex initialization*/
	pthread_mutexattr_init (mutex_attr);
	pthread_mutexattr_setprotocol (mutex_attr, PTHREAD_PRIO_INHERIT);	// can be PTHREAD_PRIO_NONE, PTHREAD_PRIO_INHERIT, PTHREAD_PRIO_PROTECT
	//pthread_mutexattr_setprioceiling(&mutex_attr, pceiling);		// if PTHREAD_PRIO_PROTECT mutex (set pceiling)

	//Inizializzazione dei semafori nelle strutture dichiarate
	pthread_mutex_init(&enc_data.lock, mutex_attr);

	pthread_mutex_init(&round_time.lock, mutex_attr); 
	pthread_mutex_init(&rising_edge.lock, mutex_attr);

	pthread_mutex_init(&slackRT1.lock, mutex_attr); 
	pthread_mutex_init(&slackRT2.lock, mutex_attr);

}


void createThread(pthread_t *thread, struct periodic_thread *th, pthread_attr_t *attr, void *startingRoutine, int priority, int period){
	
	static int i=0;


	//Definizione struttura per impostare la priotià
	struct sched_param myparam;

	//Impostazioni degli attrubuti del thread
	th->index=i++;
	th->period=period;
	th->priority=priority;
	

	//Impostazione della priorità
	myparam.sched_priority=th->priority;

	//Impostazione della priorità nell'attributo
	pthread_attr_setschedparam(attr, &myparam);

	//Creazione del thread 
	if(pthread_create(thread, attr, startingRoutine, th)!=0){
		printf("Errore nella creazione del thread!\n");
	}

	printf("thread creato!\n");



}


int main(){	

	struct periodic_thread th_e;
	
	//Strutture per  thread da dichiarare
	struct periodic_thread th_re; 
	struct periodic_thread th_rt;
	struct periodic_thread th_bd;

	struct periodic_thread th_sl;

	pthread_t thread_enc;

	//pthread type
	pthread_t thread_re; 
	pthread_t thread_rt;
	pthread_t buddy;
	pthread_t slack;
	
	//Dichiarazione attributo dei thread
	pthread_attr_t myattr;

	pthread_mutexattr_t mutex_attr;

	init(&myattr, &mutex_attr);

	//Struttura per definire la priorità del thread
	struct sched_param myparam;
	
	//Chiamata della funzione per impostare il primo thread
	//printf("Creazione thread\n");
	createThread(&thread_enc, &th_e, &myattr, enc, 11, TICK_PERIOD);

	//Il thread che conta i fronti di salita deve avere il periodo uguale alla metà del periodo dell'altro, che gli permette di contare i fronti di salita e di
	//discesa del segnale
	//Posso rendermi conto ogni qual volta esiste l'incremento!
	//printf("Creazione thread\n");
	createThread(&thread_re, &th_re, &myattr, rt_task1, 12, TICK_PERIOD/2);

	//Imposto il thread che conta quanto tempo ho passato in home!
	//In particolare, questo ha il medesimo periodo e la stessa priorità dell'altro task periodico con cui ho a che fare
	//Questo gli consente di andare a contare ogni qual volta sto avendo a che fare con un fronte di salita o un fronte di discesa!
	//printf("Creazione thread\n");
	createThread(&thread_rt, &th_rt, &myattr, rt_task2, 12, TICK_PERIOD/2);

	//Creazione del thread buddy che conta i valori che sono stati prodotti
	createThread(&buddy, &th_bd, &myattr, scope, 10, 2*TICK_PERIOD);

	createThread(&slack, &th_sl, &myattr, diagnostic, 10, TICK_PERIOD*2);
	 
	
	/* Clear attr*/
	pthread_mutexattr_destroy(&mutex_attr);
	pthread_attr_destroy(&myattr);
	
	/* Wait user exit commands*/
	while (1) {

   		if (getchar() == 'q') break;
		   
  	}
  	
  	/* Clear */
  	pthread_mutex_destroy(&enc_data.lock);
  	pthread_kill(thread_enc,0);
  	printf("EXIT!\n");

	return 0;
}
