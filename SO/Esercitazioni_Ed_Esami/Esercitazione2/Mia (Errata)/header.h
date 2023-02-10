#define MSG_TYPE 1
#define STRING_MAX_DIM 11
#define INT_MAX_DIM 2


#define NUM_FILTER 1
#define NUM_CHECKSUM 1
#define NUM_VISUAL 1

#define NUM_GENERATORS 4
#define DIM_QUEUE 4
#define VARCOND_GEN_PRODUTTORI 0
#define VARCOND_GEN_CONSUMATORI 1

#define NUM_VARCOND 2

#define NUM_MESSAGES 8

//Definisco una macro che può essere utile nella definizione della dimensione del messaggio
#define SIZE sizeof(message)-sizeof(long)


#include "monitor_signal_continue.h"

typedef struct {
        
    //Definisco il tipo del messaggio 
    long type; 

    //Includo la stringa
    char string[STRING_MAX_DIM];

    int arr[INT_MAX_DIM];

    int var;

} message;

//Uso un typedef
typedef struct ProdConsGen {

    //Definisco la coda dove inserire i messaggi
    message buff[DIM_QUEUE];

    //Inserisco il segnaposto della testa
    int testa; 
    
    //Segnaposto della coda 
    int coda;

    //Definisco le variabili condition
    int spazio_libero; 
    int spazio_occupato;

    //Definisco il monitor nella struttura
    Monitor m;
    
    
}Buff;

void generatore_produttore(struct ProdConsGen *);
void generatore_consumatore(struct ProdConsGen *,  int);

void filtro(int, int);
void checksum(int , int);
void visualizzatore(int);
