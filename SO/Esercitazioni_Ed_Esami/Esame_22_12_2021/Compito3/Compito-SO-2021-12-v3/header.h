#ifndef _HEADER_
#define _HEADER_

#include <pthread.h>

//Definisco le variabili che mi occorono per generare la chiave della coda di messaggi
#define PATH "."
#define CHAR 'a'

/* TBD: Definire qui una struttura dati per i messaggi */
//Imposto anche una macro per la  dimensione e per il tipo del messaggio
#define STD_TYPE 1 

#define SIZE(x) sizeof(x)-sizeof(long)

//Struttura del messaggio
typedef struct{
    long type; 

    //Il messaggio deve essere di tipo intero
    int val;

}Mess;

typedef struct {

    int valore;
    
    /* TBD: Estendere questa struttura, in modo da realizzare la 
     *      mutua esclusione per l'accesso al valore
     */

    //I thread devono operare in mutua esclusione sul valore, dunque devo aggiunger eun mutex
    pthread_mutex_t mutex; 

    //Utilizzo dunqune un mutex per poter impostare i valori


} BufferMutuaEsclusione;

#endif
