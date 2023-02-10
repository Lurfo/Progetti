/*
 * Client 
 * un esempio di interprocess commnuication 
 * tramite messaggi POSIX
 */

//Come il server, il client ha i medesimi parametri

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define SERVER_QUEUE_NAME   "/sp-example-one-server"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256

int main (int argc, char **argv)
{
    char client_queue_name [64];
    mqd_t qd_server, qd_client;   // Descrittore delle code

    //Il client apre però una propria coda, sulla quale riceve le risposte dal server!
    //il nome, contiene anche il suo pid, così sono sicuro di avere ognuno una cosa "privata"
    sprintf (client_queue_name, "/sp-example-one-client-%d", getpid ());

    //Il client scrive al server il nome della sua coda, così questo sa dove rispondere!

    // Vanno definiti gli attributi che andremo ad assegnare alla coda
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MESSAGES;
    attr.mq_msgsize = MAX_MSG_SIZE;
    attr.mq_curmsgs = 0;

    // Apriamo una coda in sola lettura (O_RDONLY) e se non esiste la creiamo (O_CREAT). La coda serve a ricevere le risposte del server
    if ((qd_client = mq_open (client_queue_name, O_RDONLY | O_CREAT, QUEUE_PERMISSIONS, &attr)) == -1) {
        perror ("Client: mq_open (client)");
        exit (1);
    }
   
   // Apriamo una coda in sola scrittura (O_WRONLY), la coda dovrebbe essere già stata creata dal server. La coda serve ad inviare messaggi al server.
   //La coda del server viene aperta in sola scrittura
   //Se la coda non esiste, questa non viene creata: Ho un vincolo nell'esecuzione dei processi, deve eseguire necessariamente
   //dopo l'avvio del server, difatti non vado ad inserire nemmeno i processi, perchè la coda già esiste!
    if ((qd_server = mq_open (SERVER_QUEUE_NAME, O_WRONLY)) == -1) {
        perror ("Client: mq_open (server)");
        exit (1);
    }
    //Sicuramente ho i permessi di accesso alla coda, in base a quelli che sono stati usati nel server!

    //Il client ha il buffer di ingresso!
    char in_buffer [MAX_MSG_SIZE];

    printf ("Ask for a token (Press <ENTER>) [q to exit]: ");

    //Aspetto di ricevere un input da tastiera, e viene ripetuto il cilo fino a che non riceve q
    while (getchar()!='q') {
 
        // Invio un messaggio al server contente il nome della coda sulla quale rispondere
        //In questo modo posso ricevere le risposte!
        if (mq_send (qd_server, client_queue_name, strlen (client_queue_name) + 1, 0) == -1) {
            perror ("Client: Not able to send message to server");
            continue;
        }

        // Ricevo la risposta del server
        if (mq_receive (qd_client, in_buffer, MAX_MSG_SIZE, NULL) == -1) {
            perror ("Client: mq_receive");
            exit (1);
        }
        // Mostro il token ricevuto dal server
        printf ("Client: Token received from server: %s\n\n", in_buffer);
        
        printf ("Ask for a token (Press <ENTER>) [q to exit]: ");
    }
    
    // Invio un messaggio di terminazione al server
    if (mq_send (qd_server, "q", sizeof(char) + 1, 0) == -1) {
	perror ("Client: Not able to send message to server");
    }

    /* Clear */
    //Quando ricevo il messaggio di q, vado a rimuovere tutte le code ed eseguo unlink SOLO della sua coda privata!
    if (mq_close (qd_server) == -1) {
        perror ("Client: mq_close qd_server");
        exit (1);
    }

    if (mq_close (qd_client) == -1) {
        perror ("Client: mq_close qd_client");
        exit (1);
    }

    if (mq_unlink (client_queue_name) == -1) {
        perror ("Client: mq_unlink client queue");
        exit (1);
    }
    printf ("Client: bye\n");

    exit (0);
}
