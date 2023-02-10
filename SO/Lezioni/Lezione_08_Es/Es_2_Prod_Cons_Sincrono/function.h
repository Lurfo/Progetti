//Definisco tramite una macro i vari tipi di messaggio che posso avere
//Questi sono per il canale di comunicazione
#define REQUEST_TO_SEND 1
#define OK_TO_SEND 2

//Questo identifica il messaggio vero e proprio
#define MESSAGGIO 3

#define MAX 100

#define SIZE sizeof(Messaggio)-sizeof(long)

typedef struct{
    long type;

    char string[MAX];

}Messaggio;

//Definisco le funzioni di cui ho bisogno!
void sendSincrona(Messaggio* mess, int queue); 

void receiveBloccante(Messaggio* mess, int queue, int tipoMess);

void produttore(int queue);
void consumatore(int queue);

//Definisco delle funzioni che vanno a fungere da inizializzatori per e code di servizio che uso
void initService(); 
void removeService();