#include "header.h"



void inizializza(struct monitor* m){

	m->molo=0;
	m->id_nave=0;

    /* TODO: Inizializzare le variabili dell'algoritmo, il mutex, e le variabili condition */

    //Il mutex, lo inizialitto tramite la funzione di libreria
    pthread_mutex_init(&(m->mutex), NULL); 

    //Lo stesso faccio con le variabili conditio 
    pthread_cond_init(&(m->vc_Lett), NULL);
    pthread_cond_init(&(m->vc_Scritt), NULL);

    //Inizializzo a 0 le variabli di controllo!
    m->numLettori=0;
    m->numScrittori=0;

}

void rimuovi (struct monitor* m){
    /* TODO: Disattivare mutex e variabili condition */

    //La rimozione di mutex e VC è sempre fatta attraverso le funzioni di libreria destroy
    pthread_mutex_destroy(&(m->mutex));

    pthread_cond_destroy(&(m->vc_Lett));
    pthread_cond_destroy(&(m->vc_Scritt));
}


//SCRITTURA. AGGIORNAMENTO DELLA POSIZIONE DEL TRENO
void scrivi_molo(struct monitor* m, int molo){

    /* TODO: Implementare qui lo schema dei lettori-scrittori con starvation di entrambi.
     * nella parte della SCRITTURA
     */
    
    //Entro nel monitor, tramite una lock sul mutex
    if(pthread_mutex_lock(&(m->mutex))){
        perror("Errore del lock 1 sul mutex - Scrittore\n"); 
            exit(1);
    }

        //Effettuo dunque un controllo della condizione
        //Voglio verificare se ci sono già dei lettori
        //In generale, dovrei anche controllare se sono già presenti scrittori, ma in questo problema, ogni scrittore
        //È assegnato ad un prorprio monitor, quindi non ho il rischio che ci sia competizione tra due scrittori!
        while(m->numLettori>0){
            
            //Se sono presenti lettori, effettuo una wait sulla condizione degli scrittori
            pthread_cond_wait(&(m->vc_Scritt), &(m->mutex));
              
        }

        //Se sono in questo punto, sono stato sbloccato, vado a modificare il numero di scrittori che sono nel monitor
        m->numScrittori++; 

    //Posso uscire dal monitor, per andare ad effettuare la scrittura!
    if(pthread_mutex_unlock(&(m->mutex))){
        perror("Errore unlock 1 mutex - Scrittore\n");
            exit(1);
    }


    //Posso scrivere la posizione della barca 
    m->molo=molo;

    //Effettuo una lock sul mutex, devo modificare il numero di scrittori presenti e fare una signal a tutti i lettori in
    //attesa
    if(pthread_mutex_lock(&(m->mutex))){
        perror("Errore lock 2 su mutex - Scrittore\n");
            exit(1);
    }  

        m->numScrittori--; 

        //Effettuo una signal a tutti i lettori che sono in attesa sulla loro variabile condition
        //Uso la funzione cond_broadcast, equivalente alla signal_all
        pthread_cond_broadcast(&(m->vc_Lett));

    //Posso dunque effettuare un unlock sul mutex
    if(pthread_mutex_unlock(&(m->mutex))){
        perror("Errore unclok 2 - Scrittore\n"); 
            exit(1);
    }

}





//LETTURA. RESTITUISCE LA POSIZIONE DEL TRENO
int leggi_molo(struct monitor* m){

    /* TODO: Implementare qui lo schema dei lettori-scrittori con starvation di entrambi.
     * nella parte della LETTURA
     */

    int molo;

    //La lettura, ha una struttura molto simile alla scrittura
    if(pthread_mutex_lock(&(m->mutex))){
        perror("Errore lock 1 - Lettore\n");
            exit(1);
    }

        //Una volta che sono qui, effettuo un controllo sulla variabile di controllo, per verificare se ci sono scrittori
        while(m->numScrittori>0){
            
            //Se sono presenti scrittori, effettuo una wait sulla variabile condition dei lettori
            pthread_cond_wait(&(m->vc_Lett), &(m->mutex)); 

        }

        //Se sono qui, sono stato sbloccato, incremento il numero di lettori presenti
        m->numLettori++;

    //Posso effettuare un unlock sul mutex per effettuare poi la lettura 
    if(pthread_mutex_unlock(&(m->mutex))){
        perror("Errore unlock 1 - Lettore\n"); 
            exit(1);
    }

    //Effettuo la lettura della posizione
    molo=m->molo; 

    //Effettuo nuovamente un lock sul mutex
    if(pthread_mutex_lock(&(m->mutex))){
        perror("Errore lock 2 - Lettore\n");
            exit(1);
    }

        //Diminuisco il numero di lettori presenti
        m->numLettori--; 

        //Controllo se sono l'ultimo lettore
        if(m->numLettori==0){
            //In caso positivo, sblocco lo scrittore
            pthread_cond_signal(&(m->vc_Scritt));
        }

    //Posso dunque effettuare unlock sul mutex 
    if(pthread_mutex_unlock(&(m->mutex))){
        perror("Errore unlock 2 - Lettore\n");
            exit(1);
    }

    //Ritorno il valore che ho letto
    return molo;

}

