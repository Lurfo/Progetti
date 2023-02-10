//Rispetto al caso precedente, vado ad inserire un mutex, per risolvere il problema della race condition
//Vado ad utilizzare i mutex che sono messi a disposizione dalla libreria pthread!

//ATTENZIONE: Anche se vado ad usare il semaforo, ottengo comunque l'uso corretto della risorsa, ma si può verificare il fenomeno
//di INVERSIONE DI PRIORITA', poichè il thread che ha maggiore priorità eseguirà soltano alla fine delle operazioni eseguite dal thread
//a minore priorità

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

    //Devo inizializzare il mutex (per ora non vado ad usare alcun attributo)
    pthread_mutex_init(&mutex, NULL);
  	
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
	
	printf("Final shared value: %d\n",shared);

    return 0;
}


