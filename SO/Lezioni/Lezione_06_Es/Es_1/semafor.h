#ifndef SEMAFOR_H
#define SEMAFOR_H

//Per poter usare le funzioni sui semafori, come semop, devo andare a sfruttare le librerie qui definite!
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

//Definisco la signature delle due funzioni di wait e signal!


int wait_sem(int semid, int sem_num);

int signal_sem(int semid, int sem_num);

//Entrambe restituiscono un intero, che in caso è pari a -1

//Entrambe hanno come argomenti: 
// -Id del semaforo
// -Il numero del semaforo su cui devo eseguire l'operazione!


#endif