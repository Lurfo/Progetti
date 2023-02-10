//Specifica del nimero di semafori di cui ho bisogno!

//Semafori per la sincronizzazione tra produttori e consumatori
#define SPAZIO_DISPONIBILE  0
#define MESSAGGIO_DISPONIBILE   1

//Semafori per la gestione della concorrenza!
#define MUTEX_C 2
#define MUTEX_P 3

//Definisco l'ampiezza massima del vettore di stato!
#define DIM  20

//Posso anche andare a definire il numero di produttori e consumatori
#define NUMERO_PRODUTTORI 40
#define NUMERO_CONSUMATORI 40

//IN QUESTO CASO, DEVO DEFINIRE ANCHE I TRE STATI CHE PUÒ ASSUMERE IL VETTORE DI STATO!
#define BUFFER_VUOTO 0
#define SPAZIO_IN_USO 1
#define SPAZIO_PIENO 2

//Definsco la struttura che specifica il mio buffer di memoria!
//Nella struct oltre
typedef struct{
    int buffer[DIM]; 
    int vetto[DIM];
} buffer;

//Signature delle funzioni di produttore e consumatore!
void produttore(buffer* mem, int semID); 
void consumatore(buffer* mem, int semID);



