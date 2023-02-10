#include "header.h"

/*Funzione che, per 10 volte,incrementa di uno la posizione molo, ovvero la posizione della nave, e tramite scrivi_molo effettua la modifica poi attende 3 secondi*/
void * gestoreMolo (void * p){
	struct monitor* m = (struct monitor*) p;
	int i,s;
	s=m->molo;
	for(i=0; i<10; i++){

		//NOTA: Il molo, indica la posizione della nave, che deve essere aggiornata periodicamente, venendo incremenetata!
		//di un unico valore
		s=s+1;
		scrivi_molo(m,s);
		printf("[C: Posizione della nave %d modificata. La nuova posizione è: %d]\n",m->id_nave,s);
		sleep(3);
	}
	pthread_exit(NULL);
}

//Funzione che controlla la posizione di un nave per tre volte
void * Viaggiatori (void * p){
	struct monitor* m = (struct monitor*) p;
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
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);
	
	srand(time(NULL));

	struct monitor* m[5]; //l'array di monitor per gestire 5 navi

	pthread_t gestore_molo[5];//5 gestori molo
	pthread_t viagg[10];//10 viaggiatori	
	
	int i;

    //Con un ciclo for, vado ad allocare in memoria, le 5 istanze di monitor che ho definito
	//per poi andare ad inizializzarle con la funzioni di inizializzazione!
	for(i=0; i<5; i++){
		m[i] = (struct monitor *) malloc(sizeof(struct monitor));

		//Inizializzo la struttura, andando ad usare la funzioni di inizializzazione
		inizializza(m[i]);
	}

	//assegno un id ad ogni nave
	m[0]->id_nave=1;
	m[1]->id_nave=2;
	m[2]->id_nave=3;
	m[3]->id_nave=4;
    m[4]->id_nave=5;


	//Avvio i 5 thread, ad ognuno dei quali assegno la gestione di un differente molo
	for(i=0; i<5; i++){

		if(pthread_create(&gestore_molo[i], &attr, gestoreMolo, (void *) m[i])){
			perror("Errore nella creazione del thread gestore molo!");
				exit(1);
		}

	}
    
	printf("Creo i thread viaggiatori!\n");
    
    /* TBD: Avviare 10 thread, facendogli eseguire la funzione Viaggiatori(),
     *      e passando ad ognuno una istanza di monitor diversa, da scegliere
     *      a caso con "rand() % 5"
     */
	//Come fatto anche i gestori, creo i thread viaggiatori, ognuno tuttavia legge un monitor a caso
	for(i=0; i<10; i++){
		
		if(pthread_create(&viagg[i], &attr, Viaggiatori, (void *) m[rand()%5])){
			perror("Errore nalla creazione di un monitor viaggiatore!\n");
		}

	}
    
    
    /* TBD: Effettuare la join con i thread "gestoreMolo" */
	//Uso un for, per andare ad effettuare il join tra il thread main  e i thread gestori del molo
	for(i=0; i<5; i++){

		pthread_join(gestore_molo[i], NULL);

	}
    
    /* TBD: Effettuare la join con i thread "Viaggiatori" */
	//Come fatto per i gesotiri effettuo lo stesso procedimento anche per i viaggiatori
	for(i=0;i<10; i++){
		
		pthread_join(viagg[i], NULL);

	}
    
    /* TBD: Disattivazione delle 5 istanze di monitor con rimuovi() */
	//Utilizzo la funzione di rimozione definita per andare a rimuovere i valori inizializzati!
	//La funione deve essere applicata a tutti e 5 i monitor
	for(i=0; i<5; i++){
		rimuovi(m[i]);
	}


    /* TBD: Deallocazione delle 5 istanze di monitor con free() */
	//Devo anche liberare la memoria che ho usato per implementare le istanze dei monitor
	for(i=0; i<5; i++){
		
		free(m[i]);

	}
	
    
	return 0;
}	
