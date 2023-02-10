#include "libreria.h"
#include <stdio.h>

int conteggio(int* vettore, int dim){
    int somma=0; 

    for(int i=0; i<dim; i++){
        somma+=vettore[i];
    }

    return somma;

}

double prodotto(int* vetto, int dim){

    double prod=1;

    for(int i=0; i<dim; i++){
       prod = prod*vetto[i];
       printf("Il prodotto ha valore, per ora: %f\n", prod);
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