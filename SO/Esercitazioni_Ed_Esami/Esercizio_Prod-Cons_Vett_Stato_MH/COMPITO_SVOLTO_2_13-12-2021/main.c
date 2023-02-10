#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <time.h>

#include "header.h"

//ATTENZIONE
//Siccome sto usando UN'APPLICAIZONE MULTIPROCESSO, devo sfruttare, necessariamente, UNA SHARED MEMORY!!!!
//IN MODO CHE I DATI POSSANO ESSERE CONDIVISI TRA I PROCESSI    

int main() {

    int shm_id = shmget(IPC_PRIVATE, sizeof(MonitorCoda), IPC_CREAT|0660);
    
    if (shm_id < 0)
    {
        perror("Errore creazione shared memory");
        exit(1);
    }
    
    //Ottento un puntatore a monitor coda, usando una attach, andando anche a fare 
    //l'opportuno type casting!!!
    MonitorCoda *p = (MonitorCoda *) shmat(shm_id, NULL, 0);


    if (p == (void *)-1)
    {
        perror("Errore attach shared memory");
        exit(1);
    }

    /* TBD: Inizializzare monitor e variabili per la sincronizzazione tramite la procedura inizializza(...) */

    //Siccome ho impostato la funzione di inizializzazione, allora richiamo quella per inizializzare la struttura monitor
    inizializza(p);
    
    /* TBD: Aggiungere codice per la creazione dei processi produttori e consumatori */

    //Creo i processi produttori e consumatori, andando ad usare due fork differenti 

    pid_t pid; 

    for(int i=0; i<NUM_PRODUTTORI; i++){
        pid = fork(); 

        if(pid<0){
            perror("Errore fork produttori\n"); 
                exit(1);
        }

        if(pid==0){
            produttore(p);
        }
    }

    for(int i=0; i<NUM_CONSUMATORI; i++){
        pid = fork(); 

        if(pid<0){
            perror("Errore fork consumatori\n"); 
                exit(1);
        }

        if(pid==0){
            consumatore(p);
        }
    }


    /* TBD: Aggiungere codice per l'attesa della terminazione dei processi produttori e consumatori */

    //Attendo che i processi produttori e consumtori, terminino con un for
    for(int i=0; i<NUM_CONSUMATORI+NUM_PRODUTTORI; i++){
        wait(NULL);
    }


    /* TBD: Aggiungere codice per la rimozione del monitor tramite la procedura rimuovi(...) */
   
    //Rimuovo il monitor tramite la procedura apposita
    rimuovi(p);

    //Rimuovo ance la memoria 
    //ATTENZIONE: Devo rimuovere la memoria, solo dopo aver rimosso il monitor, altrienti
    //se elimino prima la memoria, non posso più eliminare il monitor e dunque rimuovere i 
    //semafori che sono stati inizializzati!
    shmctl(shm_id, IPC_RMID, NULL);

    return 0;
}

