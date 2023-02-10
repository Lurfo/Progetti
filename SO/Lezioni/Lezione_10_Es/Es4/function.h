
#include <pthread.h>


#ifndef FUNCTION_H
#define FUNCTION_H

#define NUMTHREAD 10

#define MAX_LEN 10


//Definisco la struttura che mi occorre
typedef struct{

    //Il semaforo del monitor
    pthread_mutex_t mutex; 

    //Le variabili condition
    pthread_cond_t v_scritt; 
    pthread_cond_t v_lett; 

    //Le variabili di controllo che specificano quandi lettori o quandi scrittori sono già presenti nella struttura!
    int numScritt; 
    int numLett;

    //Oltre queste, inserisco anche altre due variabili, che mi tengono conto del numero di scrittori/lettori che sono in attesa
    int lett_wait; 
    int scritt_wait;

    //Infine definisco la mia variabile da andare a scrivere/leggere
    char str[MAX_LEN];

    int strlen;

}data;

//Definisco poi le starting function dei thread, una di lettura e una di scrittura
void * Scrittura( void *arg); 
void * Lettura(void *arg); 

#endif