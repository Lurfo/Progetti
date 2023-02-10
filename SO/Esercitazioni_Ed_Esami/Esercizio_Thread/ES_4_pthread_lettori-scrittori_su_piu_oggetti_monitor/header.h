#ifndef HEADER_H
#define HEADER_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>



struct monitor {

	int molo;
	int id_nave;

	//Sicuramente ho bisogno di aggiungere un mutex che mi permette l'accesso al monitor
	pthread_mutex_t mutex; 

	pthread_cond_t condLettori; 
	pthread_cond_t condScrittori;

	//Aggiungo poi variabili di controllo che mi tengono traccia del numero di scrittori e del numero di lettori che sono 
	//preseti
	int numLettori; 
	int numScrrittori;

	//Tengo una variabile di contreggio del numero di elementi che sono in attesa!
	int lettoriWait; 
	int scrittoriWait;
    
};

void inizializza(struct monitor * m);
void rimuovi (struct monitor * m);
void scrivi_molo(struct monitor * m, int molo);
int leggi_molo(struct monitor * m);



#endif
