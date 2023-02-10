#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "header.h"

void inizializza_vettore(VettoreProdCons * p) {

    /* TBD: Inizializzare la struttura dati "VettoreProdCons" */
    for(size_t i=0; i<DIM; i++){
        p->buffer[i]=0;
    }

    p->testa=0;
    p->coda=0;

    p->numElementi=0;

    //Inizializzo il monitor con la funzione apposita
    //Ho due condizioni, una per produttori e l'altra per consumatori
    init_monitor(&(p->mon), N_VC);


}

void produci(VettoreProdCons * p, int valore) {

    /* TBD: Implementare la sincronizzazione, mediante
     *      l'algoritmo del vettore circolare di buffer
     */

    //Entro nel monitor
    enter_monitor(&(p->mon)); 

        //Controllo della condizione, essendo un monitor hoeare, posso usare if
        if(p->numElementi==DIM){
            //Se il numero di elementi è uguale alla dimensione del vettore, mi sospendo
            wait_condition(&(p->mon), VC_Produttori);
        }

        //Se sono qui, sono stato sbloccato, dunque posso produrre in testa al vettore

        p->buffer[p->testa] = valore;

        //Incremento il puntatore di testa
        p->testa=(p->testa+1)%DIM;

        //Dunque, aumenti il numero di elementi presenti
        p->numElementi++; 

        //Dunque, faccio una segnalazione ai consumatori
        //Controllando se c'è qualcuno che attende
        if(queue_condition(&(p->mon), VC_Consumatori)){
            signal_condition(&(p->mon), VC_Consumatori);
        }

    //Dunque, posso lasciare il monitor
    leave_monitor(&(p->mon));

}

int consuma(VettoreProdCons * p) {

    int valore;

    /* TBD: Implementare la sincronizzazione, mediante
     *      l'algoritmo del vettore circolare di buffer
     */


    //La funzione di consumazione è molto simile a quella di produzione

    enter_monitor(&(p->mon)); 

        //Controllo della condizione con if
        if(p->numElementi==0){
            //Se non ci sono elementi, mi sospendo
            wait_condition(&(p->mon), VC_Consumatori);
        }

        //Diminuisco il numero di elementi che sono presenti
        p->numElementi--; 

        //Consumo in coda

        valore = p->buffer[p->coda];

        //Incremento il valore del puntatore di coda
        p->coda = (p->coda+1) %DIM; 

        //Controllo se ci sono produttori in attesa
        if(queue_condition(&(p->mon), VC_Produttori)){
            //Se ci sono, li posso segnalare
            signal_condition(&(p->mon), VC_Produttori);
        }

    //Posso lasciare il monitor
    leave_monitor(&(p->mon));

    return valore;

}

void rimuovi_vettore(VettoreProdCons * p) {

    /* TBD: De-inizializzare la struttura dati "VettoreProdCons" */
    //Devo rimuovere il monitor
    remove_monitor(&(p->mon));
}


void inizializza_buffer(BufferMutuaEsclusione * p) {

    /* TBD: Inizializzare la struttura dati "BufferMutuaEsclusione" */

    //Inizializzare questa struttura, vuol dire andare ad ottenre l'id dei semafori ed impostarli
    p->sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT|0660); 


    //Imposto dunque il semaforo
    //Lo imposto in modo che il primo processo che arriva, può direttamente accedere alla risorsa
    semctl(p->sem_id, MUTEX, SETVAL, 1);

}

void aggiorna(BufferMutuaEsclusione * p, int valore) {

    /* TBD: Aggiungere la sincronizzazione per la mutua esclusione */

    //Facico una signal ed una wait sul semaforo
    Wait_Sem(p->sem_id, MUTEX);

        p->buffer += valore;

        printf("[AGGIORNA] Nuovo valore del buffer: %d\n", p->buffer);

    Signal_Sem(p->sem_id, MUTEX);

}

void rimuovi_buffer(BufferMutuaEsclusione * p) {

    /* TBD: De-inizializzare la struttura dati "BufferMutuaEsclusione" */

    //Rimuovo il buffer andando a rimuovere il semaforo
    semctl(p->sem_id, 0, IPC_RMID);
}


