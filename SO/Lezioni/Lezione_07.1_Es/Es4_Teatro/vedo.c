//Definisco il programma che va a visualizzare i processi
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/wait.h>

#include "semafor.h"
#include "function.h"

int main(){
    //Definisco la memoria che contiene i posti
    key_t chiaveMem = ftok(".", 'a'); 
    
    //Ottengo il descrittore
    int memID = shmget(chiaveMem, 80*sizeof(seduta), 0); 

    //Ottengo il puntatore 
    seduta* punt = (seduta*) shmat(memID, NULL, 0); 
    
    printf("Memoria condivisa presa, ho trovato i posti!\n"); 

    //Definisco la memoria che contiene il numero di posti

    key_t chiaveDisp = ftok(".", 'c');

    //Id

    int dispID = shmget(chiaveDisp, sizeof(int), 0); 

    //Puntatore alla memoria

    int* disp = (int*) shmat(dispID,  NULL, 0);

    printf("Ho ottenuto la disponibilità di cose!\n"); 

    //Definsco il semaforo!

    key_t chiaveSem = ftok(".", 'b'); 

    //Ottengo id del semaforo!

    int semID=semget(chiaveSem, 4, 0);

    //Il programma deve prendere tutte le memorie e i semafori che sono stati già creati, per questo i fleg di semget e shmget
    //sono tutti nulli!

    printf("Ottenuto il semaforo che mi serve!\n");

    //Ora, quello che deve fare il programma, alla fine di ogni prenotazione, controllo i post



    for(int j=0; j<NUM_PROCESSI; j++){
    
    wait_sem(semID, ATTENDERE);

       // wait_sem(semID, MUTEX_DISPONIB); 
            printf("Ho una disponibilità di %d\n", *disp); 


        //wait_sem(semID, MUTEX_POSTO); 

            for(int i=0; i<DIM; i++){
                
                if(punt[i].stato==OCCUPATO){
                printf("Posto %d, occupato da: %d\n", i+1, punt[i].ID_cliente);
                }
            }

       // signal_sem(semID, MUTEX_POSTO); 
    
        //signal_sem(semID, MUTEX_DISPONIB);

    //signal_sem(semID, PROSEGUO);

    }


    



}