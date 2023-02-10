#include <pthread.h>

#ifndef HEADER_H
#define HEADER_H

#define DIM_BUFFER 5

//Mi tengo in conto anche il tipo del messaggio che devo inviare
#define RISULTATO_TYPE 3

/* TBD: Definire le macro per la comunicazione su coda sincrona */
//Definisco due tipologie del messaggio
#define WAIT_CONFIRM 1
#define PROCEDI 2

//Mi definisco la macro per la dimensione del messaggio
#define SIZE(x) sizeof(x)-sizeof(long)
//In questo modo, ponendo la x, posso andare ad modificare se lo sto calcolando sul messaggio di controllo o sul messaggio
//che invia il risultato!




extern int coda_RTS;
extern int coda_OTS;
extern int coda_risultati;

typedef struct {
    
    // pool di buffer condivisi
    int operandi[DIM_BUFFER];
    
    /* TBD: Aggiungere le variabili necessarie per la sincronizzazione */
    //Dovendolo implementare come una coda circolare, devo inserire sicuramente i valori di testa e di coda
    int testa; 
    int coda;

    //Definisc una variabile che mantiene il nuero di posti occupati 
    //Che utilizzo come variabile di controllo

    //RICORDA: Ogni consumatore, deve consumare ogni volta almeno due elementi, il suo controllo della condizione 
    //è differente rispetto a quello fatto fino ad ora
    int numOccupati;

    //Su questa struttura, agiscono i thread, inserisco le variaibli necessarie alla loro sincronizzazione
    pthread_mutex_t mutex; 

    //Le due variabili condition che mi occorrono, una per i lettori ed una per i consumatori
    pthread_cond_t vcProduttori; 
    pthread_cond_t vcConsumatori;

    
} MonitorOperandi;

typedef struct {

    /* TBD: Definire la struttura messaggio */
    //Questo messaggio contiene il risultato della mia operazione
    long type; 

    int mess;


} Risultato;

//Mi definisco anche la struttura del messaggio di controllo
typedef struct{
    long type;

    int payload;

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

