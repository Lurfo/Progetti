#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>

#include "header.h"

#define NUM_MESSAGGI_DA_INVIARE 5

int main() {

    int ret;

    //Per ottenere l'id della coda, ottengo prima la chiave, tramite la funzione ftok
    key_t kMess = ftok(PATH, CHAR);

        if(kMess<0){
            perror("Errore fotk client\n"); 
                exit(1);
        }

    //Il flag è 0 perchè la coda è stata creata già dal processo main
    int id_coda = msgget(kMess, 0);

        if(id_coda<0){
            perror("Errore msgget client\n"); 
                exit(1);
        }

    printf("[CLIENT] Chiave: %d, Id: %d\n", kMess, id_coda);

    srand(getpid());

    //Definisco un messaggio e imposto il suo tipo
    Mess m; 

    m.type = STD_TYPE;
    
    for(int i=0; i<NUM_MESSAGGI_DA_INVIARE; i++) {

        int valore = rand() % 10;

        printf("[CLIENT] Invio: %d\n", valore);

        //Imposto il valore del messaggio
        m.val=valore;

        /* TBD: Inviare il valore tramite un messaggio */
        //Effettuo una semplice send del messaggio sulla coda
        ret = msgsnd(id_coda, (void *) &m, SIZE(Mess), 0); 

            if(ret<0){
                perror("Erorre send del valore al server\n"); 
                    exit(1);
            }
    }

    return 0;

}
