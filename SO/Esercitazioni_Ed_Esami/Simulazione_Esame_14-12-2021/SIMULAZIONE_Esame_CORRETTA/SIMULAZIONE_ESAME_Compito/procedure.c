#include "header.h"
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <string.h>

int coda_RTS;
int coda_OTS;

void initServiceQueues(){

    /* TODO: Inizializzazione code di servizio */
        //Utilizzo la funzione di msgget per ottenere l'id delle code
    
    coda_RTS = msgget(IPC_PRIVATE, IPC_CREAT|0660);
    printf("Coda di servizio coda_RTS create con desc: %d\n", coda_RTS);
    
    coda_OTS = msgget(IPC_PRIVATE, IPC_CREAT|0660);
    printf("Coda di servizio coda_OTS create con desc: %d\n", coda_OTS);
}

void removeServiceQueues(){
    
    /* TODO: rimozione code di servizio */
    //Rimuovo le code, usando sempre la funzione di controllo
    msgctl(coda_RTS, IPC_RMID, NULL); 
    msgctl(coda_OTS, IPC_RMID, NULL);
    
}

// Send Sincrona
void inserisci_risultato (Risultato *m , int queue){
    
    /* TODO: Implementare il protocollo per la send sincrona e inviare il messaggio
     * per l'inserimento del risultato
     */

    //In questo caso, devo implementare la funzione che va ad inserire un elemento all'interno della coda dei risultati
    //la coda che però devo utilizzare, deve essere una coda sincrona, dunque vuol dire che devo andare ad effettuare
    //un protocollo di handshake, prima di poter procedere all'invio del messaggio
    //La funzione di send sincrona, prevede proprio che ci sia proprio questo scambio di messaggi!

    //Definisco due messaggi di controllo 
    Risultato m1, m2;

    int ret;

    //Invio la richiesta di invio
    m1.type=WAIT_CONFIRM;
    m1.mess=1;

    ret = msgsnd(coda_RTS, (void *) &m1, SIZE(Controllo), 0);

        if(ret<0){
                perror("Errore nell'invio del messaggio di controllo WAIT_CONFIRM\n"); 
                exit(1);
        }

    //Attendo che mi arrivi il messaggio di ok, per procedere con l'invio!
    ret = msgrcv(coda_OTS, (void *) &m2, SIZE(Controllo), OK_SEND, 0);

        if(ret<0){
                perror("Errore nella ricezione del messaggio di controllo OK_SEND\n"); 
                exit(1);
        }

     //A questo punto, posso mandare il messaggio sulla coda dei risultati

     ret = msgsnd(queue, (void *) m, SIZE(Risultato), 0);

     printf("[invio_risultato] Messaggio Risultato inviato\n");

        if(ret<0){
                perror("Errore nell'invio del messaggio RISULTATO\n"); 
                        exit(1);
        }



}

// Receive Bloccante
int preleva_risultato(Risultato *m, int queue, int tipomess){
    
    /* TODO: Implementare il protocollo per la send sincrona e ricevere il messaggio
     * per il prelevamento del risultato
     */

    //La funzione di prelievo del risultato è ovviamente molto simile a quella di inserimento del risultato
    
    //Mi definisco i due messaggi di controllo
   Risultato m1, m2;

    int ret; 
    
    //Imposto il messaggio di OK_SEND
    m2.type=OK_SEND;
    m2.mess=1;

    //Devo attendere il messaggio di WAIT_CONFIRM
    
    ret = msgrcv(coda_RTS, (void* ) &m1, SIZE(Controllo), WAIT_CONFIRM, 0);

        if(ret<0){
                perror("Errore nella ricezione del messaggio WAIT_CONFIRM\n");
                exit(1);
        }

    ret = msgsnd(coda_OTS, (void *) &m2, SIZE(Controllo), 0);

        if(ret<0){
                perror("Errore nell'invio del messaggio OK_SEND\n"); 
                exit(1);
        }

    
    //A questo punto, mi metto in attesa del messaggio del risultato che mi deve arrivare

    ret = msgrcv(queue, (void *) m, SIZE(Risultato), tipomess, 0);

    printf("[Prelevo_Risultato] Messaggio Risultato ottenuto!\n");

        if(ret<0){
                perror("Errore nella ricezione del messaggio RISULTATO_TYPE\n"); 
                exit(1);
        }

    
    return m->mess;
}

