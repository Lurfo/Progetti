#include "libreria.h"
#include <stdio.h>

int conteggio(int* vettore, int dim){
    int somma=0; 

    for(int i=0; i<dim; i++){
        somma+=vettore[i];
    }

    return somma;

}

int prodotto(int* vetto, int dim){
    int prod=1;

    for(int i=0; i<dim; i++){
       prod = prod*vetto[i];
    }

    return prod;
}

int somma_pari(int* vett, int dim){

    int somma=0; 



    for(int i=0; i<dim; i++){

        if((i+1)%2==0){

            somma+=vett[i];

        }


    }

    return somma;

}