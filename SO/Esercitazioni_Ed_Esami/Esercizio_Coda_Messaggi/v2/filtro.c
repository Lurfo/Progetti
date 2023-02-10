//Specifica del filtro
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <string.h>


//Includo l'header
#include "header.h"


int main(int argc, char* argv[]){

    printf("Sono il filtro, controllo i messaggi\n");

    Messaggio mess;
    
    //Ottengo la chiave della coda di messaggi
    key_t kMsg = ftok(PATH, CHAR);

    if(kMsg<0){
        perror("Erroe della ftok del filtro\n"); 
            exit(1);
    }

    //Id della coda
    //Metto 0 come flag perchè la coda è stata creata già
    int idMsg = msgget(kMsg, 0);

    if(idMsg<0){
        perror("Errore msgget filtro\n");
            exit(1);
    }

/*
    printf("Chiave della coda: %d\n", kMsg); 
    printf("Id della coda %d\n", idMsg);
*/

    //Definizione del lavoro del filtro

    //Imposto una variabile contatore!
    //La variabile di conteggio, mi serve per comunicare al processo successivo, quanti messaggi sono inseriti nella coda
    int cont=0;
    
    //Controllo la lista per quante volte i processi inviano dei messaggi
    for(int i=0; i<NUM_GENERATORI*NUM_INVII; i++){

        //In particolare, posso fare in modo che il processo filtro, faccia una receive bloccante
        //questo perchè il processo filtro deve sempre controllare tutti i messaggi che gli arrivano dal processo generatore
        msgrcv(idMsg, (void*)(&mess), SIZE, TYPE_GENERATOR, 0);

        //printf("~Ho trovato il messaggio\n");

        //Cerco il carattere x nel messaggio

        if(strchr(mess.string, 'x')!=NULL){

            //printf("~Sono nell'if del filtro!\n");

            //Se sono qui vuol dire che ho incontrato una stringa con la x
            //Cambio il tipo del messaggio e lo invio al prossimo
            mess.type=TYPE_FILTRO;

            //Posso quindi inviare il messaggio
            msgsnd(idMsg, (void*) (&mess), SIZE, IPC_NOWAIT);

            cont++;

            //printf("~Messaggio passato attraverso il filtro: %d\n", cont);

        }
    }

    //Per poter passare il valore della variabile conteggio al successivo processo che verrà eseguito
    //devo sfruttare la funzione snprintf, che va a scrivere all'interno della stringa il valore dell'intero
    //che ho ottenuto dal conteggio
    char string[100]; 

    snprintf(string, sizeof(string), "%d" , cont);

    //A questo punto, il generatore, deve andare a "chiamare", il processo filtro
    pid_t pid = vfork(); 

    if(pid<0){
        perror("Errore vfork del processo checksum\n"); 
            exit(1);
    }

    if(pid==0){
        //Posso eseguire l'exec del processo checksum
        if(execl("./checksum", "./checksum", string, NULL)<0){
            perror("Errore exec del processo checksum\n");
                exit(1);

        }
    }

    //Il processo attendeche finisca il check sum!
    printf("È terminato il processo checksum: %d\n", wait(NULL));

}