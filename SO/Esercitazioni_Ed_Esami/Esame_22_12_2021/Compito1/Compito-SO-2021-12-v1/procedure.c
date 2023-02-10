#include <stdio.h>
#include <unistd.h>

#include "header.h"

void inizializza_vettore(VettoreProdCons * p) {

    /* TBD: Inizializzare la struttura dati "VettoreProdCons" */

    //Imposto il vettore di stato
    //con tutte le posizioni libere
    for(int i=0; i<DIM; i++){
        p->stato[i]=LIBERO;
    }

    //Imposto il numero di elementi occupati
    p->numOccupati=0; 

    //Imposto mutex e VC
    pthread_mutex_init(&(p->mutex), NULL); 

    pthread_cond_init(&(p->vc_produttori), NULL); 
    pthread_cond_init(&(p->vc_consumatori), NULL); 

}

void produci(VettoreProdCons * p, int valore) {

    int indice = 0;

    /* TBD: Aggiungere la sincronizzazione, mediante l'algoritmo del 
     *      produttore-consumatore con pool di buffer
     */

    //Il produttre effettua un lock sul mutex
    pthread_mutex_lock(&(p->mutex)); 

        //Effettuo un controllo della condizione (Con il while perchè signal and continue)
        while(p->numOccupati==DIM){
            //Se non ci sono posti liberi, mi sospendo sulla condizione dei produttori
            pthread_cond_wait(&(p->vc_produttori), &(p->mutex));
        }

        //Se sono qui, sono stato sbloccato, trovo un posto libero
        while(indice<DIM && p->stato[indice]!=LIBERO){
            indice++;
        }

        //modifico lo stato del posto
        p->stato[indice]=IN_USO; 

        //Modifico il numero di occupati
        p->numOccupati++;

    //Unlock sul mutex per effettuare la produzione 
    pthread_mutex_unlock(&(p->mutex));


    //Produzione
    p->buffer[indice] = valore;
    sleep(1);

    printf("[PRODUCI] Produzione effettuata: %d\n", valore);


    //Lock sul mutex per modifica dello stato e segnalazione ai consumatori
    pthread_mutex_lock(&(p->mutex)); 

        //Modifica stato
        p->stato[indice]=OCCUPATO;

        //Segnalo ai consumatori
        pthread_cond_signal(&(p->vc_consumatori));

    //Posso fare unlock sul mutex 
    pthread_mutex_unlock(&(p->mutex));

}

int consuma(VettoreProdCons * p) {

    int valore;

    int indice = 0;

    /* TBD: Aggiungere la sincronizzazione, mediante l'algoritmo del 
     *      produttore-consumatore con pool di buffer
     */

    //La consumazione avviene in modo molto simile
    pthread_mutex_lock(&(p->mutex));

        //Controllo se ci sono posti occupati
        while(p->numOccupati==0){
            //Se non ci sono posti occupati, allora mi sospendo 
            pthread_cond_wait(&(p->vc_consumatori), &(p->mutex));
        }

        //Se sono qui, sono sbloccato, trovo un posto occupato
        while(indice<DIM && p->stato[indice]!=OCCUPATO){
            indice++;
        }

        //Modifico lo stato del posto e modifico il numero di occupati
        p->stato[indice]=IN_USO; 

        p->numOccupati--;
    
    //Unlcok sul mutex per consumare
    pthread_mutex_unlock(&(p->mutex));

    valore = p->buffer[indice];
    sleep(1);

    printf("[CONSUMA] Consumazione effettuata: %d\n", valore);

    //Ritorno nel mutex per modificar lo stato del posto e segnalare ai produttori
    pthread_mutex_lock(&(p->mutex)); 
        
        //Modifico lo stato
        p->stato[indice]=LIBERO; 

        //Signal ai produttori 
        pthread_cond_signal(&(p->vc_produttori));

    //Posso lasciare il mutex
    pthread_mutex_unlock(&(p->mutex));

    //Ritorno il valore che ho consumato
    return valore;

}

void rimuovi_vettore(VettoreProdCons * p) {

    /* TBD: De-inizializzare la struttura dati "VettoreProdCons" */
    //In questo caso bisgna distruttggere sia il mutex che le VC
    pthread_mutex_destroy(&(p->mutex)); 

    pthread_cond_destroy(&(p->vc_produttori)); 
    pthread_cond_destroy(&(p->vc_consumatori));


}


void inizializza_buffer(BufferMutuaEsclusione * p) {

    /* TBD: Inizializzare la struttura dati "BufferMutuaEsclusione" */

    //Imposto il valore del buffer iniziale uguale a 0
    p->buffer=0;

    //Inizializzo il semaforo
    pthread_mutex_init(&(p->mutex), NULL);

}

void aggiorna(BufferMutuaEsclusione * p, int valore) {

    /* TBD: Effettuare la modifica al buffer in mutua esclusione */

    //Prima di aggiornare il buffer, ogni consumatore, deve effettuare un lock sul mutex, in modo da essere sicuro
    //che lui sia l'unico che può accedere a quell'elemento
    pthread_mutex_lock(&(p->mutex));


        p->buffer += valore;

        printf("[AGGIORNA] Nuovo valore del buffer: %d\n", p->buffer);

    //Effettuo poi unlock, in modo che il prossimo consumatore possa accedere 
    pthread_mutex_unlock(&(p->mutex));

}

void rimuovi_buffer(BufferMutuaEsclusione * p) {

    /* TBD: De-inizializzare la struttura dati "BufferMutuaEsclusione" */

    //In questo caso, occorre semplicemente andare a distruggere il mutex
    pthread_mutex_destroy(&(p->mutex));
}


