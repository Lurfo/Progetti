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

#define SIZE sizeof(message)- sizeof(long)

#include "monitor_signal_continue.h"

typedef struct
{
    long type;
    char stringa[STRING_MAX_DIM];
    int array[INT_MAX_DIM];
    int var;
} message;

typedef struct
{
    message msg[DIM_QUEUE];
    int testa;
    int coda;
    int occupato;
    int libero;
    Monitor m;

} ProdConsGen;

void generatore_produttore(ProdConsGen *);
void generatore_consumatore(ProdConsGen *, int);

void filtro(int, int);
void checksum(int, int);
void visualizzatore(int);
