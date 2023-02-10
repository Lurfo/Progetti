//Specifica delle funzioni di produzione e consumazione che sono presenti nel file .h

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#include "function.h"


void * produttore (void *arg){
    
    //Effettuo un casting inverso degli argomenti della funzione!
    data *p = (data*) arg;

    //Per produrre il mio messaggio, devo entra nel monitor
    //Devo dunque effettuare un lock sul mutex presente nella struttura

    //ogni Produttore, deve effettuare questo processo di produzion per 3 volte


    for(int i=0; i<3; i++){

        pthread_mutex_lock(&(p->mutex));

            //Entrato nel monitor, devon controllare la condizione, andando a controllare le variabili di controllo 
            //essendo una tipologia di monitor  signal and continue, allora si ha che devo effettuare un controllo usando un while
            while(p->ok_produzione==0){
                //In questo caso, mi devo bloccare sulla condizione
                pthread_cond_wait(&(p->v_prd), &(p->mutex));
            }


            //In questo caso, se sono qui vuol dire che posso andare a produrre il mio messaggio!
            //Come prima cosa, modifico le variabili di controllo
            p->ok_produzione=0;
            p->ok_consumo=1;

            //Genero poi il mio valore
            p->msg= rand() %10 +1;


            printf("Ho prodotto il valore: %d\n", p->msg);

            //Posso andare a fare la segnalazione ai consumatori che è presente una variabile
            pthread_cond_signal(&(p->v_cns));

        //Non ho più altro da fare, posso quindi fare unlock sul mutex del monitor
        pthread_mutex_unlock(&(p->mutex));
    }

    //Alla fine, è corretto che il thread termini con pthread exit
    pthread_exit((void *)0);        

}







void * consumatore(void *arg){

    //Il ocnsumatore "si muove", allo stesso modo del produttore!

    //Come prima cosa, effettuo un casting da void* a un puntatore di tipo data!
    data* val = (data*) arg; 

    int mess;

    //Come il Produttore, anche il consumatore, deve ripetere il processo per 3 volte!
    for(int i=0; i<3; i++){

        //Effettuo l'accesso al monitor, usando il mutex
        pthread_mutex_lock(&(val->mutex));

            //Effettuo un controllo usando le variabili apposite, sempre definite nella struttura
            while(val->ok_consumo==0){
                //Fino a quando la variabile di controllo è nulla, allora ho che devo effettuare una wait sulla condizione di
                //consumo
                pthread_cond_wait(&(val->v_cns), &(val->mutex));
            }

            //Nel caso in cui io sia qui, vuol dire che sono stato sbloccado, modifico le variabili di controllo
            val->ok_consumo=0;
            val->ok_produzione=1;

            mess=val->msg;

            //Posso mostrare a video il messaggio
            printf("Ho consumato il valore: %d\n", mess);

            //Faccio una signal ai produttori
            pthread_cond_signal(&(val->v_prd));

        
        //Posso fare unlock sul mutex poichè ho concluso il mio compito!
        pthread_mutex_unlock(&(val->mutex));
    }

    //Alla fine, è corretto che il thread termini con l'istruzione di pthread_exit
    pthread_exit((void *)0);

}