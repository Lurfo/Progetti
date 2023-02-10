//Definisco il programma principale
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>

#include "semafor.h"
#include "function.h"

int main(){
    //Definisco la memoria cond
    int memID = shmget(IPC_PRIVATE, sizeof(buffer), IPC_CREAT|IPC_EXCL|0660); 

    //Ottengo il puntatore

    buffer* mem = (buffer*) shmat(memID, NULL, 0); 

    //Inizializzo i valori della memoria!
    mem->messaggio=0;
    mem->numLettori=0;

    //Inizializzo dunque i semafori!
    int semID = shmget(IPC_CREAT, 2, IPC_CREAT|IPC_EXCL|0660); 

    //inizializzo i semafori
    //Entrambi, devono essere sincronizzati ad 1! Il primo che arriva è quello che viene subito "servito"
    semctl(semID, MUTEXL, SETVAL, 1);
    semctl(semID, SYNCH, SETVAL, 1);

    //Inizio con la definizione di scrittori e lettori
    for(int i=0; i<VOLTE; i++){
        //Decido che quelli pari saranno scrittori e i dispari lettori
        int pid=fork();

            if(pid==0){
              
                if(i%2==0){
                    srand(getpid()*time(NULL));
                    printf("Creo processo Scrittore\n"); 
                        scrittore(mem, semID);
                }

                else{
                    printf("Creo figlio lettore\n"); 
                    lettore(mem, semID);
                }
                exit(0);

            }

    }

    for(int i=0; i<VOLTE; i++){
        wait(NULL);
    }

    printf("Processi conclusi, proseguo con la cancellazione di tutto\n");

    semctl(semID, 0, IPC_RMID);
    shmctl(memID, IPC_RMID, NULL);

}