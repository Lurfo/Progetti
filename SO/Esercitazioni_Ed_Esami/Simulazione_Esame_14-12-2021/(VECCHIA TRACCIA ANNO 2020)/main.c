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

int coda_risultati;

#define NUM_THREADS_OPERANDI    2
#define NUM_THREADS_CALCOLO     3

int main(){

        pthread_attr_t attr;
        pthread_t threads_operandi[NUM_THREADS_OPERANDI];
        pthread_t threads_calcolo[NUM_THREADS_CALCOLO];

        srand(time(NULL)*getpid());

        // Creazione coda risultati
        coda_risultati = msgget(IPC_PRIVATE, IPC_CREAT|0660);
        printf("Coda coda_risultati create con desc: %d\n", coda_risultati);
    
        initServiceQueues();
            
        //creazione di una istanza di struttura monitor per gli operandi
        // MonitorOperandi sarà usato dai thread generazione operandi
        //Devo utilizzare una malloc per allocare la memoria necessaria
        MonitorOperandi * pc_op = (MonitorOperandi *) malloc(sizeof(MonitorOperandi));
    
        //inizializzazione mutex e condition
        //Variabili che sono presenti all'interno della struttura che ho appena definito
        pthread_mutex_init(&(pc_op->mutex), NULL);
        
        pthread_cond_init(&(pc_op->vcConsumatori), NULL);
        pthread_cond_init(&(pc_op->vcProduttori), NULL);

        //inizializzazione delle variabili di stato
    
        pc_op->testa=0;
        pc_op->coda=0;
        pc_op->numOccupati=0;

    
        //impostazione dei thread come joinable
        //Utilizzo le funzioni per inizializzare l'attributo
        pthread_attr_init(&attr); 

        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
        // genero processo prelievo risultati
    
        pid_t pid; 

        pid = fork();

        if(pid<0){
                perror("Erroe generazione processo prelevo risultati\n"); 
                        exit(1);
        } 

        if(pid==0){
                printf("[Figlio %d] Comincio il prelievo dei risultati\n", getpid());

                //Il processo invoca la funzione di prelievo dei risultati, inviando la coda sulla quale procedere
                //con la ricezione
                preleva_risultati(coda_risultati);
                

                exit(0);

        }
        
        int ret;

        // genero thread generazione operandi
        for(int i=0; i<NUM_THREADS_OPERANDI; i++){
             
               ret = pthread_create(&threads_operandi[i], &attr, genera_operandi, (void*) pc_op);

               if(ret){
                        perror("Errore nella creazione di un thread operando\n"); 
                                exit(1);

               }

        }
        
        
        // genero thread di calcolo
        for(int i=0; i<NUM_THREADS_CALCOLO; i++){
                
                ret = pthread_create(&threads_calcolo[i], &attr, calcola, (void *) pc_op);

                if(ret){
                        perror("Errore nella creazione di un thread calcolo\n"); 
                                exit(1);
                }

        }
    
        /* TBD:  Join threads a wait processo*/
        for(int i=0; i<NUM_THREADS_OPERANDI; i++){
                pthread_join(threads_operandi[i], NULL);
        }

        for(int i=0; i<NUM_THREADS_CALCOLO; i++){
                pthread_join(threads_calcolo[i], NULL);
        }

        wait(NULL);
        
    
    
        /*deallocazione risorse*/	
        
        //Distruzione mutex, condition e attributo
        pthread_mutex_destroy(&(pc_op->mutex)); 
        pthread_cond_destroy(&(pc_op->vcProduttori));
        pthread_cond_destroy(&(pc_op->vcConsumatori)); 

        pthread_attr_destroy(&attr); 

        //Posso liberare la memoria che contiene il messaggio
        free(pc_op);

        //Eliminazione della coda di messaggi
        msgctl(coda_risultati, IPC_RMID, NULL);

        removeServiceQueues();
    
        pthread_exit(NULL);
}

