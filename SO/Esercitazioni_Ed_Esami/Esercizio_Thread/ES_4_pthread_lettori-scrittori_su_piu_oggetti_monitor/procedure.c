#include "header.h"



void inizializza(struct monitor* m){

	m->molo=0;
	m->id_nave=0;

    m->numLettori=0;
    m->numScrrittori=0;

    m->lettoriWait=0;
    m->scrittoriWait=0;

    pthread_mutex_init(&(m->mutex), NULL);

    pthread_cond_init(&(m->condLettori), NULL);
    pthread_cond_init(&(m->condScrittori), NULL);
}

void rimuovi (struct monitor* m){
    
    pthread_mutex_destroy(&(m->mutex));
    
    pthread_cond_destroy(&(m->condLettori));
    pthread_cond_destroy(&(m->condScrittori));

}


//SCRITTURA. AGGIORNAMENTO DELLA POSIZIONE DEL TRENO
void scrivi_molo(struct monitor* m, int molo){

    /* TBD: Implementare qui lo schema dei lettori-scrittori con starvation di entrambi.
     * nella parte della SCRITTURA
     */
    //Come prima cosa, entro nel monitor
    pthread_mutex_lock(&(m->mutex)); 

        //Effettuo un controllo sulla variabile che mi indica se ci sono dei lettori che attendono
        //in particolare, siccome ho un unico scrittore per ogni monitor, posso anche non andare a controllare se 
        //ci sono altri scrittori in attesa!
        while(m->numLettori>0){
          
            //Effettuo una wait sulla varcond degli scrittori, incrementando anche il numero di scrittori che sono
            //fermi alla condizione!
            m->scrittoriWait++; 
            pthread_cond_wait(&(m->condScrittori), &(m->mutex));

            //Quanfo vengo sbloccato, diminuisco il numero di sceittori in attesa
            m->scrittoriWait--; 
        }

        //Sono nel monitor, modifico il numero di scrittori presenti
        m->numScrrittori++; 

    //Posso uscire dal monitor per effettuare la lettura
    pthread_mutex_unlock(&(m->mutex));

    //Imposto il numero del molo
    m->molo=molo;

    //Posso rientrare nel monitor
    pthread_mutex_lock(&(m->mutex)); 

        //Diminuisco il numero di scrittori
        m->numScrrittori--;

        //Dovrei controllare se ci sono degli scrittori in attesa per poterli sbloccare, ma siccome ogni scrittore gestice
        //un unico monitor, posso andare direttamente a segnalare i lettori!

        //In questo modo, segnalo tutti i lettori che sono in attesa
        pthread_cond_broadcast(&(m->condLettori));

    //Posso uscire dal monitor
    pthread_mutex_unlock(&(m->mutex));

}



//LETTURA. RESTITUISCE LA POSIZIONE DEL TRENO
int leggi_molo(struct monitor* m){

    int pos;

    /* TBD: Implementare qui lo schema dei lettori-scrittori con starvation di entrambi.
     * nella parte della LETTURA
     */

    //Entro nel monitor
    pthread_mutex_lock(&(m->mutex)); 

        //Controllo se ci sono degli scrittori che stanno già agendo sul monitor!
        while(m->numScrrittori>0){
            
            //Incremento il numero di lettori in attesa
            m->lettoriWait++;

            //Faccio una wait sulla condizione dei lettori 
            pthread_cond_wait(&(m->condLettori), &(m->mutex));

            //Vengo sbloccato, decremento il numero di lettori in attesa!
            m->lettoriWait--;

        }

        //Aumento il numero di lettori nel monitor
        m->numLettori++;

    //Posso lasciare il monitor per leggere!
    pthread_mutex_unlock(&(m->mutex));

    //Leggo il valore, salvandolo nella variabile!
    pos=m->molo;

    //printf("Sono un lettore, ho letto il valore: %d\n", pos);

    //Ritorno nel monitor per andare a diminuire il numero di lettori presenti
    pthread_mutex_lock(&(m->mutex)); 

        m->numLettori--; 

        //Controllo se sono l'ultimo lettore, allora sblocco gli scrittori che attendono
        if(m->numLettori==0){
            pthread_cond_signal(&(m->condScrittori));
        }

    //Posso uscire dal monitor
    pthread_mutex_unlock(&(m->mutex));

    //Ritorno il valore che ho letto
    return pos;


}

