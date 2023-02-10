//Definizione di un programma semplice da andare a compilare tramite makefile 
#include <stdio.h>
#include <stdlib.h>
//Includo la mia libreria, che si comprende di una sola funzione
#include "libreria.h"
#include <time.h>

//In c per andare a definire un array, orroccorre specifica una struct, poichè non ho gli oggetti

typedef struct arr{
    //La struct deve contenere un puntatore ad un intero, il primo elemento dell'array e la sua dimensione!
    int* a;
    int dim;
} array; //Usando il type def, so che ogni volta che scrivo array, creo questa tipologia di struct!


//Alla funzione di inserimento e di visualizzazione del contenuto devo passargli il puntatore alla struct che ho creato nel main!
void alloco(array*);
void vedo(array*);

int main(){

    srand(time(NULL));

    array numeri;

    printf("Sono il programma compilato tramite makefile\n");

    int dim;

    printf("Dimmi quanti numeri vuoi che ti salvi\n"); 
    scanf("%d", &dim);
    
    //Salvo la dimensione dell'array nella mia struct
    numeri.dim=dim;

    alloco(&numeri);

    printf("Ti mostro a video i numeri che hai scelto\n");

    vedo(&numeri);

    printf("\n");

    //Poichè la funzione conteggio non opera con un array, allora non faccio altro che passargli i contenuti della struct!
    printf("La loro somma corrisponde a: %d\n", conteggio(numeri.a, numeri.dim));

    printf("Il loro prodotto è uguale a: %d\n", prodotto(numeri.a, numeri.dim));

    printf("La somma dei numeri pari è uguale a: %d\n", somma_pari(numeri.a, numeri.dim));

   free(numeri.a);

}

void alloco(array* num){
    //Uso la funzione malloc per allocare la memoria necessaria per contenere i miei numeri!
    //(Lo stesso funzionamento della funzione new in c, ora ho che "a" punta alla prima locazione di memoria dove sono
    //conservati i miei numeri!)

    num->a = malloc(num->dim*sizeof(int));

    for(int i=0; i<num->dim; i++){
        num->a[i]=1+rand()%100;
    }

    return;

}

void vedo(array* num){
    
    for(int i=0; i<num->dim; i++){
        printf("%d, ", num->a[i]);
    }
}