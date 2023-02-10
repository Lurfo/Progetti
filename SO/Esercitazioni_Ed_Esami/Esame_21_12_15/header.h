#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef HEADER_H
#define HEADER_H

#define DIM 10


//Imposto le strutture che mi occorrono

//Struttura che contiene il messaggio
typedef struct { 
    
    int indirizzo; 
 
    int dato; 

} Buffer; 

//Struttura per la gestione della coda circolare
typedef struct { 
    Buffer vettore[DIM]; 

     // ... inserire qui variabili aggiuntive per la sincronizzazione ... 

    //Puntatore test e coda
    int testa;
    int coda; 

    //Variabile di controllo 
    int numOccupati;

    //Imposto le variabili per il monitor 
    pthread_mutex_t mutex;

    pthread_cond_t vc_produttori; 
    
    //pthread_cond_t vc_consumatori; //Controllare bene uso di questa condizione

} GestioneIO; 

void Inizializza(GestioneIO * g, pthread_attr_t *attr); 
void rimuovi(GestioneIO *g, pthread_attr_t *attr);
void Produci(GestioneIO * g, Buffer * b); 
int Consuma(GestioneIO * g, Buffer * b);



#endif