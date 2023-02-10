//Definizine delle funzioni di lettura e scrittura
#include <stdio.h>
#include <unistd.h>

#include "function.h"

void scrivo(Buff* p, int valore){

    //Entro nel monitor
    enter_monitor(&(p->m));

        //Controllo la condizione, se ci sono degli scrittori, non devo accedere, in modo che non ci siano problemi di competizione
        //Controllo il numero di lettori, se essi ci sono, non devo accedere
        while(p->numLett>0 || p->numScritt>0){
            //Faccio una wait sulla condizione degli scrittori
            wait_condition(&(p->m), VARCON_SCRITTORI);
        }

        //Quando sono "libero", posso procedere

        //Incremento il numero di scrittori
        p->numScritt++;

    //A questo punto, posso anche uscire dal monitor, il prossimo che entra, lo trova comunque pieno!
    leave_monitor(&(p->m));

    //Posso quindi procedere con l'inserimento del valore!
    sleep(1);
    p->buff=valore; 

    printf("Ho scritto il valore: %d\n", valore);

    //A questo punto, deve rientrare nel monitor per andare a modificare il valore di elementi presenti
    enter_monitor(&(p->m));

        //Diminuisco il numero di elementi presenti
        p->numScritt--;

        //Devo controllare quanti scrittori sono in attesa
        if(queue_condition(&(p->m), VARCON_SCRITTORI)){
            signal_condition(&(p->m), VARCON_SCRITTORI);

        }

        else{
            signal_all(&(p->m), VARCON_LETTORI);
        }

    leave_monitor(&(p->m));
}

int leggo(Buff* p){


    int valore; 

    //Entro nel monitor
    enter_monitor(&(p->m)); 

        //Controllo della condizione
        while(p->numScritt>0){

            wait_condition(&(p->m), VARCON_LETTORI);
        }

        //Quando sono in questa sezione, sono sbloccato e sono nel monitor

        //Incremento il numero di scrittori
        p->numLett++;

        /*  ATTENZIONE: 
            Nel caso signal and continue, un processo lettore, sarà sicuramente segnalato da uno scrittore, quindi
            posso anche lasciare il monitor senza la necessità di segnalare nessun altro lettore!!!      
        */
        

    //posso, per ora, uscire dal monitor
    leave_monitor(&(p->m));

    sleep(1);

    valore=p->buff;

    //I consumatori possono accedere contemporaneamente alla risorsa condivisa 
    //printf("Ho letto, il valore: %d\n", valore);

    //Rientro nel monitor, per andare a segnalare che sto uscendo
    enter_monitor(&(p->m)); 
        //Diminuisco il valore 
        p->numLett--; 

        //Se sono l'ultimo lettore devo sbloccare gli scrittori
        if(p->numLett==0){
            signal_condition(&(p->m), VARCON_SCRITTORI);
        }

    //Lascio il monitor
    leave_monitor(&(p->m));


    return valore;


}