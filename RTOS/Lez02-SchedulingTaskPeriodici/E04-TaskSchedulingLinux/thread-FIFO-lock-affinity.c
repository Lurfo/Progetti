//Per ottenere un programma ancora più corretto dal punto di vista funzionale, che non ha dei comportamenti inattesi, posso andare
//ad effettuare due accorgimenti importanti: 

// 	-Limitare l'uso dei pagefault, usando apposite funzioni di libreria che mi assegnano, in modo permanenete, una zona di memoria
//  che non può essere spostata
//		NOTA: La strategia che viene qui usata è quella del "prefaulting" si accede alla memoria nella fase di inizializzazione, in modo
//		che tutti i pagafault vegano gestiti inizialmente, così non ho "disturbi" durante l'esecuzione del programma!

//	-Impostare un'AFFINITA' della CPU: Faccio in modo che il thread esegua sempre sulla medesima CPU 
//	(Questo è vantaggioso in quanto permette di fare in modo che la cache di una CPU non venga INVALIDATA, a causa del fatto che
//	il thread potrebbe rimbalzare da una CPU all'altra!)
//		NOTA: Il fatto che la CPU venga invalidata rappresenta un grave problema alle prestazioni, poichè occorre eliminare tutti
// 		i dati che essa contiene e riportare in essa nuovi dati, facendo aumentare notevolmente i tempi di attesa
//RICORDA:L'affinità deve essere impostata per ogni thread di cui si compone il programma!!!

//Per andare ad impostare l'affinità di un thread tramite codice, devo andare a definire quanto segue, in modo da andare a 
//utilizzare una serie di macro
#define _GNU_SOURCE
//(Oltre questo, bisogna comunque utilizzare le funzioni che sono contenute nella libreria pthread)
//Questo però non basta, occorre usare una serie di funzioni che sono contenute nella libreria seguente
#include <sched.h>
//Nella libreria, devo andare ad utilizzare le funzioni di CPU_SET

#include <sys/time.h>
#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>

//Vado ad usare nel programma la mlockall(), in modo da andare a evitare la presenza di pagefault
//occorre utilizzare la libreria corretta contente tale funzione, cioè quella del memory managment
#include <sys/mman.h>


struct periodic_thread {
	int index;
	struct timespec r;
	int period;
	int wcet;
	int priority;
};

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
 
int main()
{
	pthread_t thread_1;

	struct periodic_thread th1;
	th1.index = 1;
	th1.period = 5000;
	th1.priority = 11;
	
	struct sched_param myparam;
	pthread_attr_t myattr;
	
	pthread_attr_init(&myattr);
  
    pthread_attr_setschedpolicy(&myattr, SCHED_FIFO);
    myparam.sched_priority = th1.priority;
    pthread_attr_setschedparam(&myattr, &myparam);  
    pthread_attr_setinheritsched(&myattr, PTHREAD_EXPLICIT_SCHED);
	
    pthread_create(&thread_1, &myattr, run, &th1);  

	//Prima della creazione del secondo thread, vado ad impostare anche la CPU sulla quale deve eseguire
	//Mi serve un particolare tipo di parametro da utilizzare
	cpu_set_t cpuNum;

	//A questo punto, devo inizializzare il parametro utilizzando una funzione apposita, da quelle che sono contenute nella libreria
	//"-sched.h"
	//Alla quale devo passare, per riferimento, il valore che mi interessa
	CPU_ZERO(&cpuNum);

	//Imposto a quale CPU, si riferisce la variabile che ho definito, ad esempio scelgo di passargli la 0
	CPU_SET(0, &cpuNum);

	//Quindi vado a richiamare la funzione che assegna il thread alla CPU, andandogli a passare differenti argomenti:
	/*
		-Id del thread
		-Dimensione della variabile cpu_set_t
		-La variabile che ho definito, passata per riferimento
	*/
	pthread_setaffinity_np(thread_1, sizeof(cpu_set_t), &cpuNum);
    
    pthread_t thread_2;

	struct periodic_thread th2;
	th2.index = 2;
	th2.period = 10000;
	th2.priority = 10;
	
	myparam.sched_priority = th2.priority;
	pthread_attr_setschedparam(&myattr, &myparam);
	
	pthread_create(&thread_2, &myattr, run, &th2);

	//ATTENZIONE: La medesima cosa che ho fatto per il thread 1, devo anche andare a farla per il thread 2
	//siccome voglio che anche questo thread esegua sulla stessa CPU del precedente, posso usare la medesima variabile
	//Devo solo andare a richiamare la funzione di setaffinity
	pthread_setaffinity_np(thread_2, sizeof(cpu_set_t), &cpuNum);


    pthread_attr_destroy(&myattr);


	//A questo punto, dopo aver inizializzato i vari thread, posso andare ad usare la lock all
	//NOTA: Vado ad inserire la funzione subito dopo l'inizializzazione dei thread, in questo modo, sono sicuro di aver caricato in
	//memoria tutti i dati che mi interessano (posso quindi dire che pagine caricate non devono essere più spostate, dopo che sono)
	//state spostate nella memoria

	//Questa funzione, prende in ingresso solo un flag (che possono anche essre combinati tra loro), ognuno dei quali ha un funzionamento
	//specifico
	//NOTA: L'uso di questa funzione risulta essere una buona norma di programmazione quando ho a che fare con dei thread Real Time
	mlockall(MCL_CURRENT|MCL_FUTURE);

	

	while (1) {
   		if (getchar() == 'q') break;
  	}

	//ATTENZIONE: Alla terminazione del programma, posso andare ad usare la funzione unlockall, che mi permette di liberare la memoria
	//occupata. 
	//TUTTAVIA: Non è necessario utilizzarla in quanto alla terminazione del programma, la memoria precedentemente occupata dal processo
	//viene comunque liberata
	munlockall();

    return 0;
}


//NOTE FINALI:
/* 
Avendo anche impostato i thread sulla medesima CPU, ha senso dire che effettivamente stanno eseguendo secondo una regola di scheduling
RM, nei casi precedenti siccome non avevo controllo della CPU sulla quale questi venivano schedulati, non potevo fare alcuna assunzione
sulla modalità di schedulazione
*/
