//Implementazione della funzione main!

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
//Devo includere la memoria condivisa, perchè deve essere divisa tra i processi di produzione e consumazione!
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>

#include "function.h"

//Mi definisco con una macro il numero di processi produttori e consumatori
#define NUM_PRODUTTORI 10
#define NUM_CONSUMATORI 10

int main(){

    srand(time(NULL));

    //Mi genero la memoria condivisa
    int idMem = shmget(IPC_PRIVATE, sizeof(Strut), IPC_CREAT|0660);

    //Controllo 
    if(idMem<0){
        perror("Errore ad ottenere la memoria condivisa\n"); 
            exit(1);
    }

    //Effettuo l'attach della memoria
    Strut* punt = (Strut*) (shmat(idMem, NULL, 0));

    //Controllo
    if(punt== (void*)-1){
        perror("Errore attach\n"); 
            exit(1);
    }

    //A questo punto, dopo a memoria, devo inizializzare il monitor
    //La sua inizializzazione è molto più semplice, basta usare l'apposita funzione di inizializzazione
    //Essa prede in ingresso il riferimento al monitor ->Gli devo passare quello nella mia struttura
    //E prende anche il numero di variabili conditio ->Quello che mi sono impostato come macro!
    init_monitor(&(punt->m), NUMVAR);
    
    //NOTA:Siccome punt è un puntatore, gli devo mettere inizialmente la &, in modo da passargli l'indirizzo di memoria del
    //monitor

    //Dopo aver fatto l'inizializzazione del monitor, vado ad inizializzare le variabili condition 

    //Ovviamente il buffer inizialmente è libero
    punt->buffer_libero=1; 

    punt->buffer_occupato=0;

    //A questo punto, posso andare a generare i miei processi di produzione e consumazione!
    pid_t pid; 

    //Li genero mediante un ciclo for!
    for(int i=0; i<NUM_PRODUTTORI; i++){
     
        pid=fork(); 

        if(pid<0){
            perror("Errore fork\n"); 
                exit(1);
        }

        if(pid==0){
            printf("Figlio produttore: %d\n", getpid()); 

            //Prima della produzione, attendo 5 secondi
            sleep(5);

            //Genero un numero casuale
            int num = rand()%100+1;

            Produco(punt, num); 

            //Dopo la produzione, faccio una exit
            exit(0);
            
        }
        
    }

    for(int i=0; i<NUM_CONSUMATORI; i++){
        pid=fork(); 

        if(pid<0){
            perror("Errore fork\n"); 
                exit(1);
        }

        if(pid==0){
            printf ("Sono un consumatore: %d\n", getpid());

            int val = Consumo(punt);

            printf("Ho consumato il valore: %d\n", val);

            exit(0);

        }
    }

    //Il processo padre, effettua una wait sui processi figli
    for(int i=0; i<NUM_CONSUMATORI+NUM_PRODUTTORI; i++){
        printf("Si è concluso il processo: %d\n", wait(NULL));
    }


    //L'ultima cosa che deve fare il main, deve andare a eliminare tutto quello che ho definito

    //Rimuovo il monitor
    remove_monitor(&(punt->m)); 

    //Rimuovo la memoria condivisa
    shmctl(idMem, IPC_RMID, 0);

}
