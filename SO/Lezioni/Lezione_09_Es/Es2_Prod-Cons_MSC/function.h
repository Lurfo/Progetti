//Signature delle funzioni di produzione e consumazione
#ifndef FUNCTION_H
#define FUNCTION_H

#include "monitor_signal_continue.h"


//Mi definisco l'id delle mie Var_Cond
#define VARCOND_PRODUTTORI 0
#define VARCOND_CONSUMATORI 1

//Mi definisco anche il numero di var_cond
#define NUM_VAR 2

//Specifica della struct
//La struttura è identica al caso del monitor di hoare!
typedef struct{
    
    int buff; 

    //Specifica delle variabili di buff libero e occupato
    int buff_libero; 
    int buff_occupato; 

    //Inserisco il monitor nella struttura 
    Monitor m;
}Buff;


void produttore(Buff* p, int val);
int consumo(Buff* p);

#endif