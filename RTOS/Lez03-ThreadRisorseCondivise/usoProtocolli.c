//PER RISOLVERE L'INVERSIONE: Vado ad usare i protocolli di Priority Inheritance e Priority ceiling, che risultano essere già "inclusi"
//nella libreria POSIX!!!
//Possono essere sfruttati andando ad impostare appositi attributi sul semaforo, mediante una funzione apposita!
//Così facendo, andiamo a ritardare l'esecuzione del task che ha priorità media




//UNA NOTA: Il PC che utilizza Linux, è l'immediate Priority Ceiling, che causa alcuni bloccaggi anticipati, somiglia dunque all'highest
//priority lock, ma risulta essere più semplice da implementare rispetto alla normale versione del protocollo

#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>

//NOTA BENE: Questa è una variabile globale che viene utilizzata SOLTANTO dal thread a maggiore e quello a minore priorità
//non viene quindi toccata dal thread di priorità intermedia
//Essendo questa una variabile globale allora è liberamente accessibile dai thread!
int shared;

//Dichiarazione della variabile mutex
pthread_mutex_t mutex;

void * run_high(void * wcet) {
	
	int i = 1;
	int j;
	int a = 13, b = 17;
	usleep(1);
	printf("Thread High about to lock...\n");
	//simulating a long critical section

    //Prima della lettura e della modifica della variabile, chiamo il lock sul mutex
    pthread_mutex_lock(&mutex);

	while (i <= (long)wcet) {

		int sh = shared;
		for(j=0; j<100000; j++) a*=b;
		shared = sh+1;
		if (i%100==0) printf("Thread High, shared=%d\n",shared);

		i++;
	}

    //Dopo aver terminato le mie operazioni, vado a chiamare la funzione di unlock
    pthread_mutex_unlock(&mutex);
}

void * run_low(void * wcet) {
	
	int i = 1;
	int j;
	int a = 13, b = 17;
	printf("Thread Low about to lock...\n");
	//simulating a long critical section

    //Anche per questo thread, vado ad impostare le funzioni sul semaforo, per poter entrare nella sezione critica
    pthread_mutex_lock(&mutex);

	while (i <= (long)wcet) {
		int sh = shared;
		for(j=0; j<100000; j++) a*=b;
		shared = sh+1;
		if (i%100==0) printf("Thread Low, shared=%d\n",shared);
		i++;
	}	

    pthread_mutex_unlock(&mutex);
}

void * run_medium(void * wcet) {

	int i;
	int a = 13, b = 17;

	usleep(2);
	// cpu burn
	for(i=0; i<(long)wcet*100000; i++) {
		a *= b;
		if (i%10000000==0) printf("Thread Medium, CPU BURN!\n");
	}
	
}


int main()
{

	//Inizializzazione di tre thread che hanno 3 livelli di priorità differenti
	pthread_t threads[3];

    //Dichiarazione della variabile attriuto sul semaforo
    pthread_mutexattr_t mAttr;

    //Inizializzazione dell'attributo
    pthread_mutexattr_init(&mAttr);

    //Imposto il protocollo che mi interessa 
    pthread_mutexattr_setprotocol(&mAttr, PTHREAD_PRIO_INHERIT);
        //Come secondo parametro della funzione, vado a passare il valore che mi identifica il protocollo PI, posso usare anche dei
        //valori differenti:
        // -PTHREAD_PRIO_NONE: Non vado ad utilizzare alcun protocollo, quello che viene impostato di default;
        // -PHTREAD_INHERIT: Per impostare il PI;
        // -PHTREAD_PROTECTED: Per impostare il PC.
            //ATTENZIONE:
            /*Per poter impostare in modo opportuno il PC, devo anche utilizzare la funzione apposita
              pthread_mutexattr_setprioceiling(pthread_mutexattr_t *attr, int ceiling);
              perchè devo andare ad impostare il ceiling del semaforo, conoscendo le priotià dei thread che lo usano
            */

    //Dopo la creazione dell'attributo, vado ad inizializzare il semaforo usando l'attributo che ho appena creato
    pthread_mutex_init(&mutex, &mAttr);
  	
  	// init thread attr per lo scheduling esplicito dei thread creati
  	struct sched_param myparam;
	pthread_attr_t myattr;
	pthread_attr_init(&myattr);
    pthread_attr_setschedpolicy(&myattr, SCHED_FIFO);
    pthread_attr_setinheritsched(&myattr, PTHREAD_EXPLICIT_SCHED);
	
  	// start threads
	
	//Thread a minore priorità
	myparam.sched_priority = 10;
    pthread_attr_setschedparam(&myattr, &myparam); 
    pthread_create(&threads[0], &myattr, run_low, (void*)20000);
    
	//thread a maggiore priotità
    myparam.sched_priority = 20;
    pthread_attr_setschedparam(&myattr, &myparam); 
    pthread_create(&threads[1], &myattr, run_high, (void*)5000);
   
	//thread con priorità intermedia
    myparam.sched_priority = 15;
    pthread_attr_setschedparam(&myattr, &myparam); 
    pthread_create(&threads[2], &myattr, run_medium, (void*)500); 
    
    
    
    
 	// wait threads
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	pthread_join(threads[2], NULL);
		
	pthread_attr_destroy(&myattr);

    //Mi occupo di eliminare il mutex
    pthread_mutex_destroy(&mutex);

	//Distruggo l'attributo del semaforo
	pthread_mutexattr_destroy(&mAttr);
	
	printf("Final shared value: %d\n",shared);

    return 0;
}


