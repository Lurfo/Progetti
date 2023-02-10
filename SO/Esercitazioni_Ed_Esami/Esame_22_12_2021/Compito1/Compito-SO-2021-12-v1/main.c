#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "header.h"

#define NUM_PRODUTTORI 2
#define NUM_CONSUMATORI 5

#define PRODUZIONI 10
#define CONSUMAZIONI 4

void * produttore(void *);
void * consumatore(void *);

typedef struct {

    

    /* TBD: Completare questa struttura dati, per il passaggio
     *      dei parametri ai thread consumatori
     */

    //Siccome il consumatore ha bisogno di andare ad operare sia sul vettore che sul buffer, allora
    //nella struttura devo andare ad inserire due puntatori, uno al vettore ed uno al buffer 

    VettoreProdCons *vett; 
    BufferMutuaEsclusione *buff;

} parametri_consumatore;

int main() {

    //variabile di controllo
    int ret;

    //Imposto attributo
    pthread_attr_t attr; 

    pthread_attr_init(&attr); 

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    //Imposto vettori che contendono l'id dei thread 
    pthread_t produttori[NUM_PRODUTTORI]; 
    pthread_t consumatori[NUM_CONSUMATORI];

    //Ottento il riferimento alle due locazioni di memoria, tramite la funzione malloc
    VettoreProdCons * vettore = (VettoreProdCons *) malloc(sizeof(VettoreProdCons));

    BufferMutuaEsclusione * buffer = (BufferMutuaEsclusione *) malloc(sizeof(BufferMutuaEsclusione));

    srand(getpid());

    inizializza_vettore(vettore);

    inizializza_buffer(buffer);

    //Prima della creazione dei thread, aggiorno i campi della struct che deve essere passata ai consumatori
    parametri_consumatore *cons = (parametri_consumatore *) malloc(sizeof(parametri_consumatore));

    //In questo modo i puntatori della struttura puntano alle stesse locazioni dei vettori che ho ottenuto sopra
    cons->vett=vettore; 
    cons->buff=buffer;


    for(int i=0; i<NUM_PRODUTTORI; i++) {

        /* TBD: Creare i thread produttori, passandogli
         *      in ingresso la variabile "vettore"
         */
        ret = pthread_create(&produttori[i], &attr, produttore, (void *) vettore);

            if(ret){
                perror("Errore creazione produttori\n"); 
                    exit(1);
            }


    }


    for(int i=0; i<NUM_CONSUMATORI; i++) {

        /* TBD: Creare i thread consumatori, passandogli
         *      in ingresso le variabili "vettore" e "buffer"
         *      mediante la struttura "parametri_consumatore"
         */
        ret  = pthread_create(&consumatori[i], &attr, consumatore, (void *) cons); 

            if(ret){
                perror("Errore creazione cosumatore\n"); 
                    exit(1);
            }

    }


    /* TBD: Attendere la terminazione dei thread produttori e dei
     *      thread consumatori
     */

    //Imposto una variabile di stato per controllare la corretta terminazione dei thread
    int status;

    for(int i=0; i<NUM_PRODUTTORI; i++){
        pthread_join(produttori[i], (void *) &status);

            if((int) status==-1){
                printf("Il thread produttore %lu, è terminato con un errore!\n", produttori[i]);
                    exit(1);
            }

    }

    for(int i=0; i<NUM_CONSUMATORI; i++){
        pthread_join(consumatori[i],(void *) &status);

            if((int) status==-1){
                printf("Il thread consumatore %lu, è terminato con un errore\n", consumatori[i]);
                    exit(1);
            
            }
    }


    rimuovi_buffer(buffer);
    rimuovi_vettore(vettore);
    
    
    /* TBD: Deallocare le strutture dati */
    free(vettore); 
    free(buffer);
    free(cons);

    pthread_exit(NULL);
}

void * produttore(void * p) {

    //Effettuo casting inverso dell'argomento della funzione 
    VettoreProdCons *vett = (VettoreProdCons *) p;


    for(int i=0; i<PRODUZIONI; i++) {

        int valore = rand() % 10;

        printf("[MAIN PRODUTTORE] Produzione: %d\n", valore);

        /* TBD: Invocare il metodo "produci()" */

        //Invoco la funzione di produzione
        produci(vett, valore);

    }

    pthread_exit(NULL);
}

void * consumatore(void * p) {

    //Effettuo il casting inverso dellla struttura che contiene i dati dei consumatori
    parametri_consumatore *par = (parametri_consumatore *) p;

    for(int i=0; i<CONSUMAZIONI; i++) {

        int valore;

        //La funzione di consumazione prende in ingresso il vettore
        valore = consuma(par->vett);

        printf("[MAIN CONSUMATORE] Consumazione: %d\n", valore);

        /* TBD: Invocare il metodo "aggiorna()", passandogli
         *      in ingresso il valore che è stato appena consumato
         */

        //La funzione di aggiornamento, prende in ingresso il buffer e il valore che ho ottenuto
        aggiorna(par->buff, valore);

    }


    //Subito dopo il thread termina
    pthread_exit(NULL);
}