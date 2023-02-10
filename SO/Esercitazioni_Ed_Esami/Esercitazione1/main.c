//Programma principale, alloca le risorse e "chiama" gli altri programmi
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

#include "semafor.h"


int main(){

    pid_t pid;

    srand(time(NULL));

    //Definizione casuale della dimensione della stringa

    int numero = rand()%6 + 10; 

    //Ottengo la memoria che contiene la stringa

    int chiaveString  = ftok(".", 'a'); 

    int stringID = shmget(chiaveString, numero*sizeof(char), IPC_CREAT|0664); 

    char* stringa = (char*) shmat(stringID, NULL, 0); 

    printf("Ho ottenuto la memoria che contiene la stringa\n"); 
    printf("Descrittore: %d\n", stringID); 
    printf("Chiave: %d\n", chiaveString);
    printf("Locazione: %p\n", stringa);

    printf("#########################################\n");

    sleep(1);

    //Definisco la memoria che contiene la struttura 

    int struttChiave = ftok(".", 'b'); 

    int struttID=shmget(struttChiave, sizeof(insieme), IPC_CREAT|0660);

    insieme* p = shmat(struttID, NULL, 0); 

    //Inizializzo i valori nell'insieme
    p->dimensione=numero;
    p->Num_Lettori=0;

    printf("Memoria creata ed inizializzata\n");
    printf("Descrittore: %d\n", struttID); 
    printf("Chiave: %d\n",  struttChiave);
    printf("Locazione: %p\n", p);

    printf("######################################\n");

    sleep(1);

    //Definisco i semafori di cui ho bisogno!

    int semChiave=ftok(".", 'c'); 

    int semID=semget(semChiave, 3, IPC_CREAT|0664);

    //Inizializzo i valori dei semafori!
    //Li metto tutti ad uno, così il primo che arriva sa già dove andare!
    semctl(semID, MUTEX_L, SETVAL, 1); 
    semctl(semID, MUTEX_L1, SETVAL, 1);
    semctl(semID, SYNCH, SETVAL, 1);

    printf("Semafori inizializzati\n"); 

    printf("-------------------------------------------------\n"); 

    sleep(1);


    //A queto punto devo andare a chiamare i vari processi!
    pid=vfork(); 

        if(pid==0){
            //printf("Programma generatore!\n");
            //chiamo il programma generatore
            execl("gen", "./gen", NULL); 
        }

 
    
    //Chiamo i processi "lettori!"
    pid=vfork(); 

        if(pid==0){
            //printf("Programma elaboratore!\n");
            execl("elabor",  "./elabor", NULL);
        }


   
    for(int i=0; i<2; i++){
        pid=vfork(); 
            if(pid==0){
                //printf("Programma analizzatore %d\n", i+1);
                execl("analizz", "./analizz", NULL);
            }
    }


    //Il programma principale attende che terminino tutti i processi!
    for(int i=0; i<4; i++){
        wait(NULL);
    }


    //Il programma principale dealloca le risorse!
    shmctl(struttID, IPC_RMID, 0);
    shmctl(stringID, IPC_RMID, 0);
    semctl(semID, 0, IPC_RMID);

}