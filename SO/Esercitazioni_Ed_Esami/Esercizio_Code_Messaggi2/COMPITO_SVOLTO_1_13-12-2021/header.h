#define MSG_TYPE_CONTROL_PROXY 1
#define MSG_TYPE_ARRIVI 2
#define MSG_TYPE_PARTENZE 3

#define REQUEST_TO_SEND 4
#define OK_TO_SEND 5

//Mi definsco la macro per la dimensione del messaggio
#define SIZE(x) sizeof(x)-sizeof(long)

extern int coda_RTS;
extern int coda_OTS;

// Struttura che definisce un Volo
typedef struct {
    
    /* To be completed */

    //Inserisco il tipo del messaggio
    long type;
    
    int ID;
    char direzione [10];
    char citta_partenza [20];
    char citta_arrivo [20];

}Volo;

/* Struttura che definisce un messaggio di controllo per implementare
 * la send sincrona
 */
typedef struct {
    
    /* To be completed */
    //Il messaggio di controllo deve contenere il tipo ed, evetualmente, il corpo
    long type; 

    char mess;
    
}Control;

void controllore(int ds_queue_control_proxy);
void proxy(int ds_queue_control_proxy, int ds_queue_proxy_gestori);
void gestore_arrivi(int ds_queue_proxy_gestori);
void gestore_partenze(int ds_queue_proxy_gestori);

void initServiceQueues();
void removeServiceQueues();
