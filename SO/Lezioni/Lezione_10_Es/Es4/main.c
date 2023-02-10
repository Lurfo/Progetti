#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "function.h"

int main(){

    //Specifico il contenitore per l'id dei thread
    pthread_t idThr[NUMTHREAD];

    //Specifico l'attributo
    pthread_attr_t attr; 
    pthread_attr_init(&attr); 
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    //Alloco la mia struttura 

    data *p = (data *)malloc(sizeof(data)); 

    //Posso dunque inizializzare tutte le variabili che sono presenti nella struttura!
    pthread_mutex_init(&(p->mutex), NULL);

    pthread_cond_init(&(p->v_scritt), NULL); 
    pthread_cond_init(&(p->v_lett), NULL);

    p->scritt_wait=0;
    p->lett_wait=0;
    p->numLett=0;
    p->numScritt=0;

    p->strlen=MAX_LEN;


    //A questo punto, ho inizializzato tutte le variabili, le condizioni, e gli attributi
    //posso passare alla creaizone dei thread
    for(int i=0; i<NUMTHREAD; i++){

        if(i%2==0){
            sleep(1);
            pthread_create(&idThr[i], &attr, Scrittura, (void *) p);
        }

        else{
            sleep(1);
            pthread_create(&idThr[i], &attr, Lettura, (void *) p);
        }


    }

    //Il thread principale attnede la terminazione degli altri
    for(int i=0; i<NUMTHREAD; i++){
        pthread_join(idThr[i], NULL); 
        //printf("È terminato il thread %ld\n", idThr[i]);
    }

    //A questo punto, posso andare a deallocare tutte le risorse usate
    pthread_mutex_destroy(&(p->mutex)); 

    pthread_attr_destroy(&attr);

    pthread_cond_destroy(&(p->v_lett));

    pthread_cond_destroy(&(p->v_scritt));

    free(p);

    pthread_exit(0);


}