//Definizione delle funzioni
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "function.h"

//Specifica della funzione di produzione
void produttore(Buff* p, int val){

    //Come prima cosa, entro nel monitor
    enter_monitor(&(p->m)); 
        //Vado a controllare se è possibile andare a produrre

        //Devo fare in modo che il processo effettui un while per andare a controllare la veridicità della variabile, che può
        //essere modificata anche da altri processi!
        while(p->buff_occupato==1){
            wait_condition(&(p->m), VARCOND_PRODUTTORI);
        }

        //Se la condizione è verificata allora sono nuovamente nel monitor, dunque posso andare a modificare il valore
        //dei campi della struttura
        p->buff_libero=0;
        p->buff_occupato=1; 
        
        //Salvo il valore nella struttura
        p->buff=val; 

        printf("Ho prodotto il valore: %d\n", val);

        //A questo punto faccio una signal sulla condizione dei consumatori
        signal_condition(&(p->m), VARCOND_CONSUMATORI);

    //E posso lasciare il monitor in modo che il prossimo process possa entrare
    leave_monitor(&(p->m));

}






int consumo(Buff* p){
    int valore;
    //La funzione di consumazione è molto simile

    //Entro nel monitor
    enter_monitor(&(p->m)); 

        //Effettuo un controllo sulla var_cond
        while(p->buff_libero==1){

            //Effettuo una wait sulla condizione dei consumatori
            wait_condition(&(p->m), VARCOND_CONSUMATORI);
        }

        //Se la condizione è verificata e sono entrato nel monitor allora, modifico i valori
        p->buff_occupato=0;
        p->buff_libero=1;

        //Mi salvo il valore contenuto nella sturct 
        valore=p->buff;

       // printf("Ho consumato il vaore: %d\n", valore); 

        //Posso fare una signal ai produttori che ho concluso

        signal_condition(&(p->m), VARCOND_PRODUTTORI);

    //Dunque lascio il monitor
    leave_monitor(&(p->m));

    return valore;

}