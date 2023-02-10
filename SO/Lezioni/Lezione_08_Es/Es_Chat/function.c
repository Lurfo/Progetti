//Specifica delle funzioni di invio e di ricezione
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#include "function.h"


void invio(int queue_invio){
    //La funione di invio, effettua un while, mentre aspetta che l'utente invii il suo messaggio
    char string[MAX];

    //Mi definisco un messaggio che ha come pid quello del processo che invia il messaggio
    Messaggio m; 

    m.type=getpid();

    while(1){
        //Prendo in input dall'utente una stringa
        scanf("%[^\n]%*c", string);

        //Copio la stringa nel messaggio
        strcpy(m.string, string);

        //Effettuo un controllo sulla stringa, per vedere se essa è uguale ad EXIT
        if(strcmp(string, "EXIT")==0){
            printf("Chiudo la comunicazione\n");

            //Invio l'ultimo messaggio di exit
            msgsnd(queue_invio, (void*)(&m), SIZE, IPC_NOWAIT);
            //Interrompo il ciclo
            return;
        }

        

        //Altrimenti continuo con la ricezione 
        else{
            //In questo caso invio il messaggio senza problemi
           if(msgsnd(queue_invio, (void*)(&m), SIZE, IPC_NOWAIT)<0){
               perror("Errore send\n"); 
                exit(1);
           }
        }

    }

}



void ricezione(int queue_ricez){
    //La funzione di ricezione è molto simile 
    
    //Specifico il messaggio 
    

    //Effettuo un ciclo infinito
    while(1){

        Messaggio m; 

        //Mi metto in attesa del messaggio
        //Metto come type 0, poichè devo leggere un qualisi messaggio dalla indipendentemente dal suo tipo
        //Metto come flag 0 perchè la receive è bloccante, attendo sempre che arrivi un messaggio
        if(msgrcv(queue_ricez, (void*)(&m), SIZE, 0, 0)<0){
            perror("Errore msgrcv\n"); 
                exit(1);
        }

        //Faccio dunque un controllo del messaggio
        //Stampo il messaggio
        printf("                     %s\n", m.string);

        //Effettuo un controllo sul messaggio
        if(strcmp(m.string, "EXIT")==0){
            //Interrompo il ciclo se è uguale a EXIT
            printf("Il tuo interlocutore ha chiuso la chiamata!\n");
            return;
        }

    }



}