#include "auth.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    pid_t pid;
    int token;
} autenticazione;


void Auth(int id_coda_auth_req, int id_coda_auth_resp) {

    RichiestaAuth msg_auth_req;
    RispostaAuth msg_auth_resp;

    int ret;

    autenticazione vettore_autenticazioni[10];
    int totale_autenticazioni = 0;


    for(int i=0; i<15; i++) {

        printf("Auth: in attesa di richieste\n");

        /* TBD: ricezione richieste */

        //L'autenticatore, si mette in attesa sulla coda, per la ricezione delle richieste che gli vengono inviate
        //Devo ricevere tutti i tipi di messaggi che ci sono sulla coda, andando poi a discriminare le azioni da compirere
        //in base al messaggio che ho ricevuto
        ret = msgrcv(id_coda_auth_req, (void *) &msg_auth_req, SIZE(RichiestaAuth), 0, 0);

            if(ret<0){
                perror("Errore di ricezione autenticatore\n"); 
                    exit(1);
            }


        //Discimino le azioni da compiere in base al tipo del messaggio che ho ricevuto!
        if(msg_auth_req.type==TOKEN_AUTH_REQ_TYPE){
            
            //Messaggio di richiesta di memorizzazione

            int token = rand() % 10000;

            pid_t PIDclient = msg_auth_req.PIDclient;

            vettore_autenticazioni[totale_autenticazioni].token = token;
            vettore_autenticazioni[totale_autenticazioni].pid = PIDclient;
            totale_autenticazioni++;

            printf("Auth: salvataggio token %d per processo %d\n", token, PIDclient);


            printf("Auth: invio token\n");

            /* TBD: Invio messaggio con token */

            //Invio il messaggio che contiene il token, al client
            
            //Imposto il tipo del messaggio,  che è uguale al pid del richiedente
            msg_auth_resp.type=PIDclient;

            msg_auth_resp.esito=1;

            msg_auth_resp.token=token;

            //Invio del messaggio sulla coda apposita

            ret = msgsnd(id_coda_auth_resp, (void *) &msg_auth_resp, SIZE(RispostaAuth), 0);

        }
        else if(msg_auth_req.type==CONFERMA_AUTH_REQ_TYPE) {

            // Ricerca token nel vettore autenticazioni
            int trovato = -1;

            pid_t PIDclient = msg_auth_req.PIDclient;
            int token = msg_auth_req.token;

            pid_t PIDserver = msg_auth_req.PIDserver; 

            printf("Richiesta dal server %d\n", PIDserver);


            for(int k=0; k<totale_autenticazioni; k++) {

                if(vettore_autenticazioni[k].pid == PIDclient &&
                    vettore_autenticazioni[k].token == token) {

                    printf("Auth: token di autenticazione di %d trovato\n", PIDclient);
                    trovato = k;
                    break;
                }
            }


            printf("Auth: invio messaggio di conferma autenticazione\n");

            if(trovato != -1) {

                /* TBD: Invio messaggio di autenticazione riuscita */

                //Il messaggio di risposta deve essere mandato al server

                //il tipo del messaggio di risposta è il pid del server richiedente
                msg_auth_resp.type=PIDserver; 

                msg_auth_resp.esito=1;

                //Invio dunque il messaggio
                ret = msgsnd(id_coda_auth_resp, (void *) &msg_auth_resp, SIZE(RispostaAuth), 0); 

                    if(ret<0){
                        perror("Erorre invio messaggio responso autenticazione\n"); 
                            exit(1);
                    }


            }
            else {

                /* TBD: Invio messaggio di autenticazione fallita */
                msg_auth_resp.type=msg_auth_req.PIDserver;

                msg_auth_resp.esito=0; 

                //Invio messaggi di autenticazione non riuscita
                ret = msgsnd(id_coda_auth_resp, (void *) &msg_auth_resp, SIZE(RispostaAuth), 0);

                    if(ret<0){
                        perror("Errore invio resposno autenticazione\n"); 
                            exit(1);
                    }

            }



        }
        else {
            printf("Auth: ricevuto messaggio di tipo errato\n");
        }
    }
}