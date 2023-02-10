#include <stdlib.h>
#include <stdio.h>

//Devo aggiungere la libreria pthread per andarne ad usare le funzioni che racchiude
#include <pthread.h>

//Voglio creare 5 thread
#define NUM_THREAD 5 


//Mi definisco la starting function del thread!
//essa deve essere un puntatore a void
//Come argomento, essa ha un puntatore a void, proprio come richiesto dalla funzione pthread_create 
void* Print(void* IdThr);


int main(){

    //Come è buona norma, devo sempre andarmi a "salvare" l'id dei thread che stanno eseguendo, devo quindi creare un array
    //per contenere gli id di ogni thread!
    pthread_t IdThrd[NUM_THREAD];

    int stat;

    //NOTA: Per evitare delle problematiche ed errori durante il casting, devo usare come tipo per la variabile che mi tiene
    //conto del numero del thread, il tipo long!

    //Uso il for per andare a creare  i differenti thread!
    for(long i=0; i<NUM_THREAD; i++){

        //Vado a sfruttare la funzione pthread_create per andare a creare il mio thread
        stat = pthread_create( &IdThrd[i], NULL, Print, (void*) i);

        //La funzione riceve in input, l'indirizzo di memoria in cui inserire l'id del thread
        //Non ho la necessità di specificare degli attributi per il thread
        //Gli devo passare il nome della start_function, che è già un puntatore a void
        //Infine, sempre usando un casing a void*, gli devo passare anche gli argomenti che mi occorrono
        //Nel mio caso, gli devo inviare il numero di thread!

        if(stat){
            printf("Il thread è terminato con il codice: %d\n", stat); 
                exit(1);
        }

    }

    //Devo anche fare in modo che i thread main, termini!
    pthread_exit(NULL);

}


//Start routine del mio thread!
void* Print(void* IdThr){

    //una voltache sono giunto nella start rountine, per usare correttamente la variabile, devo effettuare nuovamente
    //un casting da "void*" a "long"!
    //In questo modo non ho problematiche nell'uso della variabile
    printf("Ciao, sono il thread : %ld\n", (long)IdThr); 

    //Come buona norma, termino il thread mediante l'apposita funzione
    pthread_exit(NULL);


}