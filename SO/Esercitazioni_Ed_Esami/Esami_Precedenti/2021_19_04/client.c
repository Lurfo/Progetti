#include "auth.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>


void ClientAuth(int id_coda_auth_req, int id_coda_auth_resp, int id_coda_elab_req, int id_coda_elab_resp) {

    RichiestaAuth msg_auth_req;
    RispostaAuth msg_auth_resp;
    RichiestaElab msg_elab_req;
    RispostaElab msg_elab_resp;

    int ret;

    //Imposto il tipo del messaggio di autenticazione
    msg_auth_req.type=TOKEN_AUTH_REQ_TYPE;

    msg_elab_req.type=ELAB_REQ_TYPE;


    srand(time(NULL)*getpid());

    for(int i=0; i<5; i++) {


        printf("Client Auth (%d): invio richiesta auth\n", getpid());

        /* TBD: Invio messaggio richiesta nuovo token */
        //Imposto il messaggio di richiesta
        msg_auth_req.PIDclient=getpid();

        //Invio il messaggio all'autenticatore 
        ret=msgsnd(id_coda_auth_req, (void *) &msg_auth_req, SIZE(RichiestaAuth), 0);

            printf("Client auth %d: richiesta inviata\n", getpid());

            if(ret<0){
                perror("Errore invio TOKEN_AUTH_REQUEST\n"); 
                    exit(1);
            }


        printf("Client Auth (%d): attesa risposta auth\n", getpid());

        /* TBD: Ricezione messaggio con token */

        //Effettuo una recieve bloccante sulla coda delle risposte date dall'autenticatore
        ret = msgrcv(id_coda_auth_resp, (void *) &msg_auth_resp, SIZE(RispostaAuth), getpid(), 0);

            printf("Client auth %d: ottenuta risposta auth\n", getpid());

            if(ret<0){
                perror("Errore ricezione del messaggio di risposta autenticazione\n");
            }

        //Prelevo il token dal messaggio di risposta
        int token = msg_auth_resp.token;

        printf("Client Auth (%d): ricevuto token %d\n", getpid(), token);


        int valore = rand() % 11;

        printf("Client Auth (%d): invio richiesta elaborazione %d\n", getpid(), valore);

        /* TBD: Invio richiesta elaborazione */

        //Imposto il messaggio per la richiesta dell'elaborazione 

        //Imposto il pid del processo che effettua la richiesta
        msg_elab_req.PID=getpid();

        //Imposto il token
        msg_elab_req.token=token; 

        msg_elab_req.valore=valore; 

        //Invio il messaggio di richiesta di elaborazione
        ret = msgsnd(id_coda_elab_req, (void *) &msg_elab_req, SIZE(RichiestaElab), 0);

            printf("Client auth %d: messaggio di richiesta elaborazione inviato\n", getpid());

            if(ret<0){
                perror("Errore invio ELAB_REQ_TYPE\n"); 
                    exit(1);
            }

        printf("Client Auth (%d): attesa risposta elaborazione\n", getpid());

        /* TBD: Ricezione risposta elaborazione */

        //Mi metto in attesa sulla coda
        ret = msgrcv(id_coda_elab_resp, (void *) &msg_elab_resp, SIZE(RispostaElab), getpid(), 0);

            printf("Client auth %d: ottenuta risposta elaborazione\n", getpid());

            if(ret<0){
                perror("Errore ricezione del messaggio di conferma esito token\n"); 
                    exit(1);
            }


        //Controllo esito della richiesta
        if(msg_elab_resp.esito==1) {

            printf("Client Auth (%d): ricevuta risposta positiva\n", getpid());
        }
        else {
            printf("Client Auth (%d): ricevuta risposta negativa\n", getpid());
        }

    }
}

void ClientNonAuth(int id_coda_elab_req, int id_coda_elab_resp) {

    RichiestaElab msg_elab_req;
    RispostaElab msg_elab_resp;

    int ret;

    msg_elab_req.type=ELAB_REQ_TYPE;

    srand(time(NULL)*getpid());

    for(int i=0; i<5; i++) {

        int token = rand() % 10000; /* Token casuale non valido */
        int valore = rand() % 11;

        printf("Client Non-Auth (%d): invio richiesta elaborazione %d\n", getpid(), valore);

        /* TBD: Invio richiesta elaborazione */
        
        //Imposto i valori del messaggi di richiesta 
        msg_elab_req.PID=getpid(); 
        msg_elab_req.token=token;
        msg_elab_req.valore=valore;

        //Invio messaggio 
        ret=msgsnd(id_coda_elab_req, (void *) &msg_elab_req, SIZE(RichiestaElab), 0); 

            if(ret<0){
                perror("Errore finta richiesta elaborazione\n"); 
                    exit(1);
            }



        printf("Client Non-Auth (%d): attesa risposta elaborazione\n", getpid());

        /* TBD: Ricezione risposta elaborazione */

        ret = msgrcv(id_coda_elab_resp, (void *) &msg_elab_resp, SIZE(RispostaElab), getpid(), 0); 

            if(ret<0){
                perror("Errore ricezione del messaggio di risposta dal server\n"); 
                    exit(1);
            }

        //Controllo dell'esito della richiesta al server
        if(msg_elab_resp.esito==1) {

            printf("Client Non-Auth (%d): ricevuta risposta positiva\n", getpid());
        }
        else {
            printf("Client Non-Auth (%d): ricevuta risposta negativa\n", getpid());
        }

    }
}