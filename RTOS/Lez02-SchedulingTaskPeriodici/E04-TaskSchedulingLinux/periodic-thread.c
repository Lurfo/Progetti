#include <sys/time.h>
#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>

//Questo programma prevede la creazione di una serie di thread periodici

//Quandi al thread devo passare più di un argomento, la strada da seguire è quella di inserire tali valori all'interno di una
//struttura apposita, che viene poi inviata al thread come se stessi inviando un unico argomento
struct periodic_thread {
	//Valore che posso usare come indice di un thread
	int index;

	//Struttura che mantiene il tempo iniziale usato come riferimento
	struct timespec r;

	//Valore del periodo
	int period;

	//Valore che mi mantiene il WCET del thread
	int wcet;

	//Valore della priorità del thread, che nel caso di questo programma non verrà considerato
	int priority;
};


//ATTENZIONE: Sto considerando un thread periodico, che esegue le medesime funzionalità dei task periodici analizzati nella
//"Lez01", come definito anche in questa lezione, il meccanismo usato per definire la periodicità è quello che si ottiene
//facendo uso della clock_nanosleep
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


//STARTING ROUTINE DEL THREAD
//Il cui comportamento risulta essere simile al corpo del job del task periodico
void * run (void * par) {

	//Casting inverso del parametro di ingresso del thread
	struct periodic_thread *th = (struct periodic_thread *) par;
	
	//Imposto i valori che mi occorrono per andare ad utilizzare la nanosleep
	//NOTA BENE: Alla funzione passo direttamente la struttura, sarà compito della struttura inserire nel campo corrispondente
	//della struttura il valore dell'istante iniziale
	start_periodic_timer(th,2000000);
    

	//Le seguenti righe rappresentano il corpo del job così come descritto negli esempi precedenti
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

int main()
{
	pthread_t thread_1;

	//Vado a dichiarare la struttura contenete gli argomenti del thread ed inzializzo i valori, al suo interno, che mi occorono
	struct periodic_thread th1;
	th1.index = 1;
	th1.period = 5000;
	
	//Proseguo con la creazione del thread
    pthread_create(&thread_1, NULL, run, &th1); 
    
	while (1) {
   		if (getchar() == 'q') break;
  	}

    return 0;
}


