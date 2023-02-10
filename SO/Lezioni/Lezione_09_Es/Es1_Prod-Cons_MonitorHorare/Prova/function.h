//Definizione delle funzioni di produzione e consumazione
#ifndef FUNCTION_H
#define FUNCTION_H

#include "monitor_hoare.h"

//Specifico, tramite una macro, l'id delle variabili condition che devo sfruttare
//id, che rappresenta anche il numero del semaforo ad essa associato
#define VARCOND_PRODUTTORI 0    //A questa assegno l'id 0 (quindi il semaforo associato sarà il primo)
#define VARCOND_CONSUMATORI 1   //A questa l'id 1 (quindi il semaforo associtato sarà il secondo)

//Mi faccio una macro dove specifico il numero di variabili condition
#define NUMVAR 2

//In questo caso, devo definre una struttura!
//Nella quale ho:
typedef struct{
  
    //Il buffer dove inserisco il valore
    int buffer; 

    //Specifico le variabili condition 
  
    int buffer_libero; //1 se libero, 0 se occupato
  
    //Indica se nel buffer è già presente un valore prodotto da un altro processo
    int buffer_occupato; //0 se libero, 1 se occupato

    //A questo punto, siccome ho che il monitor mi deve proteggere questa struttura, lo vado ad inserire al suo interno!     
    Monitor m;

}Strut;


//Mi definisco la funzione di produzione, che prende in ingresso il valore che devo inserire nel buffer
void Produco(Strut* pc, int valore);

//La funzione di consumazione mi restituisce il valore!
int Consumo(Strut* pc);


#endif



