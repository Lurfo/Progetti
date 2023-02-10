#include "header.h"

/* Funzione che, per 10 volte,incrementa di uno la posizione molo, ovvero la posizione della nave, e tramite scrivi_molo effettua la modifica poi attende 3 secondi*/
void * gestoreMolo (void * p){
	
    // TODO: ottenere il riferimento alla struttura monitor da *p
	//Per ottenere il riferimento alla struttura, devo fare un casting inverso
	struct monitor* m = (struct monitor *) p;
    
	int i,s;
	s=m->molo;
	for(i=0; i<10; i++){
        
		s=s+1;
		scrivi_molo(m,s);
		printf("[C: Posizione della nave %d modificata. La nuova posizione è: %d]\n",m->id_nave,s);
		sleep(3);
        
	}
	pthread_exit(NULL);
}

// Funzione che controlla la posizione di un nave per tre volte
void * Viaggiatori (void * p){
	
    // TODO: ottenere il riferimento alla struttura monitor da *p
	//Anche qui, effettuo un casting inverso
	struct monitor *m = (struct monitor *) p;
    
	int i;
	int ris;
	for(i=0;i<3;i++){
        
		sleep(rand()%6+1);
		ris=leggi_molo(m);
		printf("[V]~La nave n.ro %d è nel molo %d\n", m->id_nave, ris);
        
	}
	pthread_exit(NULL);
}

int main() {
	
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	
	srand(time(NULL));

	struct monitor* m[5];//l'array di monitor per gestire 5 navi

	pthread_t gestore_molo[5];//5 gestori molo
	pthread_t viagg[10];//10 viaggiatori	
	
	int i;

    /* TODO: Allocare 5 istanze di monitor, e attivarle con inizializza() */
	//Utilizzo un for, per andare ad allocare le istanze che mi occorrono
	for(i=0; i<5; i++){

		//Ottento il riferimento alla struttura
		m[i] = (struct monitor*) malloc(sizeof(struct monitor));

		//Utilizzo la funzione di inizializzazione per attivarla
		inizializza(m[i]);
	}

	// TODO: assegnare un id ad ogni nave
	//Tramite un ciclo, assegno un id ad ogni nave!
	for(i=0; i<5; i++){
	
		m[i]->id_nave= i+1;

	}

	
    /* TODO: Avviare 5 thread, facendogli eseguire la funzione gestoreMolo(),
     *     e passando ad ognuno una istanza di monitor diversa m[i]
     */

	for(i=0; i<5; i++){

		if(pthread_create(&gestore_molo[i], &attr, gestoreMolo, (void *) m[i])){
			perror("Errore nella creazione del thread gestore\n"); 
				exit(1);
		}


	}
    
    
    /* TODO: Avviare 10 thread, facendogli eseguire la funzione Viaggiatori(),
     *      e passando ad ognuno una istanza di monitor diversa, da scegliere
     *      a caso con "rand() % 5"
     */
	for(i=0; i<10; i++){

		if(pthread_create(&viagg[i], &attr, Viaggiatori, (void *) m[rand()%5])){
			perror("Errore nella creazione del thread viaggiatore\n"); 
				exit(1);
		}

	}
	
    
    
    /* TODO: Effettuare la join con i thread "gestoreMolo" */

	for(int k=0; k<5; k++){

		if(pthread_join(gestore_molo[k], NULL)){
			printf("Errore join del thread gestore %d\n", k);
				exit(1);
		}

		printf("Il thread gestore %d, è terminato\n", k);

	}
    
    /* TODO: Effettuare la join con i thread "Viaggiatori" */
	for(int j=0; j<10; j++){

		if(pthread_join(viagg[j], NULL)){
			printf("Errore join del thread viaggiatore\n"); 
				exit(1);
		}
			
		printf("Il thread viaggiatore %d è terminato\n", j);

	}
    
    /* TODO: Disattivazione delle 5 istanze di monitor con rimuovi() */
	for(i=0; i<5; i++){
		rimuovi(m[i]);
	}
    
    /* TODO: Deallocazione delle 5 istanze di monitor con free() */
	for(i=0; i<5; i++){
		free(m[i]);
	}

	//Rimozione dell'attributo
	pthread_attr_destroy(&attr);
	
    
	return 0;
}	
