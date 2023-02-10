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

    /* TBD: Inizializzazione code di servizio */

    //Per invio e ricezione dei messaggi di sincronizzazione
    
    coda_RTS = msgget(IPC_PRIVATE, IPC_CREAT|0660);
    printf("Coda di servizio coda_RTS create con desc: %d\n", coda_RTS);
    
    coda_OTS = msgget(IPC_PRIVATE, IPC_CREAT|0660);
    printf("Coda di servizio coda_OTS create con desc: %d\n", coda_OTS);
}

void removeServiceQueues(){
    
    /* TBD: rimozione code di servizio */

        msgctl(coda_RTS, IPC_RMID, NULL); 
        msgctl(coda_OTS, IPC_RMID, NULL);
    
}

// Send Sincrona
void inserisci_risultato (Risultato *m , int queue){
    
    /* TBD: Implementare il protocollo per la send sincrona e inviare il messaggio
     * per l'inserimento del risultato
     */
        int ret;

        Controllo m1, m2;

        m1.type=WAIT_CONFIRM;

        m1.payload=1;

        //Come prima coda, il thread che invoca la funzione di inserimento all'interno della coda, invia un messaggio
        //di richiesta di invio sulla coda delle richieste

        //Effettuo una send del messaggio di richiesta
        ret = msgsnd(coda_RTS, (void *) &m1, SIZE(Controllo), 0);

        printf("[INSERIMENTO] Messaggio controllo inviato\n");

        if(ret<0){
                perror("Errore send del messaggi di attesa di conferma\n");
        }

        //Dopo la richiesta, attendo il messaggio di conferma
        ret = msgrcv(coda_OTS, (void *) &m2, SIZE(Controllo), PROCEDI, 0);

        if(ret<0){
                perror("Errore nella ricezione del messaggio di procedere con l'invio\n"); 
                        exit(1);
        }

        printf("[INSERIMENTO] Messaggio controllo ricevuto\n");

        //Posso dunque procedere con l'invio del messaggio sulla coda dei risultati 
        ret = msgsnd(queue, (void *) &m, SIZE(Risultato), 0); 

        if(ret<0){
                perror("Errore invio del messaggio risultato!\n");
                        exit(1);
        }

        printf("[INSERIMENTO] Messaggio inviato\n");

}

// Receive Bloccante
int preleva_risultato(Risultato *m, int queue, int tipomess){
    
    /* TBD: Implementare il protocollo per la send sincrona e ricevere il messaggio
     * per il prelevamento del risultato
     */

        Controllo m1, m2;

        int ret;
        

        //La funzione di prelievo funziona bene o male allo stesso modo 

        //Inizialmente attende che le sia inviato un messaggio di richiesta di invio
        //si mette dunque in attesa sulla coda dei messaggi di richiesta
        //effettuando una receive bloccante
        ret = msgrcv(coda_RTS, (void *) &m1, SIZE(Controllo), WAIT_CONFIRM, 0);

        printf("[PRELIEVO_CODA] Ho ricevuto messaggi di procedere con invio!\n"); 

        if(ret<0){
                perror("Errore nella ricezione del messaggio di attesa conferma\n"); 
                        exit(1);
        }

        //Dunque, vado ad inviare il messaggio di procedere con l'invio
        m2.type=PROCEDI; 
        m2.payload=1;

        //Procedo con l'invio del messaggio
        ret = msgsnd(coda_OTS, (void *) &m2, SIZE(Controllo), 0); 

        printf("[PRELIEVO_CODA] Invio messaggio controllo\n");

        if(ret<0){
                perror("Errore nell' invio del messaggio di procedere con l'invio\n"); 
                        exit(1);
        }

        //Di conseguenza, posso andare a ricevere il messaggio!
        ret = msgrcv(queue, (void *) m, SIZE(Risultato), tipomess, 0);

        if(ret<0){
                perror("Errore nella ricezione del messaggio risultato\n");
                        exit(1);
        }

        printf("[PRELIEVO_CODA] Messaggio prelevato\n");

    
    return m->mess;
}

