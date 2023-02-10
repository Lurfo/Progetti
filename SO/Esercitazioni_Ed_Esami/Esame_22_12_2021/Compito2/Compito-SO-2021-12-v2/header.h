#ifndef _HEADER_
#define _HEADER_

#include "monitor_hoare.h"
#include "semafori.h"

#define DIM 3

#define VC_Produttori 0
#define VC_Consumatori 1
#define N_VC 2


#define MUTEX 0

typedef struct {

    int buffer[DIM];

    /* TBD: Aggiungere le variabili per la sincronizzazione con 
     *      l'algoritmo del vettore circolare di buffer
     */

    //Testa e coda
    int testa; 
    
    int coda; 

    //Tengo conto del numero di elemeti che sono presenti nel vettore 
    //Viene usata come variabile di controllo
    int numElementi; 

    //Aggiungo anche il Monitor
    Monitor mon;

} VettoreProdCons;

typedef struct {

    int buffer;

    int sem_id;  // Utilizzare questa variabile per la mutua esclusione

} BufferMutuaEsclusione;

void inizializza_vettore(VettoreProdCons * p);
void produci(VettoreProdCons * p, int valore);
int consuma(VettoreProdCons * p);
void rimuovi_vettore(VettoreProdCons * p);

void inizializza_buffer(BufferMutuaEsclusione * p);
void aggiorna(BufferMutuaEsclusione * p, int valore);
void rimuovi_buffer(BufferMutuaEsclusione * p);


#endif
