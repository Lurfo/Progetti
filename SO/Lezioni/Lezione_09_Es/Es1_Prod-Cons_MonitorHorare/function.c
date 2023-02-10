//Specifica delle funzioni di produzione e consumazione
#include <stdio.h>

#include "function.h"


void Produco(Strut* pc, int valore){

    //Come prima azione, devo sempre entrare nel monitor!
    enter_monitor(&(pc->m));

        //Entrato nel monitor, sono sicuro che nessun altro processo può distrurbarmi!

        //Devo vedere se il buffer è occupato da un valore di un altro produttore
      
        /*NOTA BENE: 
        Siccome sto usando un monitor signal and wait, allora per andare a controllare la condizione 
        posso anche andare ad usare un semplice if, poichè sono sicuro che nessun altro processo possa andare a 
        modificarla!

        */
        if(pc->buffer_occupato==1){
            //Se è occupato, faccio una wait sulla var cond per i produttori
         //   printf("Mi blocco sulla var_cond\n"); 
           
            //Uso l'id della var_cond dei produttori
            wait_condition(&(pc->m), VARCOND_PRODUTTORI);
         //   printf("Sono il produttore sbloccato\n");
        }

        //Posso procedere con la produzione 

        //Modifico prima i valori della variabile condition!
        
        //Pongo la cond libero come 0 perchè ho un valore
        pc->buffer_libero=0; 

        //Pongo la cond occupato come 1 poichè ho inserito un valore
        pc->buffer_occupato=1;

        //Produco il valore
        pc->buffer=valore; 

       // printf("Ho prodotto il valore: %d\n", valore); 

        //A questo punto, posso fare una signal sulla condizione dei consumatori
        signal_condition(&(pc->m), VARCOND_CONSUMATORI);

       // printf("Produttore, dopo signalcond\n");

        //Posso dunque uscire dal monitor!
        leave_monitor(&(pc->m));

       // printf("Esco dal monitor, produttore\n");


}

//La funzione di consumazione mi restituisce il valore!
int Consumo(Strut* pc){
    int valore; 

    //Entro sempre nel monitor!
    enter_monitor(&(pc->m)); 
    printf("Sono nel monitor, consumatore\n");

    //Controllo della var cond dei consumatori
    //Se il buffer è libero, devo sospendere il processo!

    /*NOTA: 
        Anche in questo caso, sto andando ad usare un if per controllare la veridicità della condizione,
        proprio perchè sto realizzando un monitor signal and wait!   
    */

    if(pc->buffer_libero==1){
        //printf("Consumatore, mi blocco sulla var_cond\n");
        wait_condition(&(pc->m), VARCOND_CONSUMATORI);
        //printf("Consumatore, mi sblocco sulla var_cond\n");
    }

    //Posso procedere con la consumazione 
    valore=pc->buffer; 

    //Modifico le var_cond
    pc->buffer_libero=1;
    pc->buffer_occupato=0;

    printf("Consumazionando il valore: %d\n", valore);

    //Faccio la signal sul processo produttore
    signal_condition(&(pc->m), VARCOND_PRODUTTORI); 

    //printf("Consumatore dopo signal cond\n");

    //Posso lasciare il monitor
    leave_monitor(&(pc->m));

    //printf("Esco dal monitor, conumatore\n");

    return valore;

}