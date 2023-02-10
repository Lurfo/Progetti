#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <time.h>

#include "function.h"

#define NUM_LETTORI 3
#define NUM_SCRITTORI 3

#define LETTURE 3
#define SCRITTURE 2

int main(){
    //Definisco la memoria condivisa, in cui andare ad inserire la mia struttura

    int idMem=shmget(IPC_PRIVATE, sizeof(Buff), IPC_CREAT|0660); 

    if(idMem<0){
        perror("Errore shmget\n");
            exit(1);
    }

    //Devo effettuare l'attach della memoria!
    Buff* punt = (Buff*) shmat(idMem, NULL, 0);

    if(punt==(void*)-1){
        perror("Errore attach\n");
            exit(1);
    }

  
    //Inizializzo il monitor, con le 2 variabili condition che devo considerare!
    init_monitor(&(punt->m), 2);


    //Posso quindi inizializzare la mia struttura 
    punt->num_lettori=0;
    punt->num_scrittori=0;

    //Posso andare a generare i processi
    pid_t pid;

    //Genero i processi lettori
    for(int i=0; i<NUM_LETTORI; i++){
        //Effettuo la fork
        pid=fork(); 
        
        if(pid<0){
            perror("Errore fork lettori\n"); 
                exit(1); 
        }

        if(pid==0){
            printf("Sono il processo lettore\n"); 

            sleep(2);
            
            //Il processo lettore, deve fare un certo numero di letture
            for(int j=0; j<LETTURE; j++){
                
                printf("Ho letto il valore: %d\n", Lettura(punt));
                sleep(1);
            
            }

            exit(0);

        }

    }

    //Posso generare i processi scrittori
    for(int i=0; i<NUM_SCRITTORI; i++){
      
        pid=fork(); 

        if(pid<0){
            perror("Errore fork Scrittori\n"); 
                exit(1);
        }

        if(pid==0){

            printf("Sono il processo Scrittore\n");

            srand(getpid()*time(NULL));

            sleep(1);

            //Effettuo un certo numero di scritture
            for(int j=0; j<SCRITTURE; j++){
                
                 int val = rand()%100+1;
                 Scrivi(punt, val);

                 //Aspetto un certo tempo ad ogni  scrittura
                 sleep(2);
            }

            exit(0);           

        }
    }



    //Faccio attendere il processo padre
    for(int i=0; i<NUM_SCRITTORI+NUM_LETTORI; i++){
        printf("Si è concluso il processo: %d\n", wait(NULL));
    }

    //Vado ad eliminare tutte le memorie che ho creato
    remove_monitor(&(punt->m));

    //Rimuovo la memoria condivisa
    shmctl(idMem, IPC_RMID, NULL);



}