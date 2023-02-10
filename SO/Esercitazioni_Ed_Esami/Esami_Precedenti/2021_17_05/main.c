#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "prodcons.h"


void * produttore_1(void * p){

	//Effettuo il casting inverso per ottenere la struttura MonitorPC

	MonitorPC *m  = (MonitorPC *) p;

	for(int i=0; i<4; i++) {

		int valore = rand() % 10;

		/* TBD: chiamare il metodo di produzione tipo 1 */
		produci_tipo_1(m, valore);

		sleep(1);
	}

	pthread_exit(NULL);
}


void * produttore_2(void * p){
    
	//Casting inverso
	MonitorPC *m = (MonitorPC *) p;

	for(int i=0; i<4; i++) {

		int valore = rand() % 10;

		/* TBD: chiamare il metodo di produzione tipo 2 */
		produci_tipo_2(m, valore);

		sleep(1);
	}

	pthread_exit(NULL);
}


void * consumatore_1(void * p){

	MonitorPC *m = (MonitorPC *) p;

	for(int i=0; i<8; i++) {

		int valore;

		/* TBD: chiamare il metodo di consumazione tipo 1 */
		consuma_tipo_1(m, &valore);
		
		printf("CONSUMATORE1: Consumato valore %d\n", valore);

		sleep(1);
	}

	pthread_exit(NULL);
}


void * consumatore_2(void * p){

	MonitorPC *m = (MonitorPC *)p;

	for(int i=0; i<8; i++) {

		int valore;

		/* TBD: chiamare il metodo di consumazione tipo 2 */
		consuma_tipo_2(m, &valore); 

		printf("CONSUMATORE2: Ho consumato, valore %d\n", valore);

		sleep(1);
	}

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{

	pthread_t thread_produttori_1[2];
	pthread_t thread_produttori_2[2];
	pthread_t thread_consumatore_1;
	pthread_t thread_consumatore_2;

	pthread_attr_t attr;

	//Inizializzo l'attributo e lo imposto per creare dei thread joinabili
	pthread_attr_init(&attr);

	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
	int rc;
	int i;

	srand(time(NULL));

    
	/* TBD: creare e inizializzare l'oggetto monitor */
	//Utilizzo una malloc per allocare il monitor 
	MonitorPC *m = (MonitorPC *) malloc(sizeof(MonitorPC)); 

	//Inizializzo il monitor, usando la funzione apposita
	inizializza(m);

	for(int i=0; i<2; i++) {

		/* TBD: avviare 2 produttori di tipo 1 */
		rc = pthread_create(&thread_produttori_1[i], &attr, produttore_1, (void *) m);

			if(rc){
				perror("Errore nella creazione produttori 1\n"); 
					exit(1);
			}

	}

	for(int i=0; i<2; i++) {

		/* TBD: avviare 2 produttori di tipo 2 */
		rc = pthread_create(&thread_produttori_2[i], &attr, produttore_2, (void *) m);

			if(rc) {
				perror("Errore nella crazione produttori 2\n"); 
					exit(1);
			}
		
	}

	/* TBD: avviare consumatore di tipo 1 */

	rc = pthread_create(&thread_consumatore_1, &attr, consumatore_1, (void *) m);

		if(rc){
			perror("Errore nella creazione consumatore1\n"); 
				exit(1);
		}

	/* TBD: avviare consumatore di tipo 2 */
	rc = pthread_create(&thread_consumatore_2, &attr, consumatore_2, (void *) m);

		if(rc){
			perror("Errore nella creazione consumatore2\n");
		}


	
	
	for(int i=0; i<2; i++) {

		/* TBD: attendere terminazione produttori di tipo 1 */
		rc = pthread_join(thread_produttori_1[i], NULL);

			if(rc){
				perror("Errore join produttori 1\n"); 
					exit(1);
			}

	}


	for(int i=0; i<2; i++) {

		/* TBD: attendere terminazione produttori di tipo 2 */
		rc = pthread_join(thread_produttori_2[i], NULL);

			if(rc){
				perror("Errore join produttori 2\n"); 
					exit(1);
			}

	}

	/* TBD: attendere terminazione consumatori di tipo 1 */
	rc = pthread_join(thread_consumatore_1, NULL);

		if(rc){
			perror("Errore join consumatori 1\n"); 
				exit(1);
		}

	/* TBD: attendere terminazione consumatori di tipo 2 */
	rc = pthread_join(thread_consumatore_2, NULL); 

		if(rc){
			perror("Errore join consumatore 2\n"); 
				exit(1);
		}

	/* TBD: rimuovere l'oggetto monitor */
	//Dopo aver atteso la terminazione dei thread, rimuovo tutto quello che ho instanziato
	rimuovi(m); 

	//Vado anche a liberare la memoria che contiene la struttura 
	free(m); 

	//Faccio terminare il thread principale
	pthread_exit(0);

}
