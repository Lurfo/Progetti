//Definizione del processo visualizzatore
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

int main(int argc, char* argv[]){

    //Ottento il numero di messaggi nella coda
    int a = atoi(argv[1]);

    printf("Ti devo visualizzare %d messaggi\n", a);

    Messaggio mess;
    
    //Ottengo la chiave della coda di messaggi
    key_t kMsg = ftok(PATH, CHAR);


    if(kMsg<0){
        perror("Erroe della ftok del visualizzatore\n"); 
            exit(1);
    }


    //Id della coda
    //Metto 0 come flag perchè la coda è stata creata già
    int idMsg = msgget(kMsg, 0);

    if(idMsg<0){
        perror("Errore msgget visualizzatore\n");
            exit(1);
    }

    //Passo alla specifica della funzionalità del programma visualizzatore
    for(int i=0; i<a; i++){

        sleep(1);

        if(msgrcv(idMsg, (void*)(&mess), SIZE, TYPE_CHECKSUM, IPC_NOWAIT)>0){

            //Se sono qui, vuol dire che ho ricevuto il messaggio
            printf("++++++++++++++++++++++++++\n");
            printf("Ho ottenuto il messaggio: %ld\n", mess.type);
            printf("Stringa: %s\nValori Array: %d, %d\nValore Finale: %d\n", mess.string, mess.arr[0], mess.arr[1], mess.var); 
        }

    }

}