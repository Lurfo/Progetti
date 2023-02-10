#include <stdio.h>
#include <unistd.h>

#include "prodcons.h"

void inizializza(ProdCons * p) {

    /* TBD: Inizializzazione del monitor */
}

void consuma(ProdCons * p) {

    /* TBD: Ingresso nel monitor */


    printf("[%d] Ingresso consumatore\n", getpid());

    /* TBD: Sospendere qui il consumatore se non ci sono
     *      *almeno* 3 elementi disponibili nel vettore
     */

    /* TBD: Effettuare signal_condition() per svegliare i produttori
     *      in accordo al numero di elementi consumati
     */


    printf("[%d] Uscita consumatore\n", getpid());

    /* TBD: Uscita dal monitor */
}

void produci(ProdCons * p, int val) {

    /* TBD: Ingresso nel monitor */

    printf("[%d] Ingresso produttore\n", getpid());

    /* TBD: Sospendere qui il produttore se il vettore è già pieno */


    p->vettore[p->testa] = val;
    p->testa = (p->testa + 1) % DIM;
    p->totale_elementi++;

    printf("[%d] Produzione: val=%d\n", getpid(), val);

    
    /* TBD: Svegliare un consumatore *solo se* sono disponibili almeno 3 messaggi. 
     *      Poiché è richiesto di utilizzare la semantica di Hoare, il consumatore
     *      sarà attivato immediatamente al momento della signal_condition().
     */

    printf("[%d] Uscita produttore\n", getpid());

    /* TBD: Uscita dal monitor */
}

void rimuovi(ProdCons * p) {

    /* TBD: Deallocazione del sotto-oggetto monitor */
}
