#ifndef _HEADER_
#define _HEADER_

#include <pthread.h>

#define DIM 3
#define LIBERO 0
#define INUSO 1
#define OCCUPATO 2

typedef struct
{
    int buffer[DIM];
    int stato[DIM];
    /* TBD: Aggiungere le variabili di stato per l'algoritmo del pool di buffer */
    int num_elem;
    pthread_mutex_t mutex;
    pthread_cond_t cv_prod;
    pthread_cond_t cv_cons;
    /* TBD: Aggiungere le variabili per la sincronizzazione dei thread */

} VettoreProdCons;

typedef struct
{
    int buffer;
    /* TBD: Aggiungere un mutex per la mutua esclusione */
    pthread_mutex_t mutex;

} BufferMutuaEsclusione;

void inizializza_vettore(VettoreProdCons *p);
void produci(VettoreProdCons *p, int valore);
int consuma(VettoreProdCons *p);
void rimuovi_vettore(VettoreProdCons *p);

void inizializza_buffer(BufferMutuaEsclusione *p);
void aggiorna(BufferMutuaEsclusione *p, int valore);
void rimuovi_buffer(BufferMutuaEsclusione *p);

#endif
