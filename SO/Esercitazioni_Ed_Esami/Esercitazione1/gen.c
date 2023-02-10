//Definizione del processo che va ad inserire le lettere nella memoria!
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <time.h>

#include "semafor.h"

int main(int argc, char* argv){

    //Ottengo i valori delle memorie
    
    //Definisco la memoria che contiene la struttura 

    int struttChiave = ftok(".", 'b'); 

    int struttID=shmget(struttChiave, sizeof(insieme), 0);

    insieme* p = shmat(struttID, NULL, 0); 

    int dimensione = p->dimensione;

    /*printf("Memoria creata ed inizializzata\n");
    printf("Descrittore: %d\n", struttID); 
    printf("Chiave: %d\n",  struttChiave);
    printf("Locazione: %p", p);*/


    //Ottengo la memoria che contiene la stringa

    int chiaveString  = ftok(".", 'a'); 

    int stringID = shmget(chiaveString, (dimensione)*sizeof(char), 0); 

    char* stringa = (char*) shmat(stringID, NULL, 0); 

   /* printf("Ho ottenuto la memoria che contiene la stringa\n");
    printf("Ho ottenuto la memoria che contiene la stringa\n"); 
    printf("Descrittore: %d\n", stringID); 
    printf("Chiave: %d\n", chiaveString);
    printf("Locazione: %p", stringa); */

    

    //Definisco i semafori di cui ho bisogno!

    int semChiave=ftok(".", 'c'); 

    int semID=semget(semChiave, 3, 0);


    //Imposto il seed per i numeri casuali
    srand(time(NULL));


    //Proseguo con il compito che deve svolgere il programma!


    for(int i=0; i<VOLTE; i++){



        wait_sem(semID, SYNCH); 

            for(int i=0; i<dimensione; i++){
                sleep(1); 
                stringa[i] = 'a'+(rand()%26);
                printf("Ho inserito il valore: %c\n", stringa[i]);
            }

        printf("Il generatore ha finito\n"); 
        printf("----------------------------------\n");

        signal_sem(semID, SYNCH);

        sleep(3);

    }



}