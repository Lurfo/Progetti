#include <sys/time.h>
#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>

//IMPOSTARE SCHEDULING E PRIOTIA' PER UN THREAD:
//Come fatto per il processo, la medesima cosa, può essere fatta anche per un thread
//tutto questo è possibile, andando ad eseguire delle funzioni SU DI UN ATTRIBUTO, che viene poi fornito al thread al momento
//della creazione

//Struttura contente informazioni da inviare al thread
struct periodic_thread {
	int index;
	struct timespec r;
	int period;
	int wcet;

	//In questo caso, la priorità deve essere utilizzata
	int priority;
};

//Le funzioni di seguito risultano essere analoghe al caso del semplice thread periodico
#define NSEC_PER_SEC 1000000000ULL
static inline void timespec_add_us(struct timespec *t, uint64_t d)
{
    d *= 1000;
    t->tv_nsec += d;
    t->tv_sec += t->tv_nsec / NSEC_PER_SEC;
    t->tv_nsec %= NSEC_PER_SEC;
}

void wait_next_activation(struct periodic_thread * thd)
{
    clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &(thd->r), NULL);
    timespec_add_us(&(thd->r), thd->period);
}

void start_periodic_timer(struct periodic_thread * thd, uint64_t offs)
{
    clock_gettime(CLOCK_MONOTONIC, &(thd->r));
    timespec_add_us(&(thd->r), offs);
}

void * run (void * par) {
	struct periodic_thread *th = (struct periodic_thread *) par;
	
	start_periodic_timer(th,2000000);
    
    int cnt = 0;
    uint64_t start = 0;
    uint64_t t;
    struct timeval tv;
    
    while(1) {
        wait_next_activation(th);
        if (start == 0) {
        gettimeofday(&tv, NULL);
			start = tv.tv_sec * 1000ULL + tv.tv_usec / 1000ULL;
    	}
        
    	gettimeofday(&tv, NULL);
    	t = tv.tv_sec * 1000ULL + tv.tv_usec / 1000ULL;
    	if (cnt && (cnt % 100) == 0) {
        	printf("th %d: Avg time: %f\n", th->index, (double)(t - start) / (double)cnt);
    	}
    	cnt++;
    }
}
 
//NEL MAIN SI HANNO DEI CAMBIAMENTI IMPORTANTI
int main()
{
	pthread_t thread_1;

	//Inserisco nella struttura i parametri fondamentali del thread 1
	struct periodic_thread th1;
	th1.index = 1;
	th1.period = 5000;
	th1.priority = 11;
	
	//Occorre sempre usare la struttura apposita "sched_param" per impostare ciò che occorre
	struct sched_param myparam;
	pthread_attr_t myattr;
	
	pthread_attr_init(&myattr);
  
	//Imposto la policy di scheduling all'attributo
    pthread_attr_setschedpolicy(&myattr, SCHED_FIFO);
	//Imposto la priorità nella struttura e la utilizzo per impostare, nell'attributo gli appositi parametri di scheduling
    myparam.sched_priority = th1.priority;
    pthread_attr_setschedparam(&myattr, &myparam);  

	//ATTENZIONE: Utilizzo questa funzione per impostare l'attributo in modo tale che il thread venga schedulato secondo le indicazioni
	//che io ho fornito
	//INFATTI: Non usando questa funzione, lo scheduler esegue il thread ereditando le informazioni dal thread principale
	//quello di dafault indica proprio che lo scheduler deve ereditare tutte queste informazioni
    pthread_attr_setinheritsched(&myattr, PTHREAD_EXPLICIT_SCHED);
	
	//Creo il thread fornendogli l'attributo creato
    pthread_create(&thread_1, &myattr, run, &th1);  
    
    pthread_t thread_2;

	//Allo stesso modo imposto una serie di parametri per il thread 2
	//UNA NOTA: Al thread 2, assegno una priorità minore, in quanto ha un periodo maggiore, vuol dire che sto schedulando 
	//i thread utilizzando il meccanismo di rate monotonic!
	struct periodic_thread th2;
	th2.index = 2;
	th2.period = 10000;
	th2.priority = 10;
	
	//SICCOME: Il thread 2 ha solo la priorità differente rispetto al primo, posso usare il medesimo attributo definito sopra, andando
	//a modificare opportunamente il valore della priorità, impostando quello del thread 2
	myparam.sched_priority = th2.priority;
	pthread_attr_setschedparam(&myattr, &myparam);
	
	pthread_create(&thread_2, &myattr, run, &th2);
	
    pthread_attr_destroy(&myattr);
 
	while (1) {
   		if (getchar() == 'q') break;
  	}

    return 0;
}

//ATTENZIONE: Come nel caso del singolo task, anche questo programma deve essere eseguito con "sudo" usando i privilegi di
//root, altrimenti le funzioni che ho utilizzato per impostare tutti gli attributi vengono ignorate!!!
