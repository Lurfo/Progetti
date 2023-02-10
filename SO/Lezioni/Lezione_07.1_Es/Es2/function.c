//Specifica delle funzioni di produzione e consumazione!
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>


#include "function.h"
#include "semafor.h"






void produttore(struct circular* mem, int semID){

    //La prima azione che compie un produttore è la wait sul semaforo dello spazio disponibile 
    //In modo tale da segnalare che uno spazio è stato occupato!
    if(wait_sem(semID, SPAZIO_DISPONIBILE)<0){
        perror("Errore wait sul semaforo Sincronizzazione\n"); 
            exit(1);
    }

    //A questo punto, il produttore, deve fare una wait sul semaforo che deve regolare la competizione tra i produtto, altrimenti
    //potrebbe capitare che più produttori possono accedere in contemporanea alla memoria!

        if(wait_sem(semID, MUTEX_P)<0){
            perror("Errore wait competizione processi\n"); 
                exit(1);
        } 

        sleep(2);

        //Comincia dunque la sezione critica in cui devo andare a produrre un valore ed inserirlo all'interno della memoria!

        mem->buffer[mem->testa]=rand() %100 + 1;

        printf("Ho prodotto il valore: %d\n", mem->buffer[mem->testa]);

        //Per gli altri produttori, devo andare a spostare il valore del buffer, in modo che il prossimo scriva al posto successivo
        //della testa del buffer

        //Controllo che il valore sia minore della dimensione massima, se è vero avanzo al prossimo posto disponibile, altrimeti
        //lo sposto nuovamente all'inizio!
        /*if(mem->testa<DIM){
            mem->testa++;
        }

        else{
            mem->testa=0;
        }*/ 

        //NOTA BENE, PIUTTOSTO CHE USARE IL COSTRUTTO DEFINITO SOPRA, POSSO USAR UN COSTRUTTO MOLTO PIÙ SEMPLICE    
        mem->testa=(mem->testa +1) % DIM; 
        //In questo modo, il valore di testa è uguale al resto della divisione con il valore DIM, così facendo, 
        //quando ho che testa=DIM, il valore del resto è 0 e quindi testa=0


        //A questo punto devo sbloccare il valore che segnala agli altri produttori la possibilità di accedere!

        if(signal_sem(semID, MUTEX_P)<0){
            perror("Errore sblocco processi bloccati!\n");
                exit(1);
        }

    
    //Devo alla fine andare a segnalare ai consumatori che è presente un valore all'interno della memoria condivisa da poter
    //leggere!

    //Effettu una signal sul semaforo MESSAGGIO_DISPONIBILE!
    
    if(signal_sem(semID, MESSAGGIO_DISPONIBILE)<0){
        perror("Ho avuto un problema con la signal sul semaforo MESSAGGIO_DISPONIBILE, nel produttore!\n"); 
            exit(1);
    }

    return;
    
}


void consumatore(struct circular* mem, int semID){

    //Effettuo una wait sul semaforo, in modo da verificare se sono disponibili eventuali messaggi!
    if(wait_sem(semID, MESSAGGIO_DISPONIBILE)<0){
        perror("Errore wait su MESSAGGIO_DISPONIBILE, nel consumatore\n"); 
            exit(1);
    }

        //Faccio una wait sul semaforo della mutua esclusione dei consumatori!
        if(wait_sem(semID, MUTEX_C)<0){
            perror("Errore wait su MUTEX_C\n"); 
                exit(1);
        }

        sleep(2);

        //Sono nella sezione critica, devo quindi leggere il messaggio!

        //printf("Consumatore presente!\n"); 
        printf("Il messaggio è: %d\n", mem->buffer[mem->coda]);

        //La sezione critia è fatta anche in modo che io debba andare a modificare il valore della coda della lista!
        //così che il prossimo consumatore può andare a leggere il valore corretto!

        //L'impostazione della coda è la medesima della testa!
        /* if(mem->coda<DIM){
            mem->coda++;
        }

        else{
            mem->coda=0;
        }*/

        //COME SOPRA!
        mem->coda=(mem->coda+1)%DIM;

        //Devo sbloccare la restante parte dei consumatori, effettuando un semaforo che gestisce la concorrenza tra i consumatori
        if(signal_sem(semID, MUTEX_C)<0){
            perror("Errore signal su MUTEX_C\n"); 
                exit(1);
        }

    //A questo punto devo segnalare ai produttori che si è liberato un posto per posare un nuovo messaggio!

    if(signal_sem(semID, SPAZIO_DISPONIBILE)<0){
        perror("Errore wait su SPAZIO_DISPONIBILE, Nel consumatore\n");
            exit(1);
    }


    return;


}