//TASK APERIODICO che chiede al DS di inviargli solo i dati il WCET dei task principali
#include <time.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <fcntl.h>
#include <string.h>

#include "parameters.h"


int main(){

    char mess[]="InvioWCET";

    char risp[MAX_MSG_SIZE*20];

	//Creo la coda delle richieste, impostandola come bloccante
	mqd_t idCodaRequest = mq_open(DS_QUEUE_REQUEST, O_WRONLY);

	//Controllo corretta apertura della coda
	if(idCodaRequest==-1){
		perror("DS: Impossibile aprire la coda delle richieste\n"); 
			exit(1);
	}

    //Apro la coda delle Risposte
    mqd_t idCodaResponse = mq_open(DS_QUEUE_RESPONSE, O_RDONLY);

    if(idCodaResponse==-1){
        perror("DIAG: Impossibile aprire la coda delle risposte\n"); 
            exit(1);
    }

    //Faccio una send al DS
    if(mq_send(idCodaRequest, mess, strlen(mess)+1, 1)==-1){
        perror("DIAG: Errore invio richiesta\n");
        exit(1);
    }
    
    else{
        printf("Messaggio inviato\n");
    }


    if(mq_receive(idCodaResponse, risp, sizeof(risp), NULL)==-1){
        perror("DIAG:Errore ricezione responso\n"); 
            exit(1);
    }

    else{
        printf("Responso Ricevuto:\n%s", risp);
    }


    //CHIUSURA DELLE CODE

    if(mq_close(idCodaRequest)==-1){
        perror("DIAG: Errore chiusura della code Richieste\n"); 
            exit(1);
    }

    if(mq_close(idCodaResponse)==-1){
        perror("DIAG: Errore chiusura della coda del responso\n");
            exit(1);
    }


}