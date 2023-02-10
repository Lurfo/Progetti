#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/shm.h>

#include "function.h"
#include "semafor.h"


int main(){

    pid_t pid;

    //Definisco la memoria cond 
    int memID=shmget(IPC_PRIVATE, sizeof(buffer), IPC_CREAT|IPC_EXCL|0664); 

    //Puntatore alla memoria 
    buffer* mem = (buffer*) shmat(memID, NULL, 0); 

    //Inizializzo i valori 
    mem->Num_Lettori=0;
    mem->Num_Scrittori=0;
    mem->numero=0; 

    //Definizione dei semafori

    int semID=semget(IPC_PRIVATE, 4, IPC_CREAT|IPC_EXCL|0664); 

    //Inizializzo i valori
    //Li devo impostare tutti al valore 1!
    semctl(semID, MUTEXL, SETVAL, 1);
    semctl(semID, MUTEXS, SETVAL, 1);
    semctl(semID, MUTEX, SETVAL, 1);
    semctl(semID, SYNCH, SETVAL, 1);

    //Passo alla creazione dei processi!


    for(int i=0; i<TOT; i++){
     
         pid=fork(); 
            
            if(pid==0){

                //Se i è pari creo uno scrittore, altrimenti un lettore 
                if((i%2)==0){
                    srand(getpid()*time(NULL));
                    printf("Creo Scrittore, con pid: %d\n", getpid()); 
                    scrittori(mem, semID);
                }

                else{
                    printf("Creo Lettore, con pid: %d\n", getpid()); 
                    lettori(mem, semID);
                }

                //Faccio una exit
                exit(0);

            }
    }

    //Il padre attende la terminazione
    for(int i=0; i<TOT; i++){
        wait(NULL);
    }

    //Rimuovo tutte le risorse condivise
    semctl(semID, 0, IPC_RMID);
    shmctl(memID, IPC_RMID, 0); 
    
    



}