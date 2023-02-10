#include <stdio.h>
#include <unistd.h>

#include "header.h"

void inizializza_vettore(VettoreProdCons *p)
{

    /* TBD: Inizializzare la struttura dati "VettoreProdCons" */
    pthread_mutex_init(&p->mutex, NULL);
    pthread_cond_init(&p->cv_cons, NULL);
    pthread_cond_init(&p->cv_prod, NULL);
    p->num_elem = 0;
    for (size_t i = 0; i < DIM; i++)
    {
        p->buffer[i] = LIBERO;
        p->stato[i] = LIBERO;
    }
}

void produci(VettoreProdCons *p, int valore)
{
    int indice = 0;
    /* TBD: Aggiungere la sincronizzazione, mediante l'algoritmo del 
     *      produttore-consumatore con pool di buffer
     */
    pthread_mutex_lock(&p->mutex);

    while (p->num_elem == DIM)
        pthread_cond_wait(&p->cv_prod, &p->mutex);

    while (indice < DIM && p->stato[indice] != LIBERO)
        indice++;

    p->stato[indice] = INUSO;
    pthread_mutex_unlock(&p->mutex);

    p->buffer[indice] = valore;
    sleep(1);
    printf("[PRODUCI] Produzione effettuata: %d\n", valore);

    pthread_mutex_lock(&p->mutex);

    p->num_elem++;

    pthread_cond_signal(&p->cv_cons);
    pthread_mutex_unlock(&p->mutex);
}

int consuma(VettoreProdCons *p)
{

    int valore;
    int indice = 0;

    pthread_mutex_lock(&p->mutex);
    /* TBD: Aggiungere la sincronizzazione, mediante l'algoritmo del 
     *      produttore-consumatore con pool di buffer
     */
    while (p->num_elem == 0)
        pthread_cond_wait(&p->cv_cons, &p->mutex);

    while (indice < DIM && p->stato[indice] != OCCUPATO)
        indice++;

    p->stato[indice] = INUSO;

    pthread_mutex_unlock(&p->mutex);

    valore = p->buffer[indice];
    sleep(1);
    printf("[CONSUMA] Consumazione effettuata: %d\n", valore);

    pthread_mutex_lock(&p->mutex);
    p->num_elem--;

    pthread_cond_signal(&p->cv_prod);

    pthread_mutex_unlock(&p->mutex);

    return valore;
}

void rimuovi_vettore(VettoreProdCons *p)
{
    /* TBD: De-inizializzare la struttura dati "VettoreProdCons" */
    pthread_mutex_destroy(&p->mutex);
    pthread_cond_destroy(&p->cv_cons);
    pthread_cond_destroy(&p->cv_prod);
}

void inizializza_buffer(BufferMutuaEsclusione *p)
{

    /* TBD: Inizializzare la struttura dati "BufferMutuaEsclusione" */
    pthread_mutex_init(&p->mutex, NULL);
    p->buffer = 0;
}

void aggiorna(BufferMutuaEsclusione *p, int valore)
{

    /* TBD: Effettuare la modifica al buffer in mutua esclusione */
    pthread_mutex_lock(&p->mutex);
    p->buffer += valore;
    printf("[AGGIORNA] Nuovo valore del buffer: %d\n", p->buffer);
    pthread_mutex_unlock(&p->mutex);
}

void rimuovi_buffer(BufferMutuaEsclusione *p)
{
    pthread_mutex_destroy(&p->mutex);
    /* TBD: De-inizializzare la struttura dati "BufferMutuaEsclusione" */
}
