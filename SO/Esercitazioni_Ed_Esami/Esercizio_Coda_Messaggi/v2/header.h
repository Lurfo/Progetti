#ifndef HEADER_H
#define HEADER_H

//Mi definisco il numero di processi generatori ed il numero di volte che un processo generatore va a produrre un
//messaggio
#define NUM_GENERATORI 3
#define NUM_INVII 2

//Parametri della dimensione della stringa e dell'array
#define MAX 10
#define NUM 2

//Posso provare ad inviare i messaggi all'interno della medesima coda, ogni processo dovrà poi controllare il messaggio
//e vedere quale di questi deve prelevare, in base al suo tipo
//In questo modo posso "risparmiare" usando una sola coda di messaggi
#define TYPE_GENERATOR 1
#define TYPE_FILTRO 2
#define TYPE_CHECKSUM 3

#define PATH "."
#define CHAR 'a'


#define SIZE sizeof(Messaggio)-sizeof(long)

typedef struct{
    //Inserisco il tipo del messaggio
    long type;

    char string[MAX];

    int arr[NUM];

    int var;
}Messaggio;

#endif