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
	// to do...
	// La struttura deve contenere una variabile per il conteggio dei fronti di salita 
	// e un mutex per garantire la mutua esclusione degli accessi 
	unsigned int cont;

	pthread_mutex_t lock;

};
static struct _rising_edge rising_edge;

struct _round_time{
	// to do...
	// La struttura deve contenere una variabile per il tempo intercorso tra due posizioni “home” 
	// e un mutex per garantire la mutua esclusione degli accessi 

	pthread_mutex_t lock;

	uint64_t tempo;

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

/***************************** THREADS ************************************/

void* rt_task1(void* parameter){
	// To do...
	// Implementare un task periodico hard real-time
	// Il task deve contare i fronti di salita dell'onda quadra prodotta dall'encoder
	// Selezionare la giusta frequenza del task: 
	//	indipendentemente dalla velocità dell'encoder (75-750 RPM) il task deve contare TUTTI i fronti di salita
	
	//Casting inversio della struttura
	struct periodic_thread *thread = (struct periodic_thread *) parameter;

	//Inizializzo il timer, imposto 0 come parametro in modo che
	//parte subito
	start_periodic_timer(thread, 0);

	//Inizializzazione della variabile lock
	pthread_mutex_lock(&rising_edge.lock);
	rising_edge.cont=0; 
	pthread_mutex_unlock(&rising_edge.lock);

	//Imposto un valore temporaneo per tenere traccia dell'ultimo fronte
	int valore_precedente=0;

	//Ciclo perpetuo che deve eseguire il task
	while (1){
		//Faccio un'attesa 
		wait_next_activation(thread);

		//Accedo alla struttura dell'encoder, per ottenere il fronte dell'encoder
		pthread_mutex_lock(&enc_data.lock);
		
			//Eseguo un controllo sul valore precedente e sul valore attuale
			if(valore_precedente==0 && enc_data.slit==1){
				valore_precedente=1;

				//Eseguo un conteggio
				pthread_mutex_lock(&rising_edge.lock);
					rising_edge.cont++;
				pthread_mutex_unlock(&rising_edge.lock);
			}

			//Eseguo il controllo se sono nel fronte di discesa e modifico il valore precedente
			if(valore_precedente==1 && enc_data.slit==0){
				valore_precedente=0;
			}
		
		//Rilascio il mutex dell'encoder
		pthread_mutex_unlock(&enc_data.lock);
	}
	



}

void* rt_task2(void* parameter){
	// To do...
	// Implementare un task periodico hard real-time
	// Il task deve misurare l'intervallo di tempo intercorso tra due posizioni “home” dell'encoder
	// Selezionare la giusta frequenza del task: 
	//	indipendentemente dalla velocità dell'encoder (75-750 RPM) e dall'istante di avvio del task "rt_task2"
	//	il task deve misurare l'intervallo di tempo TUTTE le volte che l'encoder ritorna in "home"

	//Casting inverso della struttura
	struct periodic_thread *thread = (struct periodic_thread *) parameter;

	start_periodic_timer(thread, 0);

	//inizializzazione della variabile
	pthread_mutex_lock(&round_time.lock);
		round_time.tempo=0;
	pthread_mutex_unlock(&round_time.lock);

	struct timespec tempoHome; 
	struct timespec lastTimeHome;

	//Definizione di due variabili temporane
	int prima_misura=1;
	int ultimo_valore_home=0;
	
	while (1){
		wait_next_activation(thread); 

			//Eseguo un lock sulla struttura dell'encode, dalla quale voglio rispendere il valore della home
		pthread_mutex_lock(&enc_data.lock);
			
			if(enc_data.slit==1 && ultimo_valore_home==0){
				ultimo_valore_home=1;
				
				//Se è la prima volta che eseguo una misurazione, prendo il tempo
				if(prima_misura){
					clock_gettime(CLOCK_REALTIME, &tempoHome);
					prima_misura=0;
				}

				else{
					clock_gettime(CLOCK_REALTIME, &tempoHome);
					//Eseguo il lock sul mutex della struttura per impostare la differenza dei valori
					pthread_mutex_lock(&round_time.lock); 
						round_time.tempo=difference_ns(&tempoHome, &lastTimeHome);
					pthread_mutex_unlock(&round_time.lock);
					//Imposto l'ultimo valore della home letto
					lastTimeHome=tempoHome;
					}
				}

			else if(enc_data.home_slit==0){
				ultimo_valore_home=0;
			}
			
		pthread_mutex_unlock(&enc_data.lock);

	}
	


}

void* scope(void* parameter){
	// To do...
	// Implementare un task periodico 
	// 1) Il task legge il valore di conteggio prodotto dal task "rt_task1" e lo stampa a schermo
	// 2) Il task legge l'intervallo di tempo prodotto dal task "rt_task2" e stampa a schermo il valore corrente di RPM dell'encoder
	
}

void* enc(void* parameter){
	printf("Encoder Start\n");
	
	//Inizializza i valori
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

		printf("%d:\t\t %d %d\n",count,enc_data.slit,enc_data.home_slit);	//DEBUG encoder
		count++;
		
		pthread_mutex_unlock(&enc_data.lock);

	}
	
}

int main(){	

	struct periodic_thread th_e;

	//Definizione delle strutture che mi occorrono per i thread successivi
	struct periodic_thread rt1;
	struct periodic_thread rt2;

	struct periodic_thread fantoccio;
	

	pthread_t thread_enc;

	//Definizione dei thread rt richiesti
	pthread_t thread_rt1;
	pthread_t thread_rt2;
	pthread_t thread_fantoccio;

	
	//NOTA: Uso questi medesimi parametri anche per i thread successivi
	//(andando a reimpostare i valori necessari)
	pthread_attr_t myattr;
	struct sched_param myparam;
	
	
	pthread_mutexattr_t mutex_attr;
	
	/*Mutex initialization*/
	pthread_mutexattr_init (&mutex_attr);
	pthread_mutexattr_setprotocol (&mutex_attr, PTHREAD_PRIO_INHERIT);	// can be PTHREAD_PRIO_NONE, PTHREAD_PRIO_INHERIT, PTHREAD_PRIO_PROTECT
	//pthread_mutexattr_setprioceiling(&mutex_attr, pceiling);		// if PTHREAD_PRIO_PROTECT mutex (set pceiling)
	pthread_mutex_init(&enc_data.lock,&mutex_attr);

	//Inizializzazione del mutex delle due strutture che ho definito sopra
	pthread_mutex_init(&rising_edge.lock, &mutex_attr);
	pthread_mutex_init(&round_time.lock, &mutex_attr);

	
	/*Encoder periodic thread initialization*/
	th_e.index = 1;
	th_e.period = TICK_PERIOD;
	th_e.priority = 11;
	
	/*thread attribute initialization*/
	pthread_attr_init(&myattr);
	pthread_attr_setschedpolicy(&myattr, SCHED_FIFO);
	myparam.sched_priority = th_e.priority;
	pthread_attr_setschedparam(&myattr, &myparam);  
	pthread_attr_setinheritsched(&myattr, PTHREAD_EXPLICIT_SCHED);
	
	pthread_create(&thread_enc, &myattr, enc, &th_e);  


	//INIZIALIZZAZIONE DEL THREAD RT1

		//Inseriemnto dei valori nella struttura
			//Imposto come indice il valore che mi occore
			rt1.index=2;

			//Imposto il periodo
			rt1.period=TICK_PERIOD/2;
			//NOTA: Viene impostato pari alla metà del precedente
			//in modo che determina sia la salita che la discesa del
			//fronte

			rt1.priority=12;
		
		//Imposto la priorità nella struttura myparam 
			myparam.sched_priority=rt1.priority;

		//Modifico la priotià dell'attributo
			pthread_attr_setschedparam(&myattr, &myparam);

	//Posso creare il thread
	pthread_create(&thread_rt1, &myattr, rt_task1, &rt1);



	//INIZIALIZZAZIONE DEL THREAD RT2
		rt2.index=3;
		rt2.period=TICK_PERIOD/2;
		rt2.priority=12;

	//Avendo definito un thread con medesima priorità del precedente, vado a crearlo usando gli stessi attributi di rt1
	pthread_create(&thread_rt2, &myattr, rt_task2, &rt2);


	//INIZIALIZZAZIONE DEL THREAD STANDARD
		fantoccio.index=4;

		//Esegue ad un periodo maggiore rispetto agli altri per stampare un resoconto
		fantoccio.period=TICK_PERIOD*2;

	//Essendo un thread che non ha bisogno di una particolare priorità, lo posso andare a definire senza usare gli attributi
	pthread_create(&thread_fantoccio, NULL, scope, &fantoccio);



	/* Clear attr*/
	pthread_mutexattr_destroy(&mutex_attr);
	pthread_attr_destroy(&myattr);
	
	/* Wait user exit commands*/
	while (1) {
   		if (getchar() == 'q') break;
  	}
  	
  	/* Clear */
  	pthread_mutex_destroy(&enc_data.lock);
	
	//Distuzione dei mutex che ho aggiunto
	pthread_mutex_destroy(&rising_edge.lock);
	pthread_mutex_destroy(&round_time.lock);

  	pthread_kill(thread_enc,0);
  	printf("EXIT!\n");

	return 0;
}
