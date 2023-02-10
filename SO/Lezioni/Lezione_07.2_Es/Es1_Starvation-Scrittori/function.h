//Definisco i semafori che mi occorono, nel mio caso, me ne occorrono due
#define MUTEXL 0

//Questo semaforo è usato come sincronizzatore per i lettori e gli scrittori e anche come mezzo per sincronizzare i soldi scrittori
#define SYNCH   1

//Definisco il numero di volte che mi interessa leggere e scrivere!
#define VOLTE 12

//Definisco la struttura
typedef struct{
    //Il messaggio
    long messaggio;

    //Definisco anche il numero di lettori che ci sono sulla risorsa!
    int numLettori;  

}buffer;

//Specifico la signature di produttori e scrittori
void scrittore(buffer* mem, int semID); 
void lettore(buffer* mem, int semID); 
