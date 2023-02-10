//Nell'header, vado a definire le librerie da utilizzare, la struttura della variabile condivisa e anche la struttura
//del messaggio (oltre che l'eventuale tipo)
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>

//Utilizzo un semaforo per accedere in mutua esclusione alla risorsa!
#include "semafor.h"

#ifndef HEADER_H
#define HEADER_H

//Definizione del path e del carattere che mi occorrono per memoria e semaforo 
#define PATH "."

//Per la memoria
#define CHAR_M 'a'

//Per il semaforo
#define CHAR_S 'b'

#define CHAR_C 'c'

//Il tipo del messaggio può anche essere unico
#define SDT_TYPE 1

#define SIZE(x) sizeof(x)-sizeof(long)

//Mi definisco il numero di semafori
#define NUM_SEM 1

#define MUTEX 0

//Imposto il valore iniziale del semaforo, che deve essere 1 (Il primo server che arriva può già produrre)
#define VAL 1

//Definisco la struttura che deve avere la memoria condivisa
typedef struct{

    //La memoria condivisa, deve contenere due valori interi
    int val1;
    int val2; 

} Buffer;

//Definisco il messaggio
typedef struct{

    long type;

    //Il messaggio contiene poi due interi, che sono quelli che si vogliono impostare
    int val1; 
    int val2;

}Mess;



#endif