#define SPAZIO_DISPONIBILE 0 // Controllo lo spazio disponibile 
#define POSTO_DISPONIBILE 1 //Sarebbe il MESSAGGIO_DISPONIBILE
#define MUTEX_P 2 //Per gestire i produttori ne sono 50!

//Non mi serve un MUTEX_C perche' ne ho solo 1 di visualizzatore.

#define NUM_PRODUTTORI 50
#define NUM_CONSUMATORI 1
#define NUM_PROCESSI 51

#define posti 80
#define DISPONIBILITA 80

#define POSTO_LIBERO 0
#define POSTO_OCCUPATO 1
#define POSTO_INAGGIORNAMENTO 2

typedef struct{
	unsigned int id_cliente[posti];
	unsigned int stato[posti];
} posto;

void cliente(int *,posto *,int);
void visualizzatore(posto *,int);


