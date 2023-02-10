#ifndef _PRODCONS_H_
#define _PRODCONS_H_

#include "monitor_hoare.h"

#define DIM 10

/* TBD: Definire delle macro per identificare le variabili condition */
//Imposto due vc, una per produttori ed una per consumatori
#define VC_Produttori 0
#define VC_Consumatori 1

#define NUM 2




typedef struct {
   
    long vettore[DIM];

    /* TBD: Definire il Monitor e le altre variabili per la sincronizzazione */

    //Imposto i puntatori di testa e di coda per andare a modificare il valore dell
    
} ProdCons;



void inizializza(ProdCons * p);
void consuma(ProdCons * p);
void produci(ProdCons * p, int val);
void rimuovi(ProdCons * p);

#endif
