#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "auth.h"

void Server(int id_coda_elab_req, int id_coda_elab_resp, int id_coda_auth_req, int id_coda_auth_resp) {

    RichiestaAuth msg_auth_req;
    RispostaAuth msg_auth_resp;
    RichiestaElab msg_elab_req;
    RispostaElab msg_elab_resp;

    int ret;

    int risorsa = 0;


    

    for(int i=0; i<10; i++) {

        printf("Server: in attesa di richieste\n");

        /* TBD: Ricezione messaggi di richiesta elaborazione */

        //Il servente, non fa altro che fare una recieve bloccante sulla coda dove si vanno ad accumulare el richieste di
        //elaborazione 
        //Il server, riceve ogni tipo di messaggio che ha come tipo ELAB_REQ_TYPE  
        ret = msgrcv(id_coda_elab_req, (void *) &msg_elab_req, SIZE(RichiestaElab), ELAB_REQ_TYPE, 0);

            //Effettuo il controllo della riuscita dell'operazione
            if(ret<0){
                perror("Errore ricezione ELAB_REQ_TYPE\n"); 
                    exit(1);
            }

        //Prelevo dal messaggio tutte le informazioni che mi interessano

        //Il valore con cui modificare la risorsa
        int valore = msg_elab_req.valore;

        //Li uso per l'autenticazione
        int PIDclient = msg_elab_req.PID;
        int token = msg_elab_req.token;

        printf("Server: ricevuta richiesta %d da %d (token=%d)\n", valore, PIDclient, token);


        printf("Server: invio conferma autenticazione\n");

        /* TBD: Invio messaggio di richiesta conferma autenticazione */

        //Prima di sovrascrivere, devo ottenere la conferma di autenticazione, inviando la richiesta 

        //Imposto i parametri del messaggi di richiesta appositi

        //Parametri che l'autenticatore deve analizzare
        
        //Modifico il tipo del messaggi di richiesta elaborazione 
        msg_auth_req.type=CONFERMA_AUTH_REQ_TYPE;
        msg_auth_req.PIDclient=PIDclient; 
        msg_auth_req.token=token;

        //Pid del server che richiede la verifica
        msg_auth_req.PIDserver=getpid();

        //Send del messaggio
        ret = msgsnd(id_coda_auth_req, (void *) &msg_auth_req, SIZE(RichiestaAuth), 0);

            if(ret<0){
                perror("Errore invio TOKEN_AUTH_REQ_TYPE\n"); 
                    exit(1);
            }


        printf("Server: in attesa di conferma\n");

        /* TBD: Ricezione messaggio di risposta conferma autenticazione */

        //Il server, fa una recieve bloccante sulla coda che deve riportare la risposta alla richiesta di autenticazione 
        ret = msgrcv(id_coda_auth_resp, (void *) &msg_auth_resp, SIZE(RispostaAuth), getpid(), 0); 

            printf("Server: Ottenuto riscontro dall'autenticatore\n");

            //Controllo esito della recieve
            if(ret<0){
                perror("Errore ricezione CONFERMA_AUTH_REQ_TYPE\n"); 
                    exit(1);
            }


        int esito;

        //Controllo della risposta di autenticazione


        if(msg_auth_resp.esito==1) {

            printf("Server: autenticazione del client %d riuscita\n", PIDclient);

            risorsa = valore;

            printf("Server: nuovo valore risorsa = %d\n", risorsa);

            esito = 1;
        }
        else {

            printf("Server: autenticazione del client %d fallita\n", PIDclient);
 
            esito = 0;
        }

        printf("Server: invio risposta al client\n");

        /* TBD: Invio messaggio di risposta elaborazione, con esito positivo o negativo */

        //Imposto i valori  del messaggio del responso

        //Il tipo del messaggio sarà, in questo caso, il tipo del messaggio di responso è uguale al processo che ha richiesto
        //la modifica
        msg_elab_resp.type=PIDclient;

        msg_elab_resp.esito=esito;

        //Procedo ad inviare il messaggio sulla coda 
        ret = msgsnd(id_coda_elab_resp, (void *) &msg_elab_resp, SIZE(RispostaElab), 0); 

            printf("Risposta al client %d, inviata\n", PIDclient);

            if(ret<0){
                perror("Errore invio RESPONSO ELABORAZIONE\n"); 
                    exit(1);
            }

    }

}