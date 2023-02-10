#include <pthread.h>

#ifndef HEADER_H
#define HEADER_H

#define DIM_BUFFER 5

/* TODO: Definire le macro per la comunicazione su coda sincrona */
//Definisci i tipi dei vari messaggi e definisco anche le variabili che contengono le code
#define WAIT_CONFIRM 1
#define OK_SEND 2

//Tipo del messaggio risultato
#define RISULTATO_TYPE 3

//Macro per calcolare la dimensione del messaggio
#define SIZE(x) sizeof(x)-sizeof(long)

//Li definisco come extern, in modo che devono essere inizalizzati nei file dove mi occorrono!
extern int coda_OTS; 
extern int coda_RTS;
extern int coda_risultati;



typedef struct {
    
    // pool di buffer condivisi
    int operandi[DIM_BUFFER];

    /* TODO: Aggiungere le variabili necessarie per la sincronizzazione */

    //Puntatori di testa e coda 
    int testa; 
    int coda; 

    //Numero di elemenri occupati
    int numOccupati; 

    //Variabili mutex e varcond
    pthread_mutex_t mutex; 

    pthread_cond_t vc_Produttori; 
    pthread_cond_t vc_Consumatori;
    
} MonitorOperandi;

//Struttura del messaggio risultato
typedef struct {

    long type; 
    
    int mess;

} Risultato;

//Definizione della struttura del messaggio di controllo
typedef struct{
    long type;

    int mess; 

} Controllo;

void inserisci_operando(MonitorOperandi * mo, int operando);
int *preleva_operando(MonitorOperandi * mo);

void inserisci_risultato(Risultato *m , int queue);
int preleva_risultato(Risultato *m, int queue, int tipomess);

void * genera_operandi(void *);
void * calcola(void *);
void preleva_risultati(int);

void initServiceQueues();
void removeServiceQueues();
    
#endif

