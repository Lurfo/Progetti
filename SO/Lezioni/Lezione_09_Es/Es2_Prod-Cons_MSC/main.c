#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>


#include "function.h"

#define NUM_PRODUTTORI 3
#define NUM_CONSUMATORI 3




int main(){
    //Definisco la memoria condivisa che contiene la struttura 

    int idMem=shmget(IPC_PRIVATE, sizeof(Buff), IPC_CREAT|0660); 

    if(idMem<0){
        perror("Errore creazione mem\n");
            exit(1);
    }

    //Attach
    Buff* p = (Buff*) shmat(idMem, NULL, 0);

    if(p==(void*)-1){
        perror("Errore attach\n");
            exit(1);
    }

    //Posso inizializzare le variabili ed il monitor
    p->buff_libero=1;
    p->buff_occupato=0; 

    //Inizializzo anche il monitor
    init_monitor(&(p->m), NUM_VAR);

    //Avendo inizializzato il monitor, posso andare a creare i processi

    pid_t pid;

    int val;

    for(int i=0; i<NUM_PRODUTTORI; i++){
        
        pid=fork(); 
        
            if(pid<0){
                perror("Errore fork dei produttori\n");
                    exit(1);
            }

            if(pid==0){
                printf("Processo produttore: %d\n", getpid()); 
                
                sleep(5);

                srand(getpid()*time(NULL)); 

                val=rand()%100+1;

                produttore(p, val);

                exit(0);

            }
    }

    //Definisco i figli consumatori
    for(int i=0; i<NUM_CONSUMATORI; i++){
        pid=fork(); 

            if(pid<0){
                perror("Errore fork consumatori\n");
                    exit(1);
            }

            if(pid==0){
              
                printf("Processo consumatore: %d\n", getpid());

                printf("Ho consumato il valore: %d\n", consumo(p));

                exit(0);
            }
    }

    //Attendo i processi figli
    for(int i=0; i<NUM_CONSUMATORI+NUM_PRODUTTORI; i++){
        printf("Si è arrestato il processo %d\n", wait(NULL));
    }

    //Rimuovo tutto quello che ho usato
    remove_monitor(&(p->m)); 
    shmctl(idMem, IPC_RMID, NULL);

}