#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <errno.h>

#include "function.h"


int main(){
    //Ottengo la chiave della coda dei messaggi
    //Uso i due parametri che ho definito prima, in modo da ottenere la chiave uniforme tra tutti gli eseguibili
    key_t k_msg = ftok(PATH, CHAR);

    int queue = msgget(k_msg, IPC_CREAT|0660);

    if(queue<0){
        perror("Errore id\n");
            exit(1);
    }

    //A questo punto, posso andare a chiamare in causa i due processi

    pid_t pid = vfork();

        if(pid==0){
            //Sono nel contesto del processo figlio, effettuo l'exec
            if(execl("./p1", "./p1", NULL)<0){
                perror("Errore exec\n");
                    exit(1);
            }
        }

        if(pid<0){
            perror("Errore vfork\n"); 
                exit(1);
        }


    pid=vfork(); 
        
       
        if(pid==0){
            if(execl("./p2", "./p2", NULL)<0){
                perror("Errore exec\n"); 
                    exit(1);
            }
        }


        if(pid<0){
            perror("Errore vfork\n"); 
                exit(1);
        }

   
    pid=vfork();
        
        if(pid==0){
            if(execl("./p3", "./p3", NULL)<0){
                perror("Errore exec\n"); 
                    exit(1);
            }
        }

      
        if(pid<0){
            perror("Errore vfork\n"); 
                exit(1);
        }
    
    //Ho quindi creato tutti i processi che mi servono per gestire il mio programma

    //Vado ad aspettare i processi

    int status;

    for(int i=0; i<3; i++){
        printf("Terminato il processo %d\n", wait(&status));
            if(!WIFEXITED(status)){
                perror("Terminato in malo modo\n");
                    exit(1);
            }
    }

    //Elimino la coda di messaggi che ho definito precedentemente
    msgctl(queue, IPC_RMID, NULL);

}