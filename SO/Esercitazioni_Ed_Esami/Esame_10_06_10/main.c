#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>

#include "header.h"

#define  NUM_UTENTI 10

int main(){

    //Ottengo la memoria condivisa (chiave privata, condivisa tra processi padre e figlio)
    int idMem = shmget(IPC_PRIVATE, sizeof(MeteoM), IPC_CREAT|0660); 

        if(idMem<0){
            perror("Errore nella creazione della memoria\n"); 
                exit(1);
        }


    //Dunque ottengo il puntatore alla memoria 
    MeteoM *p = (MeteoM *) shmat(idMem, NULL, 0); 

        if(p==(void *)-1){
            perror("Errore attach della memoria\n"); 
                exit(1);
        }

    //Inizializzo il monitor 
    init_monitor(&(p->m), NUM_VC);


    //Dopo l'inizializzazione del monitor, genero i processi

    //Generazione del processo M
    pid_t pid; 


    pid = fork(); 

        if(pid<0){
            perror("Errore fork processo M\n"); 
                exit(1);
        }

        if(pid==0){

            printf ("[METEO %d] Gestore creato\n", getpid());

            meteo(p);

            exit(0);

        }

    //Genero i processi utenti
    for(int i=0; i<NUM_UTENTI; i++){

        pid=fork(); 

            if(pid<0){
                perror("Errore fork utenti\n"); 
                    exit(1);
            }

            if(pid==0){
                
                printf("[UTENTE %d] Utente %d creato\n", getpid(), i+1);

                utenti(p); 
                
                exit(0);

            }

    }


    //Attendo la terminazione dei processi
    for(int i=0; i<NUM_UTENTI+1; i++){
        wait(NULL);
    }

    //Rimuovo il monitor ed elimino la memoria
    remove_monitor(&(p->m)); 

    shmctl(idMem, IPC_RMID, 0);

    return 0;
}

