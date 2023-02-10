//Nell'header, specifico la struttura di produttore e consumatore, ed inoltre specifico anche le variabili condition 
//che mi occorrono

#include <pthread.h>

#ifndef FUNCTION_H
#define FUNCTION_H

//Definisco anche il numero di thread che voglio creare
#define NUM_THREAD 10

//Nella strutturadevo inserire tutte le informazioni che devono essere "passate" ai vari thread!
typedef struct{

    //Stanzio una variabile mutex per il thread
    //Che poi mi occorre per il monitior!
    pthread_mutex_t mutex;

    //Stanzio le due variabili condition per i thread, una per i produttori ed una per i consumatori
    pthread_cond_t v_prd;
    pthread_cond_t v_cns;

    //Inserisco poi due variabili di controlo
    int ok_produzione; 
    int ok_consumo;

    //Oltre questi valori, devo anche andare ad inserire il mio messaggi
    int msg;

}data;


//Posso poi andare a considerare le funzioni di starting point dei thread produttori e consumatori
//Essi devono ricevere come argomento la struttura di tipo data che ho definito sopra!
void * consumatore(void *arg); 
void * produttore (void *arg);



#endif
