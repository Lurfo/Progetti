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

	/* TODO: Aggiungere variabili per la sincronizzazione */

	//Aggiungo il mutex
	pthread_mutex_t mutex; 

	//Aggiungo le Variabili condition, una per gli scrittori ed una per i lettori
	pthread_cond_t vc_Lett;
	pthread_cond_t vc_Scritt;

	//Aggiungo le variabili di controllo, che tengono conto del numero di scrittori e del numero di lettori
	//che occupano in quel momento lo spazio della memoria!
	int numScrittori;
	int numLettori;

    
};

void inizializza(struct monitor * m);
void rimuovi (struct monitor * m);
void scrivi_molo(struct monitor * m, int molo);
int leggi_molo(struct monitor * m);



#endif
