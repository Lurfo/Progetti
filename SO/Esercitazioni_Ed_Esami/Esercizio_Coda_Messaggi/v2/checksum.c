//Definizione del processo checksum
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

    //Devo prima vedere quanti messaggi il checksum deve analizzare
    //La funzione atoi, serve a convertire il carattere in un intero!
    int a = atoi(argv[1]); 

    printf("Sono il Checksum, devo controllare %d messaggi\n", a);


    Messaggio mess;
    
    //Ottengo la chiave della coda di messaggi
    key_t kMsg = ftok(PATH, CHAR);

    if(kMsg<0){
        perror("Erroe della ftok del checksum\n"); 
            exit(1);
    }

    //Id della coda
    //Metto 0 come flag perchè la coda è stata creata già
    int idMsg = msgget(kMsg, 0);

    if(idMsg<0){
        perror("Errore msgget checksum\n");
            exit(1);
    }

/*
    printf("+Chiave della coda: %d\n", kMsg); 
    printf("+Id della coda %d\n", idMsg);
*/

    //Ottenuta la coda anche per il checksum, posso andare ad eseguire il suo funzionamento
    //NOTA CHE: Il processo checksum, deve eseguire per tante volte quanti sono stati i valori inviati dal processo filtro!
    for(int i=0; i<a; i++){

        sleep(1);

        //Posso fare una receive non bloccante, perchè il processo filtro ha già concluso il suo lavoro
        if(msgrcv(idMsg, (void*)(&mess), SIZE, TYPE_FILTRO, IPC_NOWAIT)>0){
        
           /*
            printf("++++++++++++++++++++++\n");
            printf("+Trovato messaggio\n");
            printf("Stringa: %s\n", mess.string);
           */ 
          
            //printf("+Ho i valori: %d, %d\n", mess.arr[0], mess.arr[1]);
            
            //Se arrivo qui, ho trovato il messaggio, effettuo quindi la somma
            mess.var = mess.arr[0] + mess.arr[1];

            //printf("+Valore finale: %d\n", mess.var);
            
            for(int j=0; j<MAX; j++){
                //Faccio quindi la somma dei caratteri
                mess.var+= (int) mess.string[j];
            }

            //printf("+Finita somma: %d\n", mess.var);

            //Modifico il tipo del messaggio
            mess.type=TYPE_CHECKSUM;

            //Spedisco nuovamente il messaggio
            msgsnd(idMsg, (void*)(&mess), SIZE, 0);

            //printf("+Messaggio inviato\n");
        }

    }

    char string[50];

    snprintf(string, sizeof(string), "%d", a);


    //Il processo checksum a questo punto, deve chiamare il processo visualizzatore
    pid_t pid = vfork(); 

    if(pid<0){
        perror("Errore della vfork del processo visualizzatore\n");
            exit(1);
    }

    if(pid==0){
        //Posso quindi chiamare il processo visualizzatore
        //anche al processo visualizzatore, devo inviare il numero di messaggi che sono presenti nella coda

        if(execl("./visualizzatore", "./visualizzatore", string, NULL)<0){
            perror("Errore exec del processo visualizzatore\n"); 
                exit(1);
        }
    }

    //Il processo checksum, aspetta che il processi visualizzatore sia concluso
    printf("Il processo visualizzatore %d, si è arrestato\n", wait(NULL));


}