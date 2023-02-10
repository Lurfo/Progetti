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
};
static struct _rising_edge rising_edge;

struct _round_time{
	// to do...
	// La struttura deve contenere una variabile per il tempo intercorso tra due posizioni “home” 
	// e un mutex per garantire la mutua esclusione degli accessi 
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
		
}

void* rt_task2(void* parameter){
	// To do...
	// Implementare un task periodico hard real-time
	// Il task deve misurare l'intervallo di tempo intercorso tra due posizioni “home” dell'encoder
	// Selezionare la giusta frequenza del task: 
	//	indipendentemente dalla velocità dell'encoder (75-750 RPM) e dall'istante di avvio del task "rt_task2"
	//	il task deve misurare l'intervallo di tempo TUTTE le volte che l'encoder ritorna in "home"
	
}

void* scope(void* parameter){
	// To do...
	// Implementare un task periodico 
	// 1) Il task legge il valore di conteggio prodotto dal task "rt_task1" e lo stampa a schermo
	// 2) Il task legge l'intervallo di tempo prodotto dal task "rt_task2" e stampa a schermo il valore corrente di RPM dell'encoder
	
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
	
	pthread_t thread_enc;
	
	pthread_attr_t myattr;
	struct sched_param myparam;
	
	
	pthread_mutexattr_t mutex_attr;
	
	/*Mutex initialization*/
	pthread_mutexattr_init (&mutex_attr);
	pthread_mutexattr_setprotocol (&mutex_attr, PTHREAD_PRIO_INHERIT);	// can be PTHREAD_PRIO_NONE, PTHREAD_PRIO_INHERIT, PTHREAD_PRIO_PROTECT
	//pthread_mutexattr_setprioceiling(&mutex_attr, pceiling);		// if PTHREAD_PRIO_PROTECT mutex (set pceiling)
	pthread_mutex_init(&enc_data.lock,&mutex_attr);

	
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
