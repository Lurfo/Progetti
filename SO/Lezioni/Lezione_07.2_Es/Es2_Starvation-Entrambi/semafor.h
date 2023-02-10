//Specifica delle funzioni del semaforo
#ifndef SEMAFOR_H
#define SEMAFOR_H

//Definizione delle librerie necessarie per l'uso del semaforo!
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int wait_sem(int semID, int semNum); 

int signal_sem(int semID, int semNum);

#endif