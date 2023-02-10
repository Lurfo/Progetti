/*
 * Server 
 * un esempio di interprocess commnuication 
 * tramite messaggi POSIX
 */

#include <stdio.h>
#include <stdlib.h>

//Serve per lavorare con le stringhe
#include <string.h>
#include <sys/types.h>

//File control, che contiene i vari flag da impostare per le code
#include <fcntl.h>

#include <sys/stat.h>
//Libreria per le code RTPOSIX, che richiede -lrt per usarla
#include <mqueue.h>


//Vengono definiti una serie di parametri per le code, tra cui, nome, dimensione della coda, permessi, dimensione dei messaggi ecc...
//Importante per il nome è che sia univoco
#define SERVER_QUEUE_NAME   "/sp-example-one-server"
//I permessi che vengono definiti in questo modo vuol dire che ho una lettura e scrittura sia per
//l'utente che per quelli del gruppo
//Ovviamente uso il 6 perchè considero la rappresentazione binaria del 6 "110", in quanto i primi mi identificano i permessi di lettura e scrittura
#define QUEUE_PERMISSIONS 0660

//La coda rivede messaggi di massimo 256 byte e può contenere massimo 10 messaggi
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256

int main (int argc, char **argv)
{
    //Vado a dichiarare la coda del server
    mqd_t qd_server, qd_client;  	// descrittori delle code
    long token_number = 1; 	   	// Token passato ad ogni richiesta del CLient

    printf ("Server alive!\n");

    // Vanno definiti gli attributi che andremo ad assegnare alla coda
    //La parte dell'atributo è una cosa opzionale, se non lo specifico vengono usati dei valori di default
    struct mq_attr attr;

    attr.mq_flags = 0;				
    attr.mq_maxmsg = MAX_MESSAGES;	
    attr.mq_msgsize = MAX_MSG_SIZE; 
    attr.mq_curmsgs = 0;

    // Apriamo una coda in sola lettura (O_RDONLY) e se non esiste la creiamo (O_CREAT).
    //La coda in sola lettura è così per il server, in quanto deve solo leggere da questa
    //Posso anche fornigli la scrittura, ma non è necessario farlo
    // Il nome dato alla coda è una stringa: "/sp-example-server". Può essere una qualsiasi stringa l'importante è che essa inizi per "/"
    if ((qd_server = mq_open (SERVER_QUEUE_NAME, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {

        //Se eseguo questo corpo dell'if, vuol dire che c'è stato un problema nella creazione della coda!
        perror ("Server: mq_open (server)");
        exit (1);
    }
    //Sulla coda creata, vado ad aspettare i messaggi

    //Nota bene: il read only che ho usato è un meccanismo differente dai permessi, i permessi che vado a considerare, sono
    //riferiti agli altri utenti!
    //Mentre la read only è solo riferita al singolo processo!

    //Dimensione dei messaggi di ingresso e di risposta
    char in_buffer [MAX_MSG_SIZE];
    char out_buffer [MAX_MSG_SIZE];
    char end []="q";

    while (1) {
        // Ricevo il messaggio più vecchio in coda con priorità più alta
        if (mq_receive (qd_server, in_buffer, MAX_MSG_SIZE, NULL) == -1) {
            perror ("Server: mq_receive");
            exit (1);
        }

        printf ("Server: message received\n");

	// Verifico la richiesta di chiusura del server
	if(strncmp(in_buffer,"q", sizeof(in_buffer)) == 0){
		break;
	}
	else{
		// Rispondo al Client usando una diversa coda. Il nome della coda del client la ricavo dal messaggio inviato dal client stesso
		if ((qd_client = mq_open (in_buffer, O_WRONLY)) == 1) {
		    perror ("Server: Not able to open client queue");
		    continue;
		}

        //Scrivo nel messaggio il token, usando la funzione apposita della libreria string
        //viene usata in modo da scrivere il testo formattato come carattere!
        //Questo perchè sulle code, devo sempre mandare soltanto dei caratteri
        //Avviene il meccanismo del MARSHALLING!
		sprintf (out_buffer, "%ld", token_number);
		// Invio il token al client	
		if (mq_send (qd_client, out_buffer, strlen (out_buffer) + 1, 0) == -1) {
		    perror ("Server: Not able to send message to client");
		    continue;
		}

		printf ("Server: response sent to client.\n");
		token_number++;
        }
    }
    
    /* Clear */
    //Quando ricevo q, allora salto a queste istruzioni, che rimuovono la coda!
    if (mq_close (qd_server) == -1) {
        perror ("Server: mq_close qd_server");
        exit (1);
    }

    if (mq_unlink (SERVER_QUEUE_NAME) == -1) {
        perror ("Server: mq_unlink server queue");
        exit (1);
    }
   
    printf("Server: bye!\n");
}
