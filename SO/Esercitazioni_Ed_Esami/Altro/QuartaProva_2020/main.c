#include "header.h"

/*Funzione che, per 10 volte,incrementa di uno la posizione molo, ovvero la posizione della nave, e tramite scrivi_molo effettua la modifica poi attende 3 secondi*/
void *gestoreMolo(void *p)
{
	struct monitor *m = (struct monitor *)p;
	int i, s;
	s = m->molo;
	for (i = 0; i < 10; i++)
	{
		s = s + 1;
		scrivi_molo(m, s);
		printf("[C: Posizione della nave %d modificata. La nuova posizione è: %d]\n", m->id_nave, s);
		sleep(3);
	}
	pthread_exit(NULL);
}

//Funzione che controlla la posizione di un nave per tre volte
void *Viaggiatori(void *p)
{
	struct monitor *m = (struct monitor *)p;
	int i;
	int ris;
	for (i = 0; i < 3; i++)
	{
		sleep(rand() % 6 + 1);
		ris = leggi_molo(m);
		printf("[V]~La nave #%d è nel molo %d\n", m->id_nave, ris);
	}
	pthread_exit(NULL);
}

int main()
{
	int status, rc;

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	srand(time(NULL) * getpid());

	struct monitor *m[5]; //l'array di monitor per gestire 5 navi

	pthread_t gestore_molo[5]; //5 gestori molo
	pthread_t viagg[10];	   //10 viaggiatori

	/* TBD: Allocare 5 istanze di monitor, e attivarle con inizializza() */
	for (int i = 0; i < 5; ++i)
	{
		m[i] = malloc(sizeof(struct monitor));
		inizializza(m[i]);
	}

	//assegno un id ad ogni nave
	m[0]->id_nave = 1;
	m[1]->id_nave = 2;
	m[2]->id_nave = 3;
	m[3]->id_nave = 4;
	m[4]->id_nave = 5;

	/* TBD: Avviare 5 thread, facendogli eseguire la funzione gestoreMolo(),
     *     e passando ad ognuno una istanza di monitor diversa m[i]
     */
	for (size_t i = 0; i < 5; i++)
	{
		rc = pthread_create(&gestore_molo[i], &attr, gestoreMolo, (void *)m[i]);
		if (rc != 0)
		{
			printf("Pthread create %d - Quit\n", rc);
			exit(0);
		}
	}
	/* TBD: Avviare 10 thread, facendogli eseguire la funzione Viaggiatori(),
     *      e passando ad ognuno una istanza di monitor diversa, da scegliere
     *      a caso con "rand() % 5"
     */
	int pos;
	for (size_t i = 0; i < 10; i++)
	{
		pos = rand() % 5;
		rc = pthread_create(&viagg[i], &attr, Viaggiatori, (void *)m[pos]);
		if (rc != 0)
		{
			printf("Pthread create failed %d - Quit\n", rc);
			exit(0);
		}
	}

	/* TBD: Effettuare la join con i thread "gestoreMolo" */
	for (size_t i = 0; i < 5; i++)
	{
		pthread_join(gestore_molo[i], (void **)&status);
		if (status != 0)
			perror("ERROR ON TERMINATING THREAD");
		else
			printf("Thread #%ld terminated with status %d\n", gestore_molo[i], status);
	}

	/* TBD: Effettuare la join con i thread "Viaggiatori" */
	for (size_t i = 0; i < 10; i++)
	{
		pthread_join(viagg[i], (void **)&status);
		if (status != 0)
			perror("ERROR ON TERMINATING THREAD");
		else
			printf("Thread #%ld terminated with status %d\n", viagg[i], status);
	}

	/* TBD: Disattivazione delle 5 istanze di monitor con rimuovi() */
	/* TBD: Deallocazione delle 5 istanze di monitor con free() */

	for (size_t i = 0; i < 5; i++)
	{
		rimuovi(m[i]);
		free(m[i]);
	}
	pthread_exit(0);
}