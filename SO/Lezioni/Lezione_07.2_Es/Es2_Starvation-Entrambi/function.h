//Definizione dei semafori di cui ho bisogno!

//Gestisce la mutua esclusione rispetto alla variabile Num_Scrittori, che tiene conto dell numero di scrittori che sono
//presenti
#define MUTEXS 0

//Come nel caso precedente, regola la mutua esclusione dei lettori, rispetto a Num_Lettori
#define MUTEXL 1

//Gestisce l'esclusione dei processi di scrittura
#define MUTEX 2

//Usato per la sincronizzazione!
#define SYNCH 3

//Definisco il numero totale di processi
#define TOT 10


//Definisco la struttura che poi sarà inserita come elemento di memoria condivisa
typedef struct{
    long numero; 

    //Inserisco le variabili di controllo del numero dei lettori e del numero di scrittori!
    int Num_Scrittori; 
    int Num_Lettori;

} buffer;

//Signature delle funzioni!
void scrittori(buffer* mem, int semID); 
void lettori(buffer* mem, int semID);