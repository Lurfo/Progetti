//Definizione del main
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


#include "header.h"

int main(){


    //Mi definisco la coda di messaggi, usando come chiave IPC_PRIVATE
    int idMess = msgget(IPC_PRIVATE, IPC_CREAT|0660); 

    if(idMess<0){
        perror("Errore della msgget\n");
            exit(1);
    }

    printf("Coda ottenuta: %d\n", idMess);

    //A questo punto, posso andare ad effettuare la creazione dei processi


    pid_t pid;

    for(int i=0; i<NUM_GENERATORI; i++){

        pid=fork(); 

        if(pid<0){
            perror("Errore fork generatori\n"); 
                exit(1);
        }

        if(pid==0){

            printf("Processo generatore: %d\n", getpid());

            //In questo caso, avvio i processi di generazione 
            generator(idMess);

            exit(0);

        }


    }





    //Creao il processo di filtro
    pid=fork(); 

    if(pid<0){
        perror("Errore fork filtro\n"); 
            exit(1);
    }

    if(pid==0){
      
        printf("Processo filtro: %d\n", getpid());

        //Faccio partire il filtro
        filtro(idMess);

        exit(0);

    }





    //Creo il processo check
    pid=fork(); 

    if(pid<0){
        perror("Errore fork check\n"); 
            exit(1);
    }

    if(pid==0){

        printf("Processo check: %d\n", getpid());

        //Creo il processo
        checksum(idMess);
        exit(0);
    }





    //Creo il processo visualizzazione 
    pid=fork(); 

    if(pid<0){
        perror("Errore creazione visualizzatore\n");
    }

    if(pid==0){

        printf("Processo visualizzatore: %d\n", getpid());
        //Visualizzatore
        visualizzatore(idMess);
        exit(0);

    }






    for(int i=0; i<NUM_GENERATORI+3; i++){
        printf("Si è concluso il processo: %d\n", wait(NULL));
    }

    //Rimuovo la coda di messaggi
    msgctl(idMess, IPC_RMID, NULL);

}