//Specifica delle funzioni di consumazione e di produzione del messaggio!


//Uso una macro per andare a specificare il numero del semaforo!

//ATTENZIONE, QUESTI DUE SEMAFORI, NON SONO GLI UNICI CHE DEVO UTILIZZARE
//QUESTI SERVONO A GESTIRE LA SINCRONIZZAZIONE TRA PRODUTTORE E CONSUMATORE!
#define SPAZIO_DISPONIBILE 0
#define MESSAGGIO_DISPONIBILE 1
//Questi due bastano solo quando ho a che fare con un un produttore e un unico consumatore

//QUANDO HO PIÙ PRODUTTORI E PIÙ CONSUMATORI, DEVO AGGIUNGERE ALTRI SEMAFORI CHE VANNO A GESTIRE LA COMPETIZIONE TRA PRODUTTORI
//E LA COMPETIZIONE DI CONSUMATORI
//Vale a dire che un produttore alla volta può produrre e un consumatore alla volta può consumare (una differenza con il meccanismo lettori scrittori)

//Le operazioni di lettura e scrittura le devo eseguire IN MUTUA ESCLUSIONE!

//Definsco i due semafori che vanno a regolamentare la concorrenza!
#define MUTEX_C 2
#define MUTEX_P 3

//In totale avrò quindi 4 SEMAFORI!

//-------------------------------------------------------------------------------------------------------------------------------------

//Macrco per la dimensione del vettore
#define DIM 3 //Voglio che la coda debba contenere un massimo di 3 elementi!


//---------------------------------------------------------------------------------------------------------------------------

//Struttura del buffer circolare 
//questa struttura sarà quella che deve essere condivisa tra i processi!
struct circular{
    int buffer[DIM]; 

    //Il buffer contiene anche un indicazione della posizione di testa e della posizione di coda
    //Testa rappresenta la posizione del primo elemento libero in testa, disponibile alla memorizzazione
    //Ovviamente inizializzato al primo elemento della lista
    int testa; 

    //Rappresenza la posizione dell'elemento di cosa, quello che occupa la posizione 0, nel buffer!
    int coda; 
};

//-------------------------------------------------------------------------------------------------------------------------------

//Firma delle funzioni di produttore e consumatore
//Devono entrambe ricevere, l'id del semaforo, il puntatore alla memoria condivisa 
void produttore(struct circular* mem, int semID);

//Considerando che i consumatori devono partire dalla coda!
void consumatore(struct circular* mem, int semID);
