#include <errno.h>
#include <stdio.h>

#include "semafor.h"


//Definizione della funzione wait
int wait_sem(int semid, int sem_num){
    //Definisco la struct su cui deve agire la funzione semop
    //Struct che viene inclusa nella libreria sem.h!
    struct sembuf sem_buf;

    //Segno il numero del semaforo su cui devo essettuare l'operazione, ricordando che ho a disposizione un array di semafori!
    sem_buf.sem_num=sem_num;

    //Imposto i flag come nulli
    sem_buf.sem_flg=0;

    //Imposto il valore di sem_op, in base all'operazione che voglio svolgere, siccome è una wait, allora il suo valore
    //deve essere <0!
    sem_buf.sem_op=-1;

    //A questo punto, per svolgere l'operazione devo chiamare la funzione di semop!
    if(semop(semid, &sem_buf, 1)<0){
        return -1;
    }    

    //La funzione semop, prende in ingresso: 
    //  -L'id del semaforo, in modo che sa a che semaforo sto facendo riferimento!
    //  -La Struct sembuf, in modo che riesce ad estrapolare tutti i dati che sono in essa contenuti!
    //  -Infine il numero di struct presenti, poichè potrei effettuare operazioni anche su più semafori!

    //A questo punto, inserisco la funzione semop, in una struttura di controllo, essa infatti restituisce come valore 
    //-1 in caso di errore, così posso controllare la correttezza dell'operazione!

    //Se tutto è corretto, restituisco il valore 0!
    else{
        return 0;
    }

    

   
}

//Definizione della funzione signal, che ha una struttura molto simile!
int signal_sem(int semid, int sem_num){
    //Definizione della struct su cui andare a modificare i valori per esprimere la funzione 
    struct sembuf sem_buf;

    sem_buf.sem_num=sem_num;
    sem_buf.sem_flg=0; 

    //Stavolta, per espimere l'operazione di signal, devo andare a porre come valore di sem_op, un valore maggiore di 0!
    sem_buf.sem_op=1;


    //Esecuzione della funione semop, e controllo del suo risultato!
    if(semop(semid, &sem_buf, 1)<0){
        return -1; 
    }

    else{
        //In caso sia andatto tutto per il megio ritorno 0!
        return 0;
    }

}
