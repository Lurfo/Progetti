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

#define NUM_MESSAGES 8

//Specifo una macro che mi serve per la dimensione del messaggio
#define SIZE sizeof(message)-sizeof(long)

#include "monitor_signal_continue.h"

typedef struct {
        
    //Specifico il tipo del messaggio, un long che deve essere sempre presente
    long type;

    char str[STRING_MAX_DIM];

    int arr[INT_MAX_DIM];

    int var;


} message;

struct ProdConsGen {
    
    //Buffer di messaggi
    message Buff[DIM_QUEUE]; 

    //Inserisco i "puntatori" di testa e di coda
    int testa; 
    
    int coda; 

    //Inserisco una variabile che mi occorre per controllare se la coda è piena o meno
    //In questo caso, tale variabile verrà usato dai consumatori e dai produttori per effettuare
    //eventuali wait e signal sulle variabili condition
    int numOccupati;
    //Contiene il numero di posti che sono stati occupati!

    //Nella struttura, devo anche inserire il mio monitor
    Monitor m;

    
};

void generatore_produttore(struct ProdConsGen *);
void generatore_consumatore(struct ProdConsGen *,  int);

void filtro(int, int);
void checksum(int , int);
void visualizzatore(int);
