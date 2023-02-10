#ifndef FUNCTION_H
#define FUNCTION_H

#include "monitor_signal_continue.h"

//Definizione della dimensione massima del vettore che contiene gli elementi!
#define DIM_MAX 5

//Definisco i vari stati
#define LIBERO 0
#define OCCUPATO 1
#define IN_USO 2

//Definisco le variabili condition
#define VARCOND_PRODUTTRI 0
#define VARCOND_CONSUMATORI 1

#define NUM_VAR 2


typedef struct{

    //Definisco l'array che contiene gli elementi e il buffer di stato
    int buff[DIM_MAX];
    int stato[DIM_MAX];

    //Definisco le variabili che permettono di andare a considerare quanti posti sono occupati e quanti liberi
    int numero_occupati;
    int numero_liberi;

    //Mi tengo anche il monitor
    Monitor m;
}Buff;


void produttori(Buff* p, int valore);

int consuma(Buff* p);

#endif