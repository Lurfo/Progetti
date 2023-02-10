//Definisco due semafori!
#define MUTEX_POSTO 0
#define MUTEX_DISPONIB 1

//Questo semaforo può essere utile al processo visualizzatore per accedere alla memoria e controllare i posti disponibili!
//In questo modo, se un cliente sta prenotando, il visualizzatore non accede prima che questi abbia concluso
#define ATTENDERE 2
#define PROSEGUO 3


//Definisco la dimensione del vettore di stato!
//ANCHE LA DISPONIVBILITÀ DEVE  ESSERE INIZIALIZZATA A QUESTO VALORE!
#define DIM 80

//Definisco il numero di processi clienti
#define NUM_PROCESSI 50

//Definisco gli stati che può assumere il posto!
#define LIBERO 0
#define OCCUPATO 1
#define AGGIORNAMENTO 2

//IMPLEMENTO DA PARTE IL PROCESSO VISUALIZZATORE!

//Definizione della struttura che mi occorre
//La memoria condivisa, contiene 80 elementi di tipo seduta!
typedef struct{
    unsigned int ID_cliente; 
    unsigned int stato;
} seduta;

//Implementazione definita "letteralmente" dalla traccia
//Implemento qui la funzione cliente, prende in ingresso la memoria e anch l'id del semaforo!
void cliente(seduta* mem, int* disp, int semID);

//Implementazione di una seconda "versione" della funzione cliente
void cliente2(seduta* mem, int* disp, int semID);

//Cambiare nel file "main.c" la funzione da eseguire per controllare il funzionamento di entrambe

