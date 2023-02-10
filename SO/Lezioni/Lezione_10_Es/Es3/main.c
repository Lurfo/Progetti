#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#include "function.h"

int main(){
    //Instalzio le variabili che fungono da attributo e quela che deve contenere l'id del thread!

    pthread_attr_t attr; 
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    pthread_t idThr[NUM_THREAD]; 

    //Per andare ad usare la mia struttura, devo ovviamente allocarla in memoria, ottenendo un puntatore ad essa
    data *pnt = (data *) malloc(sizeof(data));

    //A questo punto è necessario andare ad inizializzare tutte le variabili, che occorrono al thread, ma che sono all'interno
    //della struttura

    //Inizializzazione del semaforo del monitor 
    pthread_mutex_init(&(pnt->mutex), NULL);

    //Anche le variabili condition, devono essere inzializzate
    pthread_cond_init(&(pnt->v_prd), NULL);
    pthread_cond_init(&(pnt->v_cns), NULL);

    //Inizializzo anche le variabili di controllo
    //Inizialmente lo spazio è vuoto, quindi devo settare quella di produzione uguale a 1!
    //Di conseguenza, quella del consumo è nulla!
    pnt->ok_consumo=0;
    pnt->ok_produzione=1;

    pnt->msg=0;

    //Posso dunque andare a creare i thread, impostandoli come joinable
    for(int i=0; i<NUM_THREAD; i++){

        srand(time(NULL)*(i+1));

        if(i%2==0){

            if(pthread_create(&idThr[i], &attr, produttore, (void *) pnt)){
                perror("ERRORE NELLA CREAZIONE DEL THREAD PRODUTTORE\n");
                    exit(1);
            }
        }

        else{

            if(pthread_create(&idThr[i], &attr, consumatore, (void *)pnt)){
                perror("ERRORE NELLA CREAZIONE DEL THREAD CONSUMATORE\n"); 
                    exit(1);
            }

        }

    }

    void *status;
    //Il thread principale, deve sempre attendere la terminazione degli altri thread!
    for(int i=0; i<NUM_THREAD; i++){

        pthread_join(idThr[i], &status);

        printf("È terminato il thread: %ld, con stato: %d\n", idThr[i], (int) status);
    }



    //Prima di terminare il thread principale, deve deallocare tutte le risorse che sono state create 
    pthread_attr_destroy(&attr);

    pthread_mutex_destroy(&(pnt->mutex));

    pthread_cond_destroy(&(pnt->v_cns));
    pthread_cond_destroy(&(pnt->v_prd));

    //Solo dopo aver eliminato tutte le variabili che ho definito nella struttura, posso rilasciare la memoria che 
    //avevo considerato!
    free(pnt);

    //Il thread principale, termina dopo che gli altri sono terminati, ma solo dopo aver deallocato e liberato la memoria 
    //e le variabili che sono state usate!
    pthread_exit(0);




}