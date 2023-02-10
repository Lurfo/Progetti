//Specifico quale deveno essere le funzioni di invio e ricezione del messaggio e la sua struttura
#define MAX 100

//Definisco una macro per la dimensione del mio messaggio
#define SIZE sizeof(Messaggio)-sizeof(long)

typedef struct{
    long type; 
    char string[MAX];
} Messaggio;

//Entrambe le funzioni ricevono come ingresso l'id della coda, il resto viene fatto tutto durante il processo
void ricezione(int queue_ricez);
void invio(int queue_invio);