#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

//Includo l'header
#include "header.h"

int main(){
    //Definisco la coda di messaggi
    key_t kMsg = ftok(PATH, CHAR); 

    if(kMsg<0){
        perror("Erroe della ftok del programma principale\n"); 
            exit(1);
    }
    
    //Ottengo l'id della coda 
    int idMsg = msgget(kMsg, IPC_CREAT|0660);

    if(idMsg<0){
        perror("Errore nella Creazione della coda di messaggi\n"); 
            exit(1);
    }


    //A questo punto, posso andare a generare i processi generatori e il processo filtro!

    pid_t pid; 

    for(int i=0; i<NUM_GENERATORI; i++){

        char string[4]; 

        snprintf(string, sizeof(string), "%d", i+1);

        pid = vfork();

        if(pid<0){
            perror("Errore nella creazione del generatore\n"); 
                exit(1);
        }

        if(pid==0){

            if(execl("./generatore", "./generatore", string, NULL)<0){
              
                perror("Errore exec del generatore\n");
                    exit(1);

            }
        }

    }

    //Posso poi andare a definire il processo filtro
    pid = vfork(); 

    if(pid<0){
        perror("Errore nel vfork del filtro\n"); 
            exit(1);
    }

    if(pid==0){
        if(execl("./filtro", "./filtro", NULL)<0){
            perror("Errore exec del filtro\n");
                exit(1);
        }
    }

    //Il main, deve aspettare la terminazione di tutti i processi per poi rimuovere la coda dei messaggi
    //in particolare, il main, termina dopo tutti i processi poichè deve aspettare il filtro, che a sua volta deve 
    //attendere la terminazione del checksum e così via
    //Dunque il main, sarà sempre l'ultimo a terminare!
    for(int i=0; i<NUM_GENERATORI+1; i++){
        printf("Si è concluso il processo: %d\n", wait(NULL));
    }

    //Posso andare ad eliminare la coda dei messaggi
    msgctl(idMsg, IPC_RMID, NULL);


}