#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "header.h"

#define NUM_THREADS_OPERANDI    2
#define NUM_THREADS_CALCOLO     3

int coda_risultati;


int main(){

        pthread_attr_t attr;
        pthread_t threads_operandi[NUM_THREADS_OPERANDI];
        pthread_t threads_calcolo[NUM_THREADS_CALCOLO];
    
        srand(time(NULL)*getpid());

        //Ottengo l'id della coda di messaggi
        coda_risultati = msgget(IPC_PRIVATE, IPC_CREAT|0660);
        printf("Coda coda_risultati create con desc: %d\n", coda_risultati);
    
        initServiceQueues();
            
        // Creazione di una istanza di struttura monitor per gli operandi
        // MonitorOperandi sarà usato dai thread generazione operandi
        //Alloco la struttura usando malloc
        MonitorOperandi * pc_op = (MonitorOperandi *) malloc(sizeof(MonitorOperandi));
    
        /* TODO: inizializzazione mutex e condition */
        //Uso le funzioni di libreria apposite
        pthread_mutex_init(&(pc_op->mutex), NULL);
        pthread_cond_init(&(pc_op->vc_Produttori), NULL); 
        pthread_cond_init(&(pc_op->vc_Consumatori), NULL);
    
        /* TODO: inizializzazione delle variabili di stato */
        pc_op->testa=0;
        pc_op->coda=0;
        pc_op->numOccupati=0;

        /* TODO: impostazione dei thread come joinable */
        //Inizializzazione ed impostazione dell'attributo di join!
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

        /* TODO: genero processo prelievo risultati */

        pid_t pid; 

        pid = fork(); 
        
        if(pid<0){
                perror("Errore nella fork del processo\n"); 
                        exit(1);
        }

        if(pid==0){
                printf("[figlio] Inizio\n"); 

                preleva_risultati(coda_risultati);

                exit(0);

        }
    
        /* TODO: genero thread generazione operandi */
        int res;

        for(int i=0; i<NUM_THREADS_OPERANDI; i++){
                res = pthread_create(&threads_operandi[i], &attr, genera_operandi, (void *) pc_op);

                if(res<0){
                        perror("Errore nella creazione del thread generatore\n"); 
                                exit(1);
                }

        }
    
        /* TODO: genero thread di calcolo */
        for(int i=0; i<NUM_THREADS_CALCOLO; i++){
                res = pthread_create(&threads_calcolo[i], &attr, calcola, (void *) pc_op);

                if(res<0){
                        perror("Errore nella creazione del thread calcolatore\n"); 
                                exit(1);
                }

        }
    
        /* TODO: Join threads a wait processo*/
        //Effettuo due pthread join, una per i thread calcolo ed una per i thread operandi
        for(int i=0; i<NUM_THREADS_OPERANDI; i++){
                pthread_join(threads_operandi[i], NULL);
        }

       //Effettuo anche la wait del processo
        wait(NULL);


        for(int i=0; i<NUM_THREADS_CALCOLO; i++){
                pthread_join(threads_calcolo[i], NULL);
        }


    
        /* TODO: deallocazione risorse */
        //Prima di eliminare la memoria, devo distruggere mutex e  variabili condition
        pthread_mutex_destroy(&(pc_op->mutex)); 
        
        pthread_cond_destroy(&(pc_op->vc_Produttori)); 
        pthread_cond_destroy(&(pc_op->vc_Consumatori)); 

        //Distruzione dell'attributo
        pthread_attr_destroy(&attr); 

        //Libero la memoria 
        free(pc_op); 

        //Chiamo la funzione per la rimozione della coda
        removeServiceQueues();

        //Rimovo la coda dei risultati
        msgctl(coda_risultati, IPC_RMID, NULL);
    
        pthread_exit(NULL);
}

