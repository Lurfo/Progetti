//Specifica delle funzioni di produzione e consumazione

#ifndef FUNCTION_H
#define FUNCTION_H

#define MAX 100

#define size sizeof(Messaggio)-sizeof(long)

//Specifico il messaggio attravero la struttura apposita
typedef struct{
    //Il tipo del messaggio deve essere sempre inserito all'inizio della struttura!
    //Lo devo sempre specificare
    long type; 

    char string[MAX];
} Messaggio;


//Sia le funzioni di produzione che quelle di consumazione devono avere come parametro di ingresso l'id della code dei messaggi

//Nel caso del produttore, ho anche il messaggio
void produttore(int coda, char* mess);

//Al consumatore, basta anche solo l'info della coda da cui andare a leggere il messaggio
void constumatore(int coda);

#endif