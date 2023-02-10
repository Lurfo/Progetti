#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//Nel seguente programma, si ha una dimostrazione di come poter usare i thread all'interno di programmi
//Per la gestione, la creazione e la definizione dei thread, si usano delle funzioni messe a disposizioni nella libreria POSIX
//che vengono definite nella libreria pthread.h


#define NUM_THREADS	10

//Questa è la starting routine che ogni thread deve avere, in base a quello che prevede la funzione, la starting routine
//deve essere di tipo "void *" o quando meno devo eseguire un casting ad essa
void *PrintHello(void *threadid)
{
	//il valore threadid, corrisponde al valore "t" che ho inserito nella funzione di creazione, ed essendo un valore long,
	//posso andare a castare direttamente il valore usando il metodo di seguito
    sleep((long)threadid);
  
   printf("\n%ld: Hello World! \n", (long)threadid);
   pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
	//Definisco un array che ha il compito di mantere l'ID dei veri thread
	pthread_t threads[NUM_THREADS];

	//Sono delle variabili temporanee
	int rc;
	long t;
	
	//Vado a dichiare l'attributo del thread, in modo da andare a creare i thread JOINABLE, potendo quindi utilizzare la funzione
	//pthread_join, che mette in pausa il thread principale, fino a quando non terminano tutti i thread figli 
		//NOTA: Utilizzo questa funzione in modo che il thread principale non termini prima
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	
	//Nel ciclo, vado a creare i thread tramite la funzione pthread_create
	for(t=0;t<NUM_THREADS;t++){

		printf("Creating thread %ld\n", t);
		
		//Alla funzione di creazione devo passare una serie di valori fondamentali, tra cui:
		/*
			-L'indirizzo di memoria dello slot dell'array contente l'id del thread che vado a creare; 
			
			-L'indirizzo di memoria dell'attributo definito sopra

			-La starting routine

			-Un valore che viene utilizzato dal thread durante la sua starting routine
			NOTA BENE: Il valore che viene passato al thread, deve essere prima castato a "void *"
			(Di conseguenza, nella starting routine, devo prima eseguire il casting inverso)

		*/
		rc = pthread_create(&threads[t], &attr, PrintHello, (void *)t);
		
		if (rc){
			printf("ERROR; return code from pthread_create() is %d\n", rc);
			exit(-1);
		}
	}
	
	//A questo punto eseguo il join dei vari thread creati
	for(t=0;t<NUM_THREADS;t++) {
		pthread_join(threads[t],NULL);
	}
	
	//Termino il thread principale
	pthread_exit(NULL);
}

/* RICORDA BENE:
	Lo scheduling di linux, non fa alcune distinzione tra processi e thread, in quanto lui vede solo l'unità di esecuzione principale
	cioè: IL TASK


*/