//Definizione di un programma semplice da andare a compilare tramite makefile 
#include <stdio.h>
#include <stdlib.h>
//Includo la mia libreria, che si comprende di una sola funzione
#include "libreria.h"
#include <time.h>


int main(){

    printf("Sono il programma compilato tramite makefile\n");

    //Questa dichiarazione di un array, non è un problema, per essere più preciso potrei però inserire i valori all'interno di una
    //struct, come fatto anche in "Dumping"
    int* numeri; 
    int dim;

    printf("Dimmi quanti numeri vuoi che ti salvi\n"); 
    scanf("%d", &dim);

    numeri = malloc(dim*sizeof(int));

    for(int i=0; i<dim; i++){
        numeri[i]=1+rand()%100;
    }

    printf("Ti mostro a video i numeri che hai scelto\n");

    for(int i=0; i<dim; i++){
        printf("%d, ", numeri[i]);
    }

    printf("\n");

    printf("La loro somma corrisponde a: %d\n", conteggio(numeri,dim));

    free(numeri);

}