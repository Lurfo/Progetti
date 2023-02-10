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

// inizializzazione code di servizio
void initServiceQueues(){
    
    coda_RTS = msgget(IPC_PRIVATE,IPC_CREAT|0664);
    printf("Coda di servizio coda_RTS create con desc: %d\n", coda_RTS);
    
    coda_OTS = msgget(IPC_PRIVATE,IPC_CREAT|0664);
    printf("Coda di servizio coda_OTS create con desc: %d\n", coda_OTS);
}

// rimozione code di servizio
void removeServiceQueues(){
    msgctl(coda_RTS,IPC_RMID,0);
    msgctl(coda_OTS,IPC_RMID,0);
}


void controllore(int ds_queue_control_proxy){
    
    int i, ret;
    char citta_partenza[][20] = { "Napoli", "Roma", "Milano", "Torino", "Firenze"};
    char citta_destinazione[][20] = { "New York", "Madrid", "Londra", "Berlino", "Parigi"};
    
    Volo v_partenza;
    Volo v_arrivo;
    
    for (i=0; i<10; i++){
        
        //HANDSHAKE
        Control m1,m2;
        // costruzione messaggio RTS
        m1.tipo = REQUEST_TO_SEND;
        strcpy(m1.mess,"Richiesta di invio");
        // invio messaggio RTS
        ret = msgsnd(coda_RTS, &m1, sizeof(Control) - sizeof(long), 0);
        if (ret<0){
            perror("Errore send RTS");
            exit(-1);
        }
        //printf("Messaggio TIPO: %lu MSG: '%s' inviato su coda di servizio %d\n", m1.tipo, m1.mess, coda_RTS);
        // ricezione OTS
        ret = msgrcv(coda_OTS, &m2, sizeof(Control) - sizeof(long), OK_TO_SEND, 0);
        if (ret<0){
            perror("Errore rcv OTS");
            exit(-1);
        }
        //printf("Messaggio TIPO: %lu MSG: '%s' ricevuto su coda di servizio %d\n", m2.tipo, m2.mess, coda_OTS);
        
        //invia arrivi
        if (i%2 == 0){
            
            
            v_arrivo.tipo = MSG_TYPE_CONTROL_PROXY;
            v_arrivo.ID = rand() % 100 + 1;
            strcpy(v_arrivo.direzione, "arrivo");
            
            strcpy(v_arrivo.citta_partenza, citta_partenza[rand() % 5]);
            strcpy(v_arrivo.citta_arrivo, citta_destinazione[rand() % 5]);
            
            // invio messaggio
            ret = msgsnd(ds_queue_control_proxy, &v_arrivo, sizeof(Volo) - sizeof(long), 0);
            if (ret<0){
                perror("msgsnd v_arrivo on ds_queue_control_proxy FALLITA!");
                exit(-1);
            }
            printf("[controllore] Messaggio #%d v_arrivo (ID: %d) INVIATO!\n", i, v_arrivo.ID);
            
        }else { //invia partenze
            
            
            v_partenza.tipo = MSG_TYPE_CONTROL_PROXY;
            v_partenza.ID = rand() % 100 + 1;
            strcpy(v_partenza.direzione, "partenza");
            
            strcpy(v_partenza.citta_partenza, citta_partenza[rand() % 5]);
            strcpy(v_partenza.citta_arrivo, citta_destinazione[rand() % 5]);
            
            ret = msgsnd(ds_queue_control_proxy, &v_partenza, sizeof(Volo) - sizeof(long), 0);
            if (ret<0){
                perror("msgsnd v_partenza on ds_queue_control_proxy FALLITA!");
                exit(-1);
            }
            printf("[controllore] Messaggio #%d v_partenza (ID: %d) INVIATO!\n", i, v_partenza.ID);
        }
        
    }
    exit(0);
    
}
void proxy(int ds_queue_control_proxy, int ds_queue_proxy_gestori){
    
    int i, ret;
    Volo v;
    for (i=0; i<10; i++){
        //RECEIVE BLOCCANTE
        //HANDSHAKE
        Control m1,m2;    // ricezione messaggio RTS
        ret = msgrcv(coda_RTS, &m1, sizeof(Control) - sizeof(long), REQUEST_TO_SEND, 0);    // costruzione messaggio OTS
        if (ret<0){
            perror("Errore rcv RTS");
            exit(-1);
        }
        //printf("Messaggio TIPO: %lu MSG: '%s' ricevuto su coda di servizio %d\n", m1.tipo, m1.mess, coda_RTS);

        m2.tipo = OK_TO_SEND;
        strcpy(m2.mess, "Ready to send");
        
        // invio messaggio OTS
        ret = msgsnd(coda_OTS, &m2, sizeof(Control) - sizeof(long), 0);
        if (ret<0){
            perror("Errore send OTS");
            exit(-1);
        }
        //printf("Messaggio TIPO: %lu MSG: '%s' inviato su coda di servizio %d\n", m2.tipo, m2.mess, coda_OTS);

        
        // ricezione messaggio vero e proprio
        ret = msgrcv(ds_queue_control_proxy, &v, sizeof(Volo) - sizeof(long), MSG_TYPE_CONTROL_PROXY, 0);
        if (ret<0){
            perror("Errore rcv dal proxy");
            exit(-1);
        }
        printf("[proxy] Messaggio VOLO #%d ricevuto con direzione =  '%s'\n", i, v.direzione);
        
        if (strcmp(v.direzione, "arrivo") == 0){
            // send to gestore arrivi
            v.tipo = MSG_TYPE_ARRIVI;
        }else {
            v.tipo = MSG_TYPE_PARTENZE;
        }
        
        sleep(1);
        ret = msgsnd(ds_queue_proxy_gestori, &v, sizeof(Volo) - sizeof(long), 0);
        if (ret<0){
            perror("Errore send verso i gestori");
            exit(-1);
        }
        
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
        ret = msgrcv(ds_queue_proxy_gestori, &v, sizeof(Volo) - sizeof(long), MSG_TYPE_ARRIVI, 0);
        if (ret<0){
            perror("[gestore_arrivi] Errore rcv!");
            exit(-1);
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
        ret = msgrcv(ds_queue_proxy_gestori, &v, sizeof(Volo) - sizeof(long), MSG_TYPE_PARTENZE, 0);
        if (ret<0){
            perror("[gestore_partenze] Errore rcv!");
            exit(-1);
        }
        
        printf("\n\n****** PARTENZE ******\n\n");
        stampa_volo_info(&v);
    }
    exit(0);
}

