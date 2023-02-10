#ifndef FUNCTION_H
#define FUNCTION_H

#include "monitor_h.h"

//Specifico l'id delle mie var_cond
#define VARCOND_LETTORI 0
#define VARCOND_SCRITTORI 1

//Definisco la mia struttura, che contine il buffer, le che specificano il numero di lettori e scrittori e il monitor
typedef struct{

    int buffer;

    //Queste variabili sono necessarie poichè sto considernado la starvation di entrambi
    int num_lettori; 
    int num_scrittori;

    //Definisco il mio monitor
    Monitor m;

}Buff;

//Definisco le funzioni di produzione e consumazioni 
void Scrivi(Buff* punt, int val); 
int Lettura(Buff*);

#endif