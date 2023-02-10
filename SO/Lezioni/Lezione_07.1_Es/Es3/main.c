#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <sys/shm.h>


#include "function.h"
#include "semafor.h"

int main(){
    //Definisco la memoria condivisa!

    int shmID = shmget(IPC_PRIVATE, sizeof(buffer), IPC_CREAT|IPC_EXCL|0660); 

        if(shmID<0){
            perror("Errore nella shmID\n"); 
                exit(1);
        }
    
    //Faccio attachment

    buffer* punt = (buffer*) shmat(shmID, NULL, 0); 

    //Inizializzo tutti gli spazio del buffer come spazi liberi!
    for(int i=0; i<DIM; i++){
        punt->vetto[i]=BUFFER_VUOTO;
    }

    printf("Memoria Condivisa creata!\n"); 

    //Creo i semafori!

    int semID = semget(IPC_PRIVATE, 4, IPC_CREAT|IPC_EXCL|0660);

        if(semID<0){
            perror("Errore nella creazione dei semafori!\n"); 
                exit(1);
        }

    //Inizializzo i semafori
    
    //Il semaforo degli spazi disponibili, inizialmente ha come valore il numero di locazioni del buffer!
    semctl(semID, SPAZIO_DISPONIBILE, SETVAL, DIM);
    semctl(semID, MESSAGGIO_DISPONIBILE, SETVAL, 0); 
    
    //I due mutex hanno entrambi 1 come valore!
    semctl(semID, MUTEX_C, SETVAL, 1); 
    semctl(semID, MUTEX_P, SETVAL, 1);

    printf("Semafori inizializzati!\n"); 

    printf("################################################\n"); 

    printf("Inizio il processo di produzione e consumazione!\n"); 

    sleep(2); 

    //Creo i producessi consumatori!
     
    for(int i=0; i<NUMERO_CONSUMATORI; i++){
        int pid=fork(); 
         
            if(pid<0){
                perror("Errore fork produttori\n"); 
                    exit(1);
            }

            if(pid==0){
                printf("Figlio consumatore\n");
                consumatore(punt, semID);
                exit(0);
            }
    }

    //Creo i processi produttori
    for(int i=0; i<NUMERO_PRODUTTORI; i++){
        int pid=fork(); 
            
            if(pid<0){
                perror("Errore fork produttori\n"); 
                    exit(1);
            }

            if(pid==0){
                printf("Figlio produttore\n"); 
                //Specifico il seme usando il pid del processo e il tempo
                srand(getpid()*time(NULL)); 
                produttore(punt, semID);
                exit(0);
            }
    }

    //Il padre aspetta tutti i suoi figli!

    for(int i=0; i<NUMERO_PRODUTTORI+NUMERO_CONSUMATORI; i++){
        wait(NULL); 
    }
    

    printf("#########################################\n"); 
    printf("Tutto concluso, cancello tutte le memorie e i semafori!\n"); 

    shmctl(shmID, IPC_RMID, 0); 
    semctl(semID, 0, IPC_RMID);
     

}