#include "libreria.h"

int conteggio(int* vettore, int dim){
    int somma=0; 

    for(int i=0; i<dim; i++){
        somma+=vettore[i];
    }

    return somma;

}