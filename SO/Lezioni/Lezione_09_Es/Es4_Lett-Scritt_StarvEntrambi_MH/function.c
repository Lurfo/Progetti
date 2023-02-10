//Definizione delle funzioni
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "function.h"



void Scrivi(Buff* punt, int val){


    //In particolare, devo entrare nel monitor
    enter_monitor(&(punt->m)); 

        //Controllo se è presente qualche lettore!
      
        //MA ATTENZIONE: 
        /*
            Devo anche andare a controllare che non ci siano già degli scrittori che sono già presenti nel
            monitor, altrimenti faccio una wait e aspetto il mio turno!
        
        */

       //In questo modo gestisco anche la competizione tra gli scrittori!
        if(punt->num_lettori>0 || punt->num_scrittori>0){
            //Mi aspetto la var condition
            wait_condition(&(punt->m), VARCOND_SCRITTORI); 

        }

    //Quando lo scrittore viene sbloccato, incremento il numero di scrittori presenti
    (punt->num_scrittori)++;

    //Nel caso del problema di lettori e scrittori, devo lasciare il monitor per poter effettuare la scrittura
    //In questo modo, altri processi possono entrare nel monitor per andare a verificare la condizione
    leave_monitor(&(punt->m));

    //A questo punto, posso andare a inserire il valore nel buffer 
    sleep(1); 
    punt->buffer=val; 

    printf("Scrivo il valore:%d\n", val);

    //A questo punto, devo entrare nel monitor per andare a modificare il numero di scrittori prescenti 
    enter_monitor(&(punt->m)); 

        //Decremento il numero di lettori
        (punt->num_scrittori)--; 

        //A questo punto, devo vedere se c'è qualche scrittore in attesa
        if(queue_condition(&(punt->m), VARCOND_SCRITTORI)){
            //Se ci sono scrittori in attesa, segnalo uno scrittore
            signal_condition(&(punt->m), VARCOND_SCRITTORI);
        }

        //Altrimenti, se non sono presenti scrittori in attesa, posso liberare un lettore
        else{

            //Siccome ho molti lettori in attesa, che possono entrare direttamente nel monitor, qui effettuo una sola signal
            //Ma il lettore, appena si risveglia, va ad effettuare a sua volta una signal, fino a quando tutti non si sono risvegliati
            signal_condition(&(punt->m), VARCOND_LETTORI);
        }

        //Dopo aver fatto queste operazioni, posso lasciare il monitor!
        leave_monitor(&(punt->m));

}


int Lettura(Buff* punt){
    int valore; 

    //Il lettore entra sempre prima nel monitor
    enter_monitor(&(punt->m));

        //Faccio un controllo sul numero di scrittori presenti, perchè se ho uno scrittori, i consumatori si devono
        //sospendere, permettendo quindi la sincronizzazione
        if(punt->num_scrittori>0){
            //Se ho degli scrittori, mi devo sospendere
            wait_condition(&(punt->m), VARCOND_LETTORI); 
        
        }

        //A questo punto, posso andare f aggiungere un lettore, quando mi riattivo!
        (punt->num_lettori)++;

        //Ma, il lettore, deve anche andare a sbloccare eventuali lettori che sono bloccati!
        //In questo modo possono tutti andare a leggere la variabile!
        signal_condition(&(punt->m), VARCOND_LETTORI);

        //Dunque, posso lasciare il monitor!

    leave_monitor(&(punt->m));


    //Simulo tempo di lettura!
    sleep(2);
    valore=punt->buffer;

    printf("Ho letto: %d\n", valore); 

    //A questo punto, devo rientrare nel monitor!

    enter_monitor(&(punt->m));

        //Decremento il numero di lettori
        (punt->num_lettori)--;

        //Devo controllare di essere l'ultimo lettore!
        if(punt->num_lettori==0){
            //Se sono l'ultimo lettore, devo sbloccare gli scrittori
            signal_condition(&(punt->m), VARCOND_SCRITTORI);
        }

    //Posso quindi lasciare il monitor
    leave_monitor(&(punt->m)); 

    return valore;

}