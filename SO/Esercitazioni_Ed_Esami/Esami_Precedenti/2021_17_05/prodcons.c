#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "prodcons.h"

void inizializza(MonitorPC * m) {

    printf("Inizializzazione monitor\n");

    /* TBD: Inizializzazione */

    //Inizializzo le Variabili Condition, tramite la funzione apposita della libreria pthread
    pthread_cond_init(&(m->vc_produttori_1), NULL);
    pthread_cond_init(&(m->vc_consumatori_1), NULL);

    pthread_cond_init(&(m->vc_produttori_2), NULL); 
    pthread_cond_init(&(m->vc_consumatori_2), NULL);

    //Inizializzo il mutex, sempre con la funzione apposita
    pthread_mutex_init(&(m->mutex), NULL); 

    //Imposto dunque le vaiabili di controllo
    m->num_liberi=DIM;
    m->num_occupati_tipo1=0;
    m->num_occupati_tipo2=0;
    
    //Imposto il vettore di stato
    for(int i=0; i<DIM; i++){
        m->stato[i]=LIBERO;
    }

    //Inizializzo anche i valori del vettore a 0
    for(int i=0; i<DIM; i++){
        m->vettore[i]=0;
    }


}


void rimuovi(MonitorPC * m) {

    printf("Rimozione monitor\n");

    /* TBD: Rimozione */
    //Questo riguarda solo attributi e mutex, che posso rimuovere usando le funzioni di libreria
    pthread_mutex_destroy(&(m->mutex));

    pthread_cond_destroy(&(m->vc_produttori_1));
    pthread_cond_destroy(&(m->vc_consumatori_1));
    
    pthread_cond_destroy(&(m->vc_produttori_2));
    pthread_cond_destroy(&(m->vc_consumatori_2));

}


void produci_tipo_1(MonitorPC * m, int valore) {

    int index = 0;


    /* TBD: Sincronizzazione, e selezione dell'indice su cui produrre */
    //Come prima cosa, effettuo un lock sul mutex
    pthread_mutex_lock(&(m->mutex)); 

        //Controllo la condizione, tramite while, perchè la libreria pthread, permette di implementare solo un monitor signal
        //and continue
        while(m->num_liberi==0){
            //Se non ci sono dei posti liberi, allora mi devo sospendere
            pthread_cond_wait(&(m->vc_produttori_1), &(m->mutex));
        }

        //Quando vengo sbloccato, trovo il primo posto libero disponibile

        while (index<DIM && m->stato[index]!=LIBERO){
            index++;
            //Incremento in modo da andare a trovare il posto libero
        }

        //Diminuisco il numero di posti liberi e poi cambio lo stato del posto
        m->num_liberi--; 

        m->stato[index]=INUSO;

    //Posso lasciare il mutex, in modo che il prossimo elemento possa trovare la sua posizione 
    pthread_mutex_unlock(&(m->mutex));
        
    //Effettuo la produzione
    printf("Produzione di tipo 1 in corso (valore=%d, index=%d)\n", valore, index);

    sleep(1);
    m->vettore[index] = valore;

    //Ritorno nuovamente nel mutex, in modo da modificare le ultime variabili 
    pthread_mutex_lock(&(m->mutex));

        //Modifico il numero di occupati tipo 1
        m->num_occupati_tipo1++; 

        //Inserisco lo stato rispetto a quella posizione
        m->stato[index]=OCCUPATO1;

        //Effettuo una signal ai consumatori che sono in attesa
        pthread_cond_signal(&(m->vc_consumatori_1));

    //Posso effettuare unlock sul mutex 
    pthread_mutex_unlock(&(m->mutex));

}


void produci_tipo_2(MonitorPC * m, int valore) {

    int index = 0;


    /* TBD: Sincronizzazione, e selezione dell'indice su cui produrre */
    //Il produttore di tipo 2 è molto simile con il produttore tipo 1, quello che cambia sono le condizioni
    //rispetto a cui vengono effettuate le signal e le wait
    pthread_mutex_lock(&(m->mutex)); 

        //Controllo la condizione
        while (m->num_liberi==0){
            //Mi sospendo rispetto alla variabile dei produttori di tipo 2
            pthread_cond_wait(&(m->vc_produttori_2), &(m->mutex));
        }

        //Dunque trovo la posizione del vettore libera
        while(index<DIM && m->stato[index]!=LIBERO){
            //Dunque incremento il valore dell'indice
            index++;
        }

        //Decremento il numero di posti liberi;
        m->num_liberi--;

        m->stato[index]=INUSO;

    //Lascio il mutex
    pthread_mutex_unlock(&(m->mutex));

    printf("Produzione di tipo 2 in corso (valore=%d, index=%d)\n", valore, index);

    sleep(1);
    m->vettore[index] = valore;

    //Ritorno nel mutex, per andare a modificare le variabile
    pthread_mutex_lock(&(m->mutex)); 

        //Modifico il numero d posti occupati di tipo 2
        m->num_occupati_tipo2++; 

        //Modifico lo stato del posto
        m->stato[index]=OCCUPATO2;

        //Effettuo una signal ai consumatori del tipo 2
        pthread_cond_signal(&(m->vc_consumatori_2));

    //Posso dunque lasciare il monitor
    pthread_mutex_unlock(&(m->mutex));



}


void consuma_tipo_1(MonitorPC * m, int * valore) {

    int index = 0;


    /* TBD: Sincronizzazione, e selezione dell'indice su cui consumare */
    
    //Faccio lock sul mutex
    pthread_mutex_lock(&(m->mutex));

        //In questo caso, devo vedere se ci sono elementi tipo 1
        while(m->num_occupati_tipo1==0){
            //Se non ci sono, faccio una wait sulla condizione
            pthread_cond_wait(&(m->vc_consumatori_1), &(m->mutex));
        }

        //Se sono qui, sono sbloccato, trovo il posto OCCUPATO1
        while(index<DIM && m->stato[index]!=OCCUPATO1){
            index++;
        }

        //Diminuisco il numero di occupati1
        m->num_occupati_tipo1--;

        m->stato[index]=INUSO;

    //Effettuo unlock sul mutex
    pthread_mutex_unlock(&(m->mutex));

    sleep(1);
    *valore = m->vettore[index];

    printf("Consumazione di tipo 1 (valore=%d, index=%d)\n", *valore, index);

    //Ritno nuovamente nel monitor
    pthread_mutex_lock(&(m->mutex)); 

        //Modifico il numero di elementi liberi
        m->num_liberi++; 

        //modifico lo stato del vettore 
        m->stato[index]=LIBERO; 

        //Faccio signal ai produttori di tipo 1
        pthread_cond_signal(&(m->vc_produttori_1));

    //Lascio il mutex
    pthread_mutex_unlock(&(m->mutex));

}


void consuma_tipo_2(MonitorPC * m, int * valore) {

    int index = 0;


    /* TBD: Sincronizzazione, e selezione dell'indice su cui consumare */
    //Il consumatore tipo 2 è uguale a quello tipo 1, con la sola eccezione che devo andare a considerare delle vc differenti

    pthread_mutex_lock(&(m->mutex));

        //In questo caso, devo vedere se ci sono elementi tipo 2
        while(m->num_occupati_tipo2==0){
            //Se non ci sono, faccio una wait sulla condizione
            pthread_cond_wait(&(m->vc_consumatori_2), &(m->mutex));
        }

        //Se sono qui, sono sbloccato, trovo il posto OCCUPATO2
        while(index<DIM && m->stato[index]!=OCCUPATO2){
            index++;
        }

        //Diminuisco il numero di occupati2
        m->num_occupati_tipo2--;

        m->stato[index]=INUSO;

    //Effettuo unlock sul mutex
    pthread_mutex_unlock(&(m->mutex));

    sleep(1);
    *valore = m->vettore[index];

    printf("Consumazione di tipo 2 (valore=%d, index=%d)\n", *valore, index);

    pthread_mutex_lock(&(m->mutex)); 

        //Modifico il numero di elementi liberi
        m->num_liberi++; 

        //modifico lo stato del vettore 
        m->stato[index]=LIBERO; 

        //Faccio signal ai produttori di tipo 2
        pthread_cond_signal(&(m->vc_produttori_2));

    //Lascio il mutex
    pthread_mutex_unlock(&(m->mutex));

}