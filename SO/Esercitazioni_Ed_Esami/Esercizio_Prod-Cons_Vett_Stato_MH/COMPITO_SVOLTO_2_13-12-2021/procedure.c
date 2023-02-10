#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

#include "header.h"


void inizializza(MonitorCoda *p) {

    /* TBD: Aggiungere codice per l'inizializzazione del monitor e delle relative
     * variabili per la sincronizzazione
     */

    //Imposto tutte le posizione del vettore di stato come vuoto
    for(int i=0; i<DIMENSIONE; i++){
        p->stato[i]=VUOTO;
    }
    
    //Imposto il numero di elementi liberi
    p->numLiberi=DIMENSIONE;

    //Imposto il numero di elementi occupati, uguale a 0
    p->numOccupati=0;

    //Inizializzo anche il numero di produttori in attesa
    //che deve essere uguale a 0, inizialmente
    p->produttori_int_attesa=0;

    //Inizializzo il monitor
    init_monitor(&(p->m), TOT_CONDITION);

}

void rimuovi(MonitorCoda * p) {
    /* TBD: Aggiungere codice per la rimozione del monitor */

    //In questo caso, devo solo rimuovere il monitor!
    //Uso la funzione apposita di libreria
    remove_monitor(&(p->m));
}


int produzione(MonitorCoda *p, int valore) {

    /* TBD: Aggiungere codice per la produzione in accordo allo schema
     * con vettore di stato, ricordando che il valore di ritorno della funzione
     * indica se il monitor è sovraccarico o meno.
     * Nel caso in cui ci siano almeno 4 produttori in attesa, bisogna forzare
     * l'uscita del processo dal monitor e ritornare un valore pari ad 1.
     * Nel caso in cui la produzione avviene normalmente ritornare un valore pari a 0.
     */
    
    //Entrno nel monitor
    enter_monitor(&(p->m)); 

        //In particolare, controllo se ci sono altri produttori in attesa sul monitor, in base alla specifica richiesta 
        //dal problema
        if(p->produttori_int_attesa == 4){
           
            printf("Ci sono produttori in attesa, esco dal monitor\n"); 

            //In questo caso, devo lasciare il monitor 
            leave_monitor(&(p->m)); 

            //Ritorno un valore pari ad 1, in modo da segnalare alla funzione chiamante che ci sono dei produttori
            //che stanno già attendendo il monitor
            return 1;
        }

        //Se la condizione fallisce, vuol dire che posso andare a controllare la condizione, essendo un monitor signal
        //and wait, la controllo tramite if

            //Controllo che il numero di posti disponibili sia maggiore di zero, dunque effettuo una wait, se il numero di posti
            //liberi è pari a 0
        if(p->numLiberi == 0){
            
            //Se sono qui vuol dire che mi devo sospendere, aumento il numero di produttori
            //che sonon in attesa 
            p->produttori_int_attesa++;

            printf("PRODUTTORI SOSPESI in attesa: %d\n", p->produttori_int_attesa);

            //In questo caso, mi sospendo sulla condizione dei produttori
            wait_condition(&(p->m), VAR_PRODUTTORI);

            //Se sono qui, vul dire che sono stato sbloccato, dunque devo diminuire il numero
            //di produttori che sono in attesa 
            p->produttori_int_attesa--;
        }

        //Se sono qui, allora sono stato sbloccato, prelevo il primo elementi libero che trovo nel vettore
        int i=0;

        while(i<DIMENSIONE && p->stato[i]!=VUOTO){
            i++;
        }

        //Dunque, imposto che quella posizione è in uso
        p->stato[i]=IN_USO;

        //Diminuisco il numero di posti liberi
        p->numLiberi--;

        //printf("Sono rimasti %d posti liberi\n", p->numLiberi); 

    //In questo caso, siccome sto usando un buffer di stato, posso lasciare il monitor per la produzione, andando a produrre
    //nella locazione segnata dal valore "i", che ho trovato precedentemente
    leave_monitor(&(p->m));

    //Dunque, produco il valore 
    p->vettore[i]=valore;

    //printf("PRODUTTORE ho prodotto %d\n", p->vettore[i]);

    //Devo ritornare nel monitor, per andare ad aggiornare il vettore di stato e il numero di posti occupati
    enter_monitor(&(p->m)); 

        p->numOccupati++;

        p->stato[i]=OCCUPATO;

        //Effettuo una signal ai consumatori
        signal_condition(&(p->m), VAR_CONS);

    //Posso dunque lasciare il monitor
    leave_monitor(&(p->m));

    //Ritorno 0, per segnalare al chiamante che ho prodotto il risultato
    return 0;



}


/* NOTA: il valore di ritorno di consumazione() è il valore prelevato dalla coda */

int consumazione(MonitorCoda *p) {


    /* TBD: Aggiungere codice per la consumazione in accordo allo schema
     * con vettore di stato, ricordando che il valore di ritorno della funzione
     * indica il valore prelevato dal buffer condiviso.
     */

    //Mi segno la variabile che mi occorre per contenere il valore che ho definito
    int var; 

    //Entro nel monitor
    enter_monitor(&(p->m)); 

        //Il consumatore, non ha lo stesso obbligo dei produttori, effettuo direttamente un controllo sulla condizione
        //Essendo che ho a che fare con un monitor signal and wait, posso andare a controllare la condizione tramite un if
        if(p->numOccupati==0){
            wait_condition(&(p->m), VAR_CONS);
        }

        //Se sono qui, sono stato sbloccato, posso dunque cercare l'elemento che corrisponde ad uno stato "OCCUPATO"

        int i=0; 

        while(p->stato[i]!=OCCUPATO && i<DIMENSIONE){
            i++;
        }

        //In questo caso, modifico lo stato rispetto a quella posizione 
        p->stato[i]=IN_USO;

        //Diminuisco il numero di elementi occupati
        p->numOccupati--; 

    //Posso lasciare il monitor, perchè sto usando il vettore di stato 
    leave_monitor(&(p->m));

    //Consumo il valore 
    var=p->vettore[i];
    printf("CONSUMATORE in posizione %d\n", i);

    //Ritorno nel monitor per andare ad aggiornare il vettore di stato e il numero di liberi
    enter_monitor(&(p->m)); 

        //printf("CONSUMATORE posti liberi %d\n", p->numLiberi);

        p->numLiberi++;

        //printf("CONSUMATORE posti liberi dopo incremento %d\n", p->numLiberi);

        p->stato[i]=VUOTO;

        //Dunque effettuo una segnalazione ai produttori
        signal_condition(&(p->m), VAR_PRODUTTORI);

    //Lascio il monitor
    leave_monitor(&(p->m));

    //Ritorno dunque il valore che ho consumato
    return var;
        

}

void produttore(MonitorCoda *m) {
    
    int valore;
    int ret;
    int i;
    
    for(i=0; i<5; i++) {
        
        while(1) {
            
            srand(time(NULL)*getpid());
            
            valore = rand() % 10 +1;
            
            ret = produzione(m, valore);
            
            if(ret==0) { break; }
            
            printf("MONITOR SOVRACCARICO, ATTENDO 3 secondi...\n");
            
            sleep(3);
        }
        
        printf("VALORE PRODOTTO: %d\n", valore);
        
        sleep(1);
    }
    
    
    exit(0);
}

void consumatore(MonitorCoda *m) {
    
    int i;
    int valore;
    
    for(i=0; i<15; i++) {
        
        valore = consumazione(m);
        
        printf("VALORE CONSUMATO: %d\n", valore);
        
        sleep(2);
    }
    
    
    exit(0);
}

