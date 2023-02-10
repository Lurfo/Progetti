//Definizione delle funzioni di produzione e consumazione
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "function.h"
#include "semafor.h"


void produttore(buffer* mem, int semID){

    //Questo valore è quello che mi occore per andare a trovare la posizione in cui andare a leggere o scrivere all'interno del
    //buffer di memoria!
    int indice=0;

    //Come prima cosa il produttore deve effettuare una wait sul semaforo che definisce se il messaggio è disponibile
    wait_sem(semID, SPAZIO_DISPONIBILE);   


        //A questo punto si avvia la sezione critica, in questo caso però, non vado ad operare sul vettore che contiene
        //gli elementi ma vado direttamente ad operare sul vettore di stato, così da ottenere la posizione che mi occorre
        //in cui andare ad inserire l'elemento!

        //In questo caso il produttore oper in mutua esclusione sul vettore di stato!

        wait_sem(semID, MUTEX_P);
            
            //Con il while trovo nel vettore la posizione del primo elemento disponibile nell'array!
            while(indice<=DIM && mem->vetto[indice]!=BUFFER_VUOTO){
                indice++;
            }  

            //A questo punto dico che quella posizione del buffer è in uso!

            mem->vetto[indice] = SPAZIO_IN_USO;

        //Ho dunque concluso la sezione critica, posso fare la signal

       
        signal_sem(semID, MUTEX_P);

    //In questo caso, posso ANDARE AD OPERARE LIBERAMENTE SUL VETTORE DI STATO PERCHÈ IL MIO PROCESSO HA ORMAI ESCLUSIVA
    //DELLA POSIZIONE DEL VETTORE!

    //Posso andare ad inserire il valore nella posizione INDICE, del buffer che deve contenere gli elementi

    sleep(2);

    mem->buffer[indice]=rand()%100 + 1;

        printf("Prodotto il valore: %d, nella posizione %d\n", mem->buffer[indice], indice); 
    
    //A questo punto dico che la posizine indice è occupata da un valore

    mem->vetto[indice]=SPAZIO_PIENO;

    //Posso quindi finire con il fare una signal sul semaforo che segnala ai consumatori che il messaggio è disponibile

    signal_sem(semID, MESSAGGIO_DISPONIBILE);

}



//Specifica della funzione del consumatore, che agisce in modo molto simile!
void consumatore(buffer* mem, int semID){

    int indice = 0; 

    //Fa una wait per vedere se ho il messaggio a disponibile
    wait_sem(semID, MESSAGGIO_DISPONIBILE);

        //Dunque faccio una wait, per vedere se posso accedere al vettore di stato1
        wait_sem(semID, MUTEX_C);


            while(indice<=DIM && mem->vetto[indice]!=SPAZIO_PIENO){
                indice++;
            }

            //A questo punto dico che lo spazio è in uso
            mem->vetto[indice]=SPAZIO_IN_USO;

        signal_sem(semID, MUTEX_C);

    sleep(2);

    //Posso operare liberamente sul vettore e sul buffer a questo punto
    printf("Nella posizione %d, è contenuto il valore: %d\n", indice, mem->buffer[indice]);
    
    //Dico dunque che la posizione è libera
    mem->vetto[indice]=BUFFER_VUOTO;

    //Posso quindi concludere il mio consumatore!
    //Faccio un signal per definire che è disponibile uno spazio nel vettore!
    signal_sem(semID, SPAZIO_DISPONIBILE);

}

