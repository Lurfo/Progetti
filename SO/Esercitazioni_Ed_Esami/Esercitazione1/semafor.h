//Specifica delle funzioni del semaforo
#ifndef SEMAFOR_H
#define SEMAFOR_H

//Definisco i semafori che mi occorrono 
#define MUTEX_L 0

#define MUTEX_L1 1

#define SYNCH 2

#define VOLTE 3

//Inserisco in una struct il numero di processi lettori e il numero di elementi che si devono inserire nella struct
typedef struct{
    int dimensione;

    //Quella che deve poi essere modificata
    int Num_Lettori;
} insieme;




//Definizione delle librerie necessarie per l'uso del semaforo!
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int wait_sem(int semID, int semNum); 

int signal_sem(int semID, int semNum);

#endif