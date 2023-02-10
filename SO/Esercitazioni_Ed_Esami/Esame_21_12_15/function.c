//Definizione delle funzioni di consumazione e di produzione

#include "header.h"

//Funzioni di gestione delle variabili per i thread
void Inizializza(GestioneIO * g, pthread_attr_t *attr){
    
    //Imposto mutex e condizioni
    pthread_mutex_init(&(g->mutex), NULL); 

    pthread_cond_init(&(g->vc_produttori), NULL); 
    //pthread_cond_init(&(g->vc_consumatori), NULL);

    //Imposto attributo
    pthread_attr_init( attr);
    pthread_attr_setdetachstate(attr, PTHREAD_CREATE_JOINABLE);

    //Oltre questo, imposto i valori interni al monitor!
    g->numOccupati=0; 
    g->testa=0;
    g->coda=0;

    for(int i=0; i<DIM; i++){
    
        //Imposto anche i valori di indirizzo e di dato pari a 0!
        g->vettore[i].dato=0;
        g->vettore[i].indirizzo=0;

    }


}



void rimuovi(GestioneIO *g, pthread_attr_t *attr){
  
    //Distruzione mutex, condizioni e attributo
    pthread_mutex_destroy(&(g->mutex)); 
    pthread_cond_destroy(&(g->vc_produttori));
    //pthread_cond_destroy(&(g->vc_consumatori));

    pthread_attr_destroy(attr);

}


void Produci(GestioneIO * g, Buffer * b){

    //Il produttore effettua un lock sul mutex
    pthread_mutex_lock(&(g->mutex)); 

        //Controllo della condizione(while perchè signal anche continue)
        while(g->numOccupati==DIM){
            //Se tutto il vettore è occupato, mi sospendo alla condizione
            pthread_cond_wait(&(g->vc_produttori), &(g->mutex));
        }
        
        //Sono sbloccato, comincio la produzione alla testa del vettore
        //Non esco dal monitor
        
        g->vettore[g->testa].indirizzo=b->indirizzo; 
        g->vettore[g->testa].dato=b->dato;

        printf("[PRODUTTORE] Prodotto dato : %d, Indirizzo: %d\n", g->vettore[g->testa].dato, g->vettore[g->testa].indirizzo);

        //Incremento il numero di elementi che sono presenti
        g->numOccupati++; 

        //Incremento il puntatore di testa
        g->testa=(g->testa+1) %DIM;

        //Faccio una signal ai consumatori

        //La funzione di segnalazione, la posso anche omettere, perchè il consumatore, non si sospende sulla condizone
        //Ma semplicemente ritorna un valore particolare
        //pthread_cond_signal(&(g->vc_consumatori)); 

    //Posso lasciare il mutex
    pthread_mutex_unlock(&(g->mutex));



}



int Consuma(GestioneIO * g, Buffer * b){

    //Il consumatore effettua un lock sulla risorsa
    pthread_mutex_lock(&(g->mutex)); 

        //Effettua un controllo sul numero di posti che sono disponibili
        while(g->numOccupati==0){

            printf("[CONSUMATORE] Non ci sono posti liberi, ritorno 1\n");

            //Se non ci sono dei posti occupati, effettuo unlock sul mutex
            pthread_mutex_unlock(&(g->mutex)); 

            //In questo caso, ritorno il valore 1
            return 1;
        }

        //Se ci sono elementi, procedo con la consumazione

        printf("[CONSUMATORE] Consumo il valore\n"); 
            

        b->dato=g->vettore[g->coda].dato; 
        b->indirizzo=g->vettore[g->coda].indirizzo; 

        printf("[CONSUMATORE] Consumato Dato: %d, Indirizzo: %d\n", g->vettore[g->coda].dato, g->vettore[g->coda].indirizzo);

        //Incremento il puntatore di coda
        g->coda=(g->coda + 1)%DIM;
        
        //Diminuisco il numero di elementi presenti
        g->numOccupati--;

        //Segnalo i processi produttori 
        pthread_cond_signal(&(g->vc_produttori));

    //Dunque, unlock sul mutex
    pthread_mutex_unlock(&(g->mutex));

    //Invio 0, per segnalare che ho correttamente consumato
    return 0;

}