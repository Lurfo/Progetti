#include "header.h"

#define NUM_PROD 4
#define NUM_CONS 2

#define PRODUZIONI 3
#define CONSUMAZIONI 4

void * produttore(void *g){

    srand(time(NULL)*getpid());

    //Effettuo un casting inverso
    GestioneIO * p = (GestioneIO *) g;

    Buffer elemento;

    //Il produttore deve effettuare 4 produzione, tramite iterazione
    for(int i=0; i<PRODUZIONI; i++){

        //Controllo se sono la prima produzione
        //In questo modo, posso andare a generare dei valori casuali
        if(!i){    

            printf("[PRODUTTORE] Sono la prima produzione!\n");

            //Imposto i valori casuali
            elemento.dato = rand()%10+1;
            elemento.indirizzo = rand()%10+1;

            //Invio l'elemento alla funzione apposita 
            Produci(p, &elemento);

        }

        //Altrimenti, incremento i valori
        else{

            elemento.dato++; 
            elemento.indirizzo++; 

            //Passo alla funzione di produzione 
            Produci(p, &elemento);

        }

        //Attendo 1 secondo ogni produzione
        sleep(1);

    }

    //Faccio terinare il thread 
    pthread_exit(NULL);

}


void * consumatore(void *g){

    //Effettuo casting inverso dell'argomento 
    GestioneIO * p = (GestioneIO *) g;

    //Buffer dove salvare i dati 
    Buffer elemento; 

    //Il consumatore ha 4 iterazioni da compiere
    for(int i=0; i<CONSUMAZIONI; i++){

        //Ogni iterazione effettua consumazioni multiple, fino a che non è vuoto il vettore!
        //Se il vettore è vuoto, vuol dire che il valore di ritorno è 1
        //Dunque, imposto la condizione del ciclo interno, in base al valore di ritorno, della funzione consuma
        while(Consuma(p, &elemento)!=1){
            
            printf("[CONSUMATORE (nel while)] Ho consumato\n"); 

            printf("Valore del dato: %d, valore indirizzo: %d\n", elemento.dato, elemento.indirizzo);

        }

        //Dopo ogni consumazione, attendo sempre 3 secondi
        sleep(3);         

    }

    //Faccio terminare il thread 
    pthread_exit(NULL);

}

//Definizione del main
int main(){

    int ret;

    //Array che contentono id dei thread
    pthread_t produttori[NUM_PROD]; 
    pthread_t consumatori[NUM_CONS]; 

    //Definizione dell'attributo
    pthread_attr_t attr; 

    //Ottenimento del puntatore alla struttura dati
    GestioneIO *p = (GestioneIO *) malloc(sizeof(GestioneIO)); 

    //Posso dunque inizializzare la struttura (contente mutex e variabili condition) e l'attrivuto
    Inizializza(p, &attr);

    //A questo punto, posso andare a creare i thread produttori e consumatori 
    for(int i=0; i<NUM_PROD; i++){

        ret = pthread_create(&produttori[i], &attr, produttore, (void *)p); 

            if(ret){
                perror("Errore creazione thread produttori\n"); 
                    exit(1);
            }

    }

    for(int i=0; i<NUM_CONS; i++){
        
        ret = pthread_create(&consumatori[i], &attr, consumatore, (void *)p); 

            if(ret){
                perror("Errore creazione trhead consumatori\n"); 
                    exit(1);
            }
    }


    //A questo punto, effettuo il join sia dei produttori che dei conumatori
    for(int i=0; i<NUM_PROD; i++){
        
        ret = pthread_join(produttori[i], NULL); 

            if(ret){
                perror("Errore join produttori\n"); 
                    exit(1);
            }

    }

    for(int i=0; i<NUM_CONS; i++){
        
        ret = pthread_join(consumatori[i], NULL); 

            if(ret){
                perror("Errore join consumatori\n"); 
                    exit(1);
            }

    }


    //Devo rimuovere gli elementi che sono presenti nella struttura e andare a liberare la memoria 
    rimuovi(p, &attr); 

    free(p); 

    //Faccio terminare il thread principale
    pthread_exit(NULL);


}