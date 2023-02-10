#ifndef _HEADER_
#define _HEADER_

#include <pthread.h>

#define DIM 3

#define LIBERO 0
#define IN_USO 1
#define OCCUPATO 2

typedef struct {

    int buffer[DIM];

    /* TBD: Aggiungere le variabili di stato per l'algoritmo del pool di buffer */

    //Inserisco il vettore di stato
    int stato[DIM];

    /* TBD: Aggiungere le variabili per la sincronizzazione dei thread */

    //Aggiungo la variabile che tiene conto del numero di elementi che sono occupati
    int numOccupati; 

    //Aggiungo mutex e VC
    pthread_mutex_t mutex; 

    pthread_cond_t vc_produttori; 
    pthread_cond_t vc_consumatori;


} VettoreProdCons;

typedef struct {

    int buffer;

    /* TBD: Aggiungere un mutex per la mutua esclusione */

    //Il buffer deve essere utilizzato in mutua esclusione tra i thread consumatori, per questa ragione, vado ad impostare
    //un mutex
    pthread_mutex_t mutex;
    
} BufferMutuaEsclusione;

void inizializza_vettore(VettoreProdCons * p);
void produci(VettoreProdCons * p, int valore);
int consuma(VettoreProdCons * p);
void rimuovi_vettore(VettoreProdCons * p);

void inizializza_buffer(BufferMutuaEsclusione * p);
void aggiorna(BufferMutuaEsclusione * p, int valore);
void rimuovi_buffer(BufferMutuaEsclusione * p);


#endif
