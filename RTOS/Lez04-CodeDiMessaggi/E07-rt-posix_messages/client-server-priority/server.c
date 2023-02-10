/*
 * Server 
 * un esempio di interprocess commnuication 
 * tramite messaggi POSIX
 */

//In questo programma, il server si blocca su un input dell'utente, in modo che può leggere i messaggi bufferizzati e rispettare la
//priorità dei messaggi (altrimenti non vado a rispettare la priorità perchè soddisfo le richieste che arrivano prima)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>

#define SERVER_QUEUE_NAME   "/sp-example-two-server"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 10
#define MAX_MSG_SIZE 256


int main (int argc, char **argv)
{
	mqd_t qd_server, qd_client;  	// descrittori delle code
	long token_number = 1; 	   	// Token passato ad ogni richiesta del CLient

	char temp_buf [10];
	char in_buffer [MAX_MSG_SIZE];
	char out_buffer [MAX_MSG_SIZE];
	
	printf ("Server alive!\n");

	// Vanno definiti gli attributi che andremo ad assegnare alla coda
	//Sono necessari alla costruzione della coda
	struct mq_attr attr;

	attr.mq_flags = 0;				
	attr.mq_maxmsg = MAX_MESSAGES;	
	attr.mq_msgsize = MAX_MSG_SIZE; 
	attr.mq_curmsgs = 0;

	// Apriamo una coda in sola lettura (O_RDONLY) e se non esiste la creiamo (O_CREAT). Inoltre la coda sarà non bloccante (O_NONBLOCK)
	// Il nome dato alla coda è una stringa: "/sp-example-server". Può essere una qualsiasi stringa l'importante è che essa inizi per "/"
	
	//Il NONBLOCK, è differente rispetto alla precedente, quando faccio la receive, non mi blocco nell'attesa di un messaggio
	//(nei sistemi RT è importante che non ci siano code bloccanti, altrimenti potrei avere un bloccaggio indefinito)
	if ((qd_server = mq_open (SERVER_QUEUE_NAME, O_RDONLY | O_CREAT | O_NONBLOCK, QUEUE_PERMISSIONS, &attr)) == -1) {
		perror ("Server: mq_open (server)");
		exit (1);
	}
	

	while (1) {
	
		// Ricevo, se esiste, il messaggio più vecchio in coda con priorità più alta. Altrimenti attendo un input da tastiera.
		//NOTA: L'ultimo parametro della receive, indica la priorità, ma nella receive ha un significato differente, posso inserire
		//un puntatore che riceve la priorità del messaggio ricevuto, posso quindi sapere quale priorità ha il messaggio ricevuto 
		if (mq_receive(qd_server, in_buffer,MAX_MSG_SIZE,NULL) == -1){
			printf ("Press <ENTER> to receive buffered messages: ");

	    		//Aspetto di ricevere un input da tastiera per ricevere i messaggi
				//La funzione fgets è quella che attende proprio un input dall'utente, che va ad inserire 2 caratteri nel temp_buf
			while (fgets (temp_buf, 2, stdin)){
				break;
			}
			
		}

		//Se ci sono elementi nella coda, allora viene eseguito questo ramo
		else{
			printf ("Server: message received.\n");

			// Verifico la richiesta di chiusura del server
			if(strncmp(in_buffer,"q", sizeof(in_buffer)) == 0){
				break;
			}

			else{
				// Rispondo al Client usando una diversa coda. Il nome della coda del client la ricavo dal messaggio inviato dal client stesso
				if ((qd_client = mq_open (in_buffer, O_WRONLY)) == -1) {
					perror ("Server: Not able to open client queue");
					continue;
				}

				//Uso questa funzione priorio come specificato nell'esempio precedente
				sprintf (out_buffer, "%ld", token_number);
				// Invio il token al client	
				//Aggiunto 1 alla lunghezza del buffer in quando devo contare il carattere terminatore
				if (mq_send (qd_client, out_buffer, strlen (out_buffer) + 1, 0) == -1) {
					perror ("Server: Not able to send message to client");
					continue;
				}

				printf ("Server: response sent to client.\n");
				token_number++;
			}
		}
	
	}

	/* Clear */
	//Questa elimina il descrittore all'interno del processo, non vado a distruggere la coda, ma il mio descrittore
	//il processo che la esegue, non può più usare la coda
	//(la coda sa quanti descrittori ad essa collegati ci sono)
	if (mq_close (qd_server) == -1) {
		perror ("Server: mq_close qd_server");
		exit (1);
	}


	//Questa va ad impostare la coda nello stato detached, quando non ci sono più elementi ad essa collegati, la coda
	//viene eliminata!
	//Se non viene eseguita, quando riavvio il programma potrei avere un comportamento anomalo, in quanto potrei avere risultati che erano
	//già presenti precedentemente nella coda
	if (mq_unlink (SERVER_QUEUE_NAME) == -1) {
		perror ("Server: mq_unlink server queue");
		exit (1);
	}

	printf("Server: bye!\n");
}
