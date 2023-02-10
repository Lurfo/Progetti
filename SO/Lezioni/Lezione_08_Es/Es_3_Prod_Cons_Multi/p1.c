//Definzione del processo produttore
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>

#include "function.h"

int main(){

    printf("Ciao, sono il processo P1\n");

    //Ottengo la chiave della coda
    key_t k_msg = ftok(PATH, CHAR); 

    //Ottengo id della coda

    int queue = msgget(k_msg, 0);

    if(queue<0){
        perror("Errore msgget p1\n");
            exit(1);
    }

    //A questo punto, scrivo 11 volte all'interno del messaggio che mi interessa!

    //Definisco il mio messaggio
    Messaggio m; 

    //Imposto il tipo di messaggio, specifico quale processo sono
    m.process=P1;

    srand((time(NULL)));

    for(int i=0; i<11; i++){
        //genero il numero casuale
        m.numero=generoFloat(1, 11);

        printf("Invio del messaggio da %d, contenente: %f\n", P1, m.numero);

        //Invio il messaggio alla queue 
        msgsnd(queue, (void*)(&m), SIZE, 0);

        //Faccio una sleep per sincronizzare
        sleep(1);

    }

    printf("P1, ha mandato tutti i messaggi\n");


    return 0;


}