void inserisci_operando(MonitorOperandi * m, int operando){

    /* TODO: Implementare la sincronizzazione richiesta tramite monitor
     * gestendo opportunamente la produzione degli operandi
     */

    //Entro nel mutex
    pthread_mutex_lock(&(m->mutex));

        //Eseguo un controllo della condione, il produttore si deve sospendere se i posti sono già tutti occupati
        while(m->numOccupati==DIM_BUFFER){
                //In questo caso, se è vero, effettua una wait sulla condizione dei produttori
                pthread_cond_wait(&(m->vc_Produttori), &(m->mutex));
        }

        //Aumenti il numero di posti occupati
        m->numOccupati++; 

        //Produco il messaggio in testa
        m->operandi[m->testa]=operando;

        //Incremento operatore di testa
        m->testa=(m->testa+1)%DIM_BUFFER;

        //A questo punto, prima di lasciare il mutex, devo andare a segnalate i thread consumatori
        //in particolare, posso porre che vengono segnalati i threas consumatori solo se sono presenti almeno due elementi
        //nel buffer
        if(m->numOccupati>=2){
                pthread_cond_signal(&(m->vc_Consumatori));
        }

    //Posso quindi lasciare il monitor
    pthread_mutex_unlock(&(m->mutex));

}

int * preleva_operando(MonitorOperandi * m){

        static int operando[2];

        /* TODO: Implementare la sincronizzazione richiesta tramite monitor
         * gestendo opportunamente la consumazione degli operandi
         */

        //Il consumatore, deve effettuare delle operazioni molto simili a quelle del produttore

        //Lock sul mutex
        pthread_mutex_lock(&(m->mutex)); 

                //Effettuo un controllo sulla condizione, i consumatori si devono sospendere sulla loro condizione
                //fino a quando non ci sono due elementi
                //Dunque devo andare a controllare che il numero di elementi presenti nel buffer sia maggiore di 2!
                while(m->numOccupati<2){
                        pthread_cond_wait(&(m->vc_Consumatori), &(m->mutex));
                }

                //A questo punto, decremento il numero di elementi occupati di due, ogni consumatore
                //preleva due elementi alla volta

                m->numOccupati-=2;

                //Dunque posso andare a consumare in coda
                for(int i=0; i<2; i++){
                        operando[i]=m->operandi[m->coda];

                        //Devo anche incrementare il puntatore di coda
                        m->coda=(m->coda+1)%DIM_BUFFER;
                }

                //A questo punto, vado a segnalare due produttori, poichè ho due posizioni che sono state liberate
                for(int i=0; i<2; i++){
                        pthread_cond_signal(&(m->vc_Produttori));
                }

        //Posso dunque andare a sbloccare il mutex
        pthread_mutex_unlock(&(m->mutex));

    
        return operando;

}

void * genera_operandi(void *m){

        int i, op;

        //Effettuo il casting inverso
        MonitorOperandi * mon = (MonitorOperandi *) m;
    
        for (i=0; i<6; i++){
        
                // call inserisci_operando generato da 1 a 10
                op = 1 + rand() % 10;
                printf("[thread genera_operandi] Operando generato: %d\n", op);
                inserisci_operando(mon, op);
                 
        }
        pthread_exit(0);
}

void preleva_risultati(int coda_risultati){

        int i, risultato, less=0, great=0;
    
        Risultato m;
    
        for (i=0; i<6; i++){
        
            
                //risultato = preleva_risultato(mon);
                risultato = preleva_risultato(&m, coda_risultati, RISULTATO_TYPE);
                printf("[processo preleva_risultati] Risultato prelevato: %d coda: %d\n", risultato, coda_risultati);
            
                if (risultato<=25)
                    less++;
                else
                    great++;
                 
        }
    
        printf("[processo preleva_risultati] STATS: Conteggio minore uguale: risultato: %d\n", less);
        printf("[processo preleva_risultati] STATS: Conteggio maggiore: %d\n", great);
        exit(0);
}


void * calcola(void *mon){

        int i, calc;
        int *op;

        //Vado ad effettuare il casting inverso
        MonitorOperandi * mon_op = (MonitorOperandi *) mon;
    
        Risultato m; //messaggio da inviare

        m.type=RISULTATO_TYPE;
    
        for (i=0; i<2; i++){
        
                // preleva operando
                op = preleva_operando(mon_op);
                int op1 = *op;
                int op2 = *(op+1);
                printf("[thread calcola] Preleva op1: %d op2: %d\n", op1, op2);

                // calcola
                calc = (op1*op1) + (op2*op2);

                printf("[thread calcola] Calcola somma dei quadrati (%d x %d) + (%d x %d) = %d\n", op1, op1, op2, op2, calc);
                // inserisci risultato
            
                printf("[thread calcola] Inserisci risultato: %d tramite send sincrona su coda: %d\n", calc, coda_risultati);
                sleep(1);
            
                /* TODO: Impostare il messaggio da inviare */
                m.mess=calc;
            
                inserisci_risultato(&m , coda_risultati);
        }
    
        pthread_exit(0);
}
