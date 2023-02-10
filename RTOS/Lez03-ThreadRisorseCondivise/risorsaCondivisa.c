// FIFO Threads Priority Inversion simulation
//Nell'esempio di seguito si vede come, andando ad utilizzare una risorsa condivisa senza che questa sia in alcun modo protetta con dei
//semafori, si può ottenere un risultato impredicibile (potrebbe verificarsi che alcuni aggiornamenti fatti dai thread non vengano
//visti dagli altri thread)

//Una soluzione che si potrebbe pensare essere ottima per questo problema è andare ad impostare anche la CPU sulla quale deve eseguire
//tale programma. Tuttavia non è così semplice: si può notare infatti che, anche andando ad impostare tutti i thread sulla medesima
//cpu, comunque non ottengo il risultato sperato, ho comunque un problema di race condition, infatti ogni thread effettua primauna lettura
//e poi una riscrittura del valore: Quindi, se il valore che vado a leggere risulta errato, andrò dunque a scrivere un valore errato

//LA RACE CONDITION: Quell'errore che si verifica quando ho che il risultato finale dipende "DELL'ORDINE DI ESECUZIONE" dei processi

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

void * run_high(void * wcet) {
	
	int i = 1;
	int j;
	int a = 13, b = 17;
	usleep(1);
	printf("Thread High about to lock...\n");
	//simulating a long critical section
	while (i <= (long)wcet) {
		int sh = shared;
		for(j=0; j<100000; j++) a*=b;
		shared = sh+1;
		if (i%100==0) printf("Thread High, shared=%d\n",shared);
		i++;
	}
}

void * run_low(void * wcet) {
	
	int i = 1;
	int j;
	int a = 13, b = 17;
	printf("Thread Low about to lock...\n");
	//simulating a long critical section
	while (i <= (long)wcet) {
		int sh = shared;
		for(j=0; j<100000; j++) a*=b;
		shared = sh+1;
		if (i%100==0) printf("Thread Low, shared=%d\n",shared);
		i++;
	}	
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
	
	printf("Final shared value: %d\n",shared);

    return 0;
}


