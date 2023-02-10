//Implemento la struttura del messaggio e le macro di cui ho bisogno
#ifndef FUNCTION_H
#define FUNCTION_H

//Specifico il tipo del messaggio
#define P1 1
#define P2 2

//Specifico le macro da usare nella funzione ftok
#define PATH "."
#define CHAR 'a'

#define SIZE sizeof(Messaggio)-sizeof(long)

//Specifico La struttura del messaggio
typedef struct{
    //Ogni processo inserisce all'interno del tipo del messaggio un proprio identificatore
    long process;

    //Inserisce poi un numero float casuale 
    float numero;
} Messaggio;

//Specifica della funzione che genera un float all'interno di un intervallo
float generoFloat(int sx, int dx);

#endif