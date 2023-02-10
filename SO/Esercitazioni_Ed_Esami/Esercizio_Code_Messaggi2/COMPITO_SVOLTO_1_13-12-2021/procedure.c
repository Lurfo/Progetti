#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "header.h"

int coda_RTS;
int coda_OTS;


void initServiceQueues(){

    /* TBD: inizializzazione code per implementare la send sincrona */
    //Utilizz come chiave, IPC_PRIVATE
    coda_RTS = msgget(IPC_PRIVATE, IPC_CREAT|0660);
    printf("Coda di servizio coda_RTS create con desc: %d\n", coda_RTS);
    
    coda_OTS = msgget(IPC_PRIVATE, IPC_CREAT|0660);
    printf("Coda di servizio coda_OTS create con desc: %d\n", coda_OTS);
}

void removeServiceQueues(){
    /* TBD: rimozione code per implementare la send sincrona */
    //Utilizzo la funzione di msgctl per andare ad eliminare la coda
    msgctl(coda_RTS, IPC_RMID, NULL);
    msgctl(coda_OTS, IPC_RMID, NULL);

}


void controllore(int ds_queue_control_proxy){

    srand(time(NULL)*getpid());
    
    int ret;
    char citta_partenza[][20] = { "Napoli", "Roma", "Milano", "Torino", "Firenze"};
    char citta_destinazione[][20] = { "New York", "Madrid", "Londra", "Berlino", "Parigi"};
    
    Volo v_partenza;
    Volo v_arrivo;

    Control m1, m2;

    m1.type=REQUEST_TO_SEND;
    m1.mess='y';
    
    for (int i=0; i<10; i++){
        
        /* TBD: Implementare lo scambio di messaggi necessario per
         * avere una send sincrona */



        //Per andare ad implementare la cosa sincrona, devo andare a definire un protocollo di handshake tra controllore e
        //proxy

        //Il Controllore invia una richiesta come primo passo

            //printf("GESTORE invio richiesta\n");

        ret = msgsnd(coda_RTS, (void *) &m1, SIZE(Control), 0);

            //printf("GESTORE richiest inviata\n");

            if(ret<0){
                perror("CONTROLLORE Errore invio REQUEST TO SEND\n"); 
                    exit(1);
            }

        //Mi metto in attesa del messaggio di ok

            //printf("GESTORE ricevo ok\n");

        ret = msgrcv(coda_OTS, (void *) &m2, SIZE(Control), OK_TO_SEND, 0); 

                printf("GESTORE ok ricevuto\n");

            if(ret<0){
                perror("GESTORE Errore nella ricezione del messaggio\n"); 
                    exit(1);
            }

        //Dopo che ho ricevuto il messaggio, posso procedere con l'invio del messaggio volo, considerando se il volo è 
        //in partenza o meno
        
            //printf("GESTORE entro nell'if\n");

        if (i%2 == 0){
            
            /* TBD: Implementare invio messaggi per voli in ARRIVO */
            //Imposto tutti i valori del volo 
            v_arrivo.type=MSG_TYPE_CONTROL_PROXY;

            v_arrivo.ID= rand() % 1305+1;

            strcpy(v_arrivo.direzione, "arrivo");

            strcpy(v_arrivo.citta_arrivo, citta_destinazione[rand() % 5]); 

            strcpy(v_arrivo.citta_partenza, citta_partenza[rand() % 5]);

            //Mando il messaggio del volo di partenza
            ret = msgsnd(ds_queue_control_proxy, (void *) &v_arrivo, SIZE(Volo), 0); 

                if(ret<0){
                    perror("CONTROLLORE invio volo arrivo\n");
                        exit(1);
                }
            
            
        }
    
        else {

            /* TBD: Implementare invio messaggi per voli in PARTENZA */
            v_partenza.type=MSG_TYPE_CONTROL_PROXY;

            v_partenza.ID = rand() % 2945+1;

            strcpy(v_partenza.direzione, "partenza");

            strcpy(v_partenza.citta_arrivo, citta_destinazione[rand()%5]);

            strcpy(v_partenza.citta_partenza, citta_partenza[rand()%5]);

            ret = msgsnd(ds_queue_control_proxy, (void *) &v_partenza, SIZE(Volo), 0);

                if(ret<0){
                    perror("CONTROLLORE invio volo partenza\n"); 
                        exit(1);
                }

        }
        
    }
    exit(0);
    
}
void proxy(int ds_queue_control_proxy, int ds_queue_proxy_gestori){
    
    int  ret;
    Volo v;

    Control m1, m2; 

    m2.type=OK_TO_SEND; 
    m2.mess='y';


    for ( int i=0; i<10; i++){
        
        /* TBD: Implementare lo scambio di messaggi necessario per
         * avere una send sincrona */


        //La proxy, deve implementare lo stesso handshake del controllore

        //Inizialmente, attendo un messaggio di request

            //printf("PROXY attendo request\n");

        ret = msgrcv(coda_RTS, (void *) &m1, SIZE(Control), REQUEST_TO_SEND, 0);

            if(ret<0){
                perror("PROXY Errore attesa REQUEST TO SEND\n"); 
                    exit(1);
            }

        //Invio il messaggio ok

            //printf("PROXY invio ok\n");

        ret = msgsnd(coda_OTS, (void *) &m2, SIZE(Control), 0);

            if(ret<0){
                perror("PROXY Errore invio OK TO SEND\n"); 
                    exit(1);
            }
        
        /* TBD: Aggiungere la ricezione del volo vero e proprio */

        //Dunque, attendo che mi arrivi il messaggio del volo
            
            //printf("PROXY attendo volo\n");

        ret = msgrcv(ds_queue_control_proxy, (void *) &v, SIZE(Volo), MSG_TYPE_CONTROL_PROXY, 0);

            //printf("PROXY volo ricevuto\n");

            if(ret<0){
                perror("PROXY Errore ricezione del volo\n"); 
                    exit(1);
            }            
        
        /* TBD: Aggiungere il codice per inviare opportunamente il volo
         * ricevuto al Gestore Arrivi o al Gestore Partenze
         */

        //A questo punto, analizzo il messaggio del volo e vedo quale tipo impostare e lo invio al gestore
        if(strcmp(v.direzione, "arrivo")==0){
            v.type=MSG_TYPE_ARRIVI;
        }

        else{
            v.type=MSG_TYPE_PARTENZE;
        }
        
        //A questo punto, lo invio sulla coda con i gestori!

        ret = msgsnd(ds_queue_proxy_gestori, (void *) &v, SIZE(Volo), 0); 

            if(ret<0){
                perror("PROXY Invio volo al gestore\n"); 
                    exit(1);
            }

        sleep(1);


    }
    exit(0);
}

void stampa_volo_info(Volo *v){
    
    printf("STAMPO INFO VOLO\n");
    printf("..........................ID: %d\n", v->ID);
    printf("..........................direzione: %s\n", v->direzione);
    printf("..........................citta_partenza: %s\n", v->citta_partenza);
    printf("..........................citta_arrivo: %s\n", v->citta_arrivo);
    
}

void gestore_arrivi(int ds_queue_proxy_gestori){
    
    int ret, i;
    Volo v;
    
    for (i=0; i<5; i++){
        
        /* TBD: Ricezione voli in ARRIVO */
        //Il gestore arrivi fa una recieve e prende solo i voli che hanno come tipo l'arrivo
        ret = msgrcv(ds_queue_proxy_gestori, (void *) &v, SIZE(Volo), MSG_TYPE_ARRIVI, 0);

            if(ret<0){
                perror("GESTORE ARRIVI Errore ricezione\n"); 
                    exit(1);
            }
        
        printf("\n\n****** ARRIVI ******\n\n");
        stampa_volo_info(&v);
    }
    exit(0);
}

void gestore_partenze(int ds_queue_proxy_gestori){
    
    int ret, i;
    Volo v;
    for (i=0; i<5; i++){
        
        /* TBD: Ricezione voli in PARTENZA */

        //Il gestore delle partenze fa una selezione dei messaggi di partenza
        ret = msgrcv(ds_queue_proxy_gestori, (void *) &v, SIZE(Volo), MSG_TYPE_PARTENZE, 0); 

            if(ret<0){
                perror("GESTORE PARTENZE Errore ricezione\n"); 
                    exit(1);
            }
        
        printf("\n\n****** PARTENZE ******\n\n");
        stampa_volo_info(&v);
    }
    exit(0);
}

