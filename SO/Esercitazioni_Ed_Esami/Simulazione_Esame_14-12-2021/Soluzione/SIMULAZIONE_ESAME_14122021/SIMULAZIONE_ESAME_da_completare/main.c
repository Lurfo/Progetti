#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>

#include "header.h"

#define NUM_THREADS_OPERANDI    2
#define NUM_THREADS_CALCOLO     3

int main(){

        pthread_attr_t attr;
        pthread_t threads_operandi[NUM_THREADS_OPERANDI];
        pthread_t threads_calcolo[NUM_THREADS_CALCOLO];
    
        srand(time(NULL)*getpid());

        coda_risultati = /* TODO: Creazione coda risultati */
        printf("Coda coda_risultati create con desc: %d\n", coda_risultati);
    
        initServiceQueues();
            
        // Creazione di una istanza di struttura monitor per gli operandi
        // MonitorOperandi sarà usato dai thread generazione operandi
        MonitorOperandi * pc_op = /* TODO: inizializzare */
    
        /* TODO: inizializzazione mutex e condition */
    
        /* TODO: inizializzazione delle variabili di stato */

        /* TODO: impostazione dei thread come joinable */

        /* TODO: genero processo prelievo risultati */
    
        /* TODO: genero thread generazione operandi */
    
        /* TODO: genero thread di calcolo */
    
        /* TODO: Join threads a wait processo*/
    
        /* TODO: deallocazione risorse */
    
        pthread_exit(NULL);
}

