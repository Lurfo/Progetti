//Specifico le funzioni di produttore e consumatore!
#include "function.h"
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


//Nel caso del produttore, ho anche il messaggio
void produttore(int coda, char* mess){

    //Il produttore genera un nuovo messaggio
    Messaggio m;

    //Imposto il tipo del messaggio, scelgo di usare il pid
    m.type=getpid();

    //Faccio una copia del valore di mess, nella stringa del messaggio
    strcpy(m.string, mess); 

    //Invoco la funzione di invio, che se trova la coda piena, non deve continuare ad inviare messaggi!
    //In questo, vedo che devo effettuare un casting a puntatore a void, per poter passare alla funione il messaggio che deve
    //inserire nela code
    //Imposto che se la coda è piena, il processo non deve arrestarsi
    if(msgsnd(coda, (void*)(&m), size, IPC_NOWAIT)<0){
        perror("Coda piena\n"); 
            exit(1);
    }

    printf("Messaggio inviato!\n");
}

//Al consumatore, basta anche solo l'info della coda da cui andare a leggere il messaggio
void constumatore(int coda){
    //Anche il consumatore definisce una sua struttura per "Accogliere" il messaggio 
    Messaggio m; 

    //Uso dunque la funzione recieve!
    //In questo caso, uso il valore speciale 0 per prelevare il primo messaggio dalla coda
    //Imposto il flag 0 che mi definisce che è una receive bloccante, blocca il processo fino a che non arriva un messaggio
    msgrcv(coda, (void*) (&m), size, 0, 0);

    //Stampo a video il messaggio che ho letto;     
    printf("Messaggio: '%s'\n", m.string);

}
