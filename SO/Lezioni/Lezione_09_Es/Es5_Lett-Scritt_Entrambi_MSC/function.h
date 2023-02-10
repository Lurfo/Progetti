//Definizione delle funzioni e delle strutture da utilizzare
#ifndef PROCEDURE_H
#define PROCEDURE_H

#include "monitor_signal_continue.h"

#define VARCON_LETTORI 0
#define VARCON_SCRITTORI 1

#define NUM_VARCOND 2

//Definizione della struttura che contiene gli elementi di cui ho bisogno
typedef struct{

    //Definisco il mio buffer
    int buff; 

    //Definisco le variabili che hanno il numero di lettori e scrittori
    int numLett; 
    int numScritt; 

    //Inserisco nella mia struttura il monitor
    Monitor m;


}Buff;


//Signatures
void scrivo(Buff* p, int valore); 

int leggo(Buff* p);

#endif