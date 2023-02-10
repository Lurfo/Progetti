#ifndef HEADER_H
#define HEADER_H

#define NUM_GENERATORI 3
#define NUM_INVII 2

#define MAX 10
#define NUM 2

//Posso provare ad inviare i messaggi all'interno della medesima coda, ogni processo dovrà poi controllare il messaggio
//e vedere quale di questi deve prelevare, in base al suo tipo
//In questo modo posso "risparmiare" usando una sola coda di messaggi
#define TYPE_GENERATOR 1
#define TYPE_FILTRO 2
#define TYPE_CHECKSUM 3
#define TYPE_VISUALIZZATORE 4

#define SIZE sizeof(Messaggio)-sizeof(long)

typedef struct{
    //Inserisco il tipo del messaggio
    long type;

    char string[MAX];

    int arr[NUM];

    int var;
}Messaggio;

void generator(int queue); 
void filtro(int queue); 
void checksum(int queue);
void visualizzatore(int queue);

#endif