#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

#include "header.h"

#define NUM_MESSAGGI_DA_RICEVERE 10

void * worker(void *);

typedef struct {

    int valore;
    BufferMutuaEsclusione * buffer;

} parametri_worker;

int main() {

    int ret;

    Mess m;

    //Ottengo sempre la chiave 
    key_t kMess = ftok(PATH, CHAR);

        if(kMess<0){
            perror("Errore ftok server\n"); 
                exit(1);
        }

    int id_coda = msgget(kMess, 0);

        if(id_coda<0){
            perror("Errore msgget server\n"); 
                exit(1);
        }

    printf("[Server] Chiave: %d, Id: %d\n", kMess, id_coda);


    //La struttura dati da condividere con i thread, deve essere allocata con malloc
    BufferMutuaEsclusione * buffer = (BufferMutuaEsclusione *) malloc(sizeof(BufferMutuaEsclusione));

    buffer->valore = 0;
  
    /* TBD: Completare l'inizializzazione di "buffer" */
    //Devo inizializzare anche il semaforo
    pthread_mutex_init(&(buffer->mutex), NULL);

    //Mi dichiaro una serie di puntatori ai parametri che devo inviare ai thread
    //Devo allocare una struttura per ogni thread
    parametri_worker *par = (parametri_worker *) malloc(NUM_MESSAGGI_DA_RICEVERE*sizeof(parametri_worker)); 

        //Imposto il puntatore al buffer
        for(int i=0; i<NUM_MESSAGGI_DA_RICEVERE; i++){
            par[i].buffer=buffer;
        }

    /* Il programma avvierà un thread worker distinto 
     * per ogni messaggio ricevuto
     */
    pthread_t thread_worker[NUM_MESSAGGI_DA_RICEVERE];

    for(int i=0; i<NUM_MESSAGGI_DA_RICEVERE; i++){

        /* TBD: Effettuare la ricezione del messaggio */
        //Il client effettua una receive bloccante, attendendo che il messaggio gli venga consegnato
        ret = msgrcv(id_coda, (void *) &m, SIZE(Mess), STD_TYPE, 0); 

            if(ret<0){
                perror("Errore ricezione valore\n"); 
                    exit(1);
            }

        printf("[SERVER] Ricezione: %d\n", m.val);

        //Imposto il valore in una delle strutture che ho definito
        par[i].valore=m.val;


        /* TBD: Creare un thread figlio, facendogli eseguire la
         *      funzione "worker", e passandogli sia il valore ricevuto
         *      sia il "buffer", tramite la struttura dati "parametri_worker"
         */  

        //Creo i thread e ad ognuno passo la funzione che ho definito
        ret = pthread_create(&thread_worker[i], NULL, worker, (void *) &par[i]);

            if(ret){
                perror("Errore creazione thread worker\n"); 
                    exit(1);
            }

    }


    /* TBD: Attendere la terminazione dei thread figli */
    int stato; 

    for(int i=0; i<NUM_MESSAGGI_DA_RICEVERE; i++){
        pthread_join(thread_worker[i], (void *) &stato); 

        if((int) stato<0){
            perror("Errore join del thread worker\n"); 
                exit(1);
        }
        
    }


    /* TBD: De-allocazione della struttura dati "buffer" */

    //Rimozione del semaforo
    pthread_mutex_destroy(&(buffer->mutex)); 

    //Rimozione del riferimento
    free(buffer); 

    //Rimozione del vettore delle strutture
    free(par);


    pthread_exit(0);

}


void * worker(void * p) {

    //Casting inverso
    parametri_worker *par  = (parametri_worker *) p;

    BufferMutuaEsclusione * buffer = par->buffer;
    int valore = par->valore;


    /* TBD: Effettuare la modifica del buffer in mutua esclusione */

    //Lock sul mutex 
    pthread_mutex_lock(&(buffer->mutex));

        sleep(1);

        buffer->valore += valore;

        printf("[WORKER] Nuovo valore del buffer: %d\n", buffer->valore);

    //Unlock
    pthread_mutex_unlock(&(buffer->mutex));


    pthread_exit(0);
}