#ifndef _HEADER_H_
#define _HEADER_H_

#include "monitor_hoare.h"

#define NUM_PRODUTTORI 6
#define NUM_CONSUMATORI 2

#define DIMENSIONE 5

/* TBD: Aggiungere macro per la gestione delle variabili condition e del vettore di stato */

//Macro per il vettore di stato
#define VUOTO 0
#define IN_USO 1
#define OCCUPATO 2

//Definizione delle variabili condition
//ATTENZIONE
//Siccome sto usando dei semafori per la VC, il valore della var condition non fa altro che rappresentare un semaforo
//dell'array semaforico che sto considerando, per questo motivo è FONDAMENTALE, partire da 0, proprio perchè il primo semaforo
//dell'insieme ha come valore 0!!!
//SE NON IMPOSTO LE CONDIZIONI PARTENDO DA 0 È UN GRAVE ERRORE!!!
#define VAR_PRODUTTORI 0
#define VAR_CONS 1

//Definizione della macro che tiene conto del numero di variabili condition
#define TOT_CONDITION 2 

typedef struct {

    int vettore[DIMENSIONE];

    //Imposto il vettore di stato 
    int stato[DIMENSIONE];
    
    /* TBD: Aggiungere variabili per la sincronizzazione */

    //Aggiungo la variabile che mi tiene conto del numero di produttori che sono già in attesa sul monitor!
    //In particolare, se ho che il numero di produttori che sono in attesa è maggiore di 4 allora devo lasciare il monitor
    int produttori_int_attesa;

    //Inserisco poi le variabili che mi occorrono per la sincronizzazione di produttori e consumatori

    //Inserisco la variabile che mi tiene traccia del numero di elementi liberi che ho all'interno della struttura
    int numLiberi; 

    //Inserisco la variabile che tiene conto del numero di elementi che sono stati occupati!
    int numOccupati;

    //NOTA BENE:
    //Qesto avviene anche con i semafori, nel cui caso, devo considerare due semafori, che come le variabili
    //mi occorrono uno per tenere il conto dei posti liberi ed uno per tenere conto del nuemro di elementi occupati
    //Nel caso dei semafori, tuttavia, imposto direttamente il valore del semaforo, uno proprio uguale al totale di elementi
    //che sono presenti nel vettore e l'altro impostato a 0 (poichè inizialmente non ci sono degli elementi nel vettore
    //di stato)

    //Inserisco l'istanza del monitor 
    Monitor m;

} MonitorCoda;

// il valore di ritorno di produzione() indica se il monitor è sovraccarico
int produzione(MonitorCoda *m, int valore);

// il valore di ritorno di consumazione() è il valore prelevato dalla coda
int consumazione(MonitorCoda *m);

void produttore(MonitorCoda *m);
void consumatore(MonitorCoda *m);

void inizializza(MonitorCoda *m);
void rimuovi(MonitorCoda * p);

#endif
