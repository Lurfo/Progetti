#ifndef __PROCEDURE_H
#define __PROCEDURE_H

#include <pthread.h>

#define DIM 4

//Come da traccia ho 4 tipologie di stato (anche il base al tipo di valore che viene prodotto)
#define LIBERO 0
#define INUSO 1
#define OCCUPATO1 2
#define OCCUPATO2 3

typedef struct{

	int vettore[DIM];

	int stato[DIM];

	int num_liberi;
	int num_occupati_tipo1;
	int num_occupati_tipo2;

	/* TBD: Aggiungere ulteriori variabili per la sincronizzazione */

	//In particolare, devo aggiungere le variabili condition per produttori e consumatori, sfruttando la libreria pthread
	//Siccome mi trovo a gestire due tipologie di produttori e consumatori, allora devo utilizzare 4 vc
	//due per ogni tipo di produttori
	pthread_cond_t vc_produttori_1; 
	pthread_cond_t vc_consumatori_1;

	pthread_cond_t vc_produttori_2;
	pthread_cond_t vc_consumatori_2;

	//Devo anche inserire il mutex, che viene usato come monitor
	pthread_mutex_t mutex;
    
} MonitorPC;

void inizializza(MonitorPC * m);
void rimuovi(MonitorPC * m);
void produci_tipo_1(MonitorPC * m, int valore);
void produci_tipo_2(MonitorPC * m, int valore);
void consuma_tipo_1(MonitorPC * m, int * valore);
void consuma_tipo_2(MonitorPC * m, int * valore);


#endif