void inserisci_operando(MonitorOperandi * m, int operando){

    /* TBD: Implementare la sincronizzazione richiesta tramite monitor
     * gestendo opportunamente la produzione degli operandi
     */

        //Il produttore, effettua un lock sul mutex

        //printf("[GENERATORE]Entro mutex generatore\n");

        pthread_mutex_lock(&(m->mutex)); 

                //printf("[GENERATORE]Controllo varibile\n");

                //Effettuo un controllo sulla variabile
                while(m->numOccupati==DIM_BUFFER){
                        //In questo caso il buffer è pieno, quindi il thread si pone in attesa di poter procedere nuovamente alla
                        //produzione
                        //printf("[GENERATORE]Effettuo signal\n");
                        pthread_cond_wait(&(m->vcProduttori), &(m->mutex));
                }

                //printf("[GENERATORE]Sblocco variabile\n");

                //Se mi trovo in questo punto, allora vuol dire che sono stato sbloccato, dunque incremento il numero di posti occupati
                m->numOccupati++; 
                //printf("[GENERATORE]Aumento occupati\n");


                //Posso andare a produrre in testa
                m->operandi[m->testa]=operando;
                //printf("[GENERATORE]Salvato operando\n");

                //Avanzo il putatore di testa
                m->testa=(m->testa+1)%DIM_BUFFER;
                //printf("[GENERATORE]Aumento testa\n");


                //Siccome il numero di elementi che i consumatori devo consumare deve essere maggiore di 2, effettuo una
                //signal, solo se il numero di elementi occupati è maggiore di 2 
                if(m->numOccupati>=2){
                        //printf("[GENERATORE]Segnalo consumatori\n");
                        pthread_cond_signal(&(m->vcConsumatori));
                }

        //printf("[GENERATORE]Esco dal mutex\n");
        //Posso dunque lasciare il monitor, in modo da permettere anche agli altri produttori di poter produrre
        pthread_mutex_unlock(&(m->mutex));


}

int * preleva_operando(MonitorOperandi * m){

        static int operando[2];

        /* TBD: Implementare la sincronizzazione richiesta tramite monitor
         * gestendo opportunamente la consumazione degli operandi
         */

        //Il consumatore, agisce allo stesso modo del produttore

        //Effettuo un lock sul mutex
        //printf("[PRELEVO] Entro nel mutex\n");
        pthread_mutex_lock(&(m->mutex)); 

        //printf("[PRELEVO] SONO NEL MUTEX\n");
                //Controllo la mia condizione
                //In questo caso, il thread consumatore, deve prelevare due valori, dunque mi devo sempre
                //assicurare che il nuemro di occupati sia maggiore di 2!
                //in caso contrario, mi devo sospendere sulla condizione

                //printf("[PRELEVO] Attesa della condizione\n");
                while(m->numOccupati < 2){
                        pthread_cond_wait(&(m->vcConsumatori), &(m->mutex));
                }

                //printf("[PRELEVO] Sbloccato, decremento numero disponibili\n");

                //Se sono qui, sono stato sbloccato, dunque posso procedere

                //Siccome vado a prelevare 2 elementi, vado a decrementare il numero di occupati di 2
                m->numOccupati-=2;

                //Mi salvo i due valori
                for(int i=0; i<2; i++){

                        //printf("[PRELEVO] Mi salvo valore %d nel mio array!\n", i+1);
                        operando[i]=m->operandi[m->coda]; 
                        m->coda=(m->coda+1) % DIM_BUFFER;
                }

                //Posso dunque segnalare due processi che sono in attesa sulla condizione, in modo che essi vengano risvegliati
                //poichè sono andato a consumare su due valori
                for(int i=0; i<2; i++){
                        //printf("[PRELEVO] sengalo thread produttore %d\n", i+1);
                        pthread_cond_signal(&(m->vcProduttori));

                }

        //printf("[PRELEVO] Lascio mutex\n");
        //Posso dunque lasciare il mutex 
        pthread_mutex_unlock(&(m->mutex));

    printf("Ritorno operando\n");
        return operando;
}

void * genera_operandi(void *m){

        int i, op;

        //Eseguo il casting inverso per ottenere la mia struttura
        MonitorOperandi * mon = (MonitorOperandi *) m;

        //printf("[GENERATORE]Ho ottenuto la struttura\n");

        for(i=0; i<6; i++){
        
                // call inserisci_operando generato da 1 a 10
                op = 1 + rand() % 10;
                printf("[thread genera_operandi] Operando generato: %d\n", op);
                inserisci_operando(mon, op);
                 
        }

        printf("Esco dal generatore\n");

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

        //Casting inverso per ottenere il puntatore alla struttura monitor
        //printf("[PRELEVATORE]Ottengo struttura monitor\n");
        MonitorOperandi * mon_op = (MonitorOperandi *) mon;
    
        Risultato m; //messaggio da inviare

        //Il messaggio deve avere il tipo pari a risultato
        //Lo posso impostare direttamente fuori, perchè il tipo del messaggio non deve cambiare
        m.type=RISULTATO_TYPE; 
     
        //printf("[PRELEVATORE]Ho impostato il tipo\n");

        for (i=0; i<2; i++){
        
                // preleva operando
                //printf("[PRELEVATORE] Prelievo operndo\n");
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
            
                /* TBD: Impostare il messaggio da inviare */
                //Inserisco nel messaggio, il risultato che ho ottenuto
                m.mess=calc;
            
                inserisci_risultato(&m , coda_risultati);

        }

        printf("Esco dal cacolo\n");
    
        pthread_exit(0);
}
