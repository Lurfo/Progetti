//Definizione delle funzioni di produzione e consumazione
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#include "function.h"


void produttori(Buff* p, int valore){

    int i=0;

    //Come prima cosa entro nel monitor 
    enter_monitor(&(p->m)); 

        //Una volta entrato nel monitor, verifico la veridicità della condizione 
        //Devo vedere se il numero di posti disponibili è maggiore di zero
        //Dunque, fino a quando i posti liberi sono 0 mi metto in attesa sulla viariabile condition
        while(p->numero_liberi==0){
            wait_condition(&(p->m), VARCOND_PRODUTTRI);
        }

        //Quando la condizione è verificata, devo cercare all'interno dell'array
        //il primo posto disponibile
        while(i<DIM_MAX && p->stato[i]!=LIBERO){
            i++;
        }

        //Quando ho ottenuto il mio posto, lo pongo in uso
        p->stato[i]=IN_USO;
        //Diminuisco il numero di posti liberi
        (p->numero_liberi)--;
   
    //Riservato quindi il mio posto, posso uscire dal monitor, in modo che anche altri processi possano andare a 
    //trovare un posto disponibile all'interno del monitor
    leave_monitor(&(p->m));

    //Grazie quindi anche al vettore di stato, posso effettuare la consumazione anche esternamente, poichè ogni processo
    //ha già ottenuto il posto a cui accedere!

    //Anche fuori dal monitor, siccome ho conservato il valore della posizione in cui andare ad inserire il mio valore, posso
    //produtte
    sleep(2);
    p->buff[i]=valore;
    printf("Ho prodotto: %d\n", valore);


    //Ora devo rientrare nel monitor, perchè devo aggiornare il valore del vettore di stato
    //siccome devo gestire la concorrenza dei processi nell'aggiornare la variabile del numero di occupati, devo
    //rientare
    enter_monitor(&(p->m));

        p->stato[i]=OCCUPATO; 

        //Aumento anche il numero dei posti occupati
        p->numero_occupati++;

        //Faccio una signal ai consumatori per segnalare la loro var_cond, che almeno un posto è pieno
        signal_condition(&(p->m), VARCOND_CONSUMATORI);

    //Posso quindi lasciare il monitor!
    leave_monitor(&(p->m));



}

int consuma(Buff* p){
    int valore; 
    int i=0;

    //Il consumatore ha un comportamento molto simile
    //Entro nel monitor
    enter_monitor((&p->m));

        //Devo quindi verificare che ci siano almeno dei posti occupati
        //Questo indica che, fino a quando il numero di posti occupati sarà 0, mi devo sospendere sulla condizione
        while(p->numero_occupati==0){
            
            wait_condition(&(p->m), VARCOND_CONSUMATORI);
        }

        //Quando verrò sbloccato perchè almeno un produttore ha concluso il suo compito, effettuo una ricerca sui posti
        while(i<DIM_MAX && p->stato[i]!=OCCUPATO){
            i++;
        }

        //Ho trovato il posto occupato, lo aggiorno
        p->stato[i]=IN_USO; 
        //Diminuisco il numero di posti occupati
        p->numero_occupati--;

    //Lascio il monitor, in modo da consumare
    leave_monitor(&(p->m));

    //Mi salvo il valore che ho ottenuto
    sleep(2);
    valore=p->buff[i]; 

    //Rientro nel monitor, per andare ad aggiornare il posto e la variabile che indica quanti posti sono liberi
    enter_monitor(&(p->m)); 

        p->stato[i]=LIBERO; 

        //La variabile di posti liberi deve essere incrementata
        p->numero_liberi++;

        //Posso fare una signal ai produttori
        signal_condition(&(p->m), VARCOND_PRODUTTRI);

    leave_monitor(&(p->m)); 

    return valore;

}