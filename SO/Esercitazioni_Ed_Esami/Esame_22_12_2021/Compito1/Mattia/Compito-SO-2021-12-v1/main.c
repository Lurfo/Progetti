#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "header.h"

#define NUM_PRODUTTORI 2
#define NUM_CONSUMATORI 5

#define PRODUZIONI 10
#define CONSUMAZIONI 4

void *produttore(void *);
void *consumatore(void *);

typedef struct
{
    /* TBD: Completare questa struttura dati, per il passaggio
     *      dei parametri ai thread consumatori
     */
    VettoreProdCons *vettore;
    BufferMutuaEsclusione *buffer;

} parametri_consumatore;

int main()
{

    pthread_t thread_prod[NUM_PRODUTTORI];
    pthread_t thread_cons[NUM_CONSUMATORI];
    VettoreProdCons *vettore = (VettoreProdCons *)malloc(sizeof(VettoreProdCons));
    BufferMutuaEsclusione *buffer = (BufferMutuaEsclusione *)malloc(sizeof(BufferMutuaEsclusione));
    parametri_consumatore *parametri = (parametri_consumatore *)malloc(sizeof(parametri_consumatore));

    inizializza_vettore(vettore);
    inizializza_buffer(buffer);

    parametri->buffer = buffer;
    parametri->vettore = vettore;

    for (int i = 0; i < NUM_PRODUTTORI; i++)
    {
        /* TBD: Creare i thread produttori, passandogli
         *      in ingresso la variabile "vettore"
         */
        printf("Avvio Produttore #%d\n", i + 1);
        pthread_create(&thread_prod[i], NULL, produttore, (void *)vettore);
    }

    for (int i = 0; i < NUM_CONSUMATORI; i++)
    {
        /* TBD: Creare i thread consumatori, passandogli
         *      in ingresso le variabili "vettore" e "buffer"
         *      mediante la struttura "parametri_consumatore"
         */
        printf("Avvio Consumatore #%d\n", i + 1);
        pthread_create(&thread_cons[i], NULL, consumatore, (void *)parametri);
    }

    /* TBD: Attendere la terminazione dei thread produttori e dei
     *      thread consumatori
     */

    int status;
    sleep(8);
    for (int i = 0; i < NUM_PRODUTTORI; i++)
    {
        pthread_join(thread_prod[i], (void **)&status);
        if (status == -1)
            printf("Error terminating thread #%ld\n", thread_prod[i]);
        else
            printf("Thread #%ld terminated with status %d\n", thread_prod[i], status);
    }

    for (int i = 0; i < NUM_CONSUMATORI; i++)
    {
        pthread_join(thread_cons[i], (void **)&status);
        if (status == -1)
            printf("Error terminating thread #%ld\n", thread_prod[i]);
        else
            printf("Thread #%ld terminated with status %d\n", thread_cons[i], status);
    }

    rimuovi_buffer(buffer);
    rimuovi_vettore(vettore);

    /* TBD: Deallocare le strutture dati */
    free(vettore);
    free(buffer);
    free(parametri);

    return 0;
}

void *produttore(void *p)
{
    VettoreProdCons *vettore = (VettoreProdCons *)p;
    for (int i = 0; i < PRODUZIONI; i++)
    {
        srand(getpid() * time(NULL) + i);
        int valore = rand() % 10;

        printf("[MAIN PRODUTTORE] Produzione: %d\n", valore);

        produci(vettore, valore);
    }

    pthread_exit(NULL);
}

void *consumatore(void *p)
{
    parametri_consumatore *parametri = (parametri_consumatore *)p;
    for (int i = 0; i < CONSUMAZIONI; i++)
    {

        int valore;

        valore = consuma(parametri->vettore);

        printf("[MAIN CONSUMATORE] Consumazione: %d\n", valore);

        aggiorna(parametri->buffer, valore);
    }

    pthread_exit(NULL);
}
