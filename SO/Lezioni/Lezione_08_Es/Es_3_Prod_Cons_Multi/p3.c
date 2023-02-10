//Definzione del processo consumatore
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

    printf("Ciao, sono il processo P3\n");

    //Definisco un array nel quale inserire tutti i valori che leggo, così da poter fare la media
    //Inizializzo i due valori come nulli
    float med[2] ={0,0};



    //Specifico il mio messaggio
    Messaggio m;

    //Accedo alla coda dei messaggi 
    key_t k_msg = ftok(PATH, CHAR); 

    //Ottengo id della coda

    int queue = msgget(k_msg, 0);

    if(queue<0){
        perror("Errore msgget p1\n");
            exit(1);
    }

    //Eseguo un ciclo pari alla somma dei due precedenti, in modo da poter leggere tutti i valori
    for(int i=0; i<22; i++){
        //Mi metto in attesa del messaggio sulla coda
        //Non mi interessa prendere un messaggio in particolare, volgio prendere il primo messaggio presente sulla coda
        //indipendentemente dal processo che lo ha inviato, effettuo dopo un controllo
        msgrcv(queue, (void*) (&m), SIZE, 0, 0);

        printf("Messaggio ricevuto da: %lu, contenuto: %f\n", m.process, m.numero);

        //Effettuo un controllo del tipo per vedere da che processo proviene
        if(m.process==P1){
            //Faccio la media delle volte che ho ricevuto da P1
            med[P1-1] += m.numero/11;
        }

        else{
            med[P2-1] += m.numero/11;
        }
    }

    //A questo punto, stampo a video il resoconto della media
    for(int i=0; i<2; i++){
        printf("Media di: %d = %f\n", i+1, med[i]);
    }
    

}