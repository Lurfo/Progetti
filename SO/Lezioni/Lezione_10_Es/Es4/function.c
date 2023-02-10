#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "function.h"


//Definizione delle due starting function!
void * Scrittura( void *arg){
    //Eseguo il cast inverso dell' argomento della funzione!

    data* pnt = (data *) arg; 

    int lung = pnt->strlen;

    char msg[lung];

    for(int i=0; i<3; i++){

        //A questo punto il Lo scrittore, deve controllare se può entrare nel monitor!
        pthread_mutex_lock(&(pnt->mutex)); 

            //Effettua un controllo sulle condizioni, in particolare, verifica se esso è il primo scrittore e se non ci sono 
            //dei lettori che stanno già controllando il messaggio che gli è stato inviato
            //Essendo un monitor signal and continue, devo sempre sfruttare il while per controllare la condizione!
            while(pnt->numScritt>0 || pnt->numLett>0){
                
                pnt->scritt_wait++;

                pthread_cond_wait(&(pnt->v_scritt), &(pnt->mutex));
                //Incremento anche il numero di scrittori che sono in attesa!
                
                pnt->scritt_wait--;
            }

            //Se sono qui, vuol dire che mi sono sbloccato, a questo punto, vado a modificare il numero di scrittori che sono
            //presenti, in modo da bloccare sia i consumatori, che altri scrittori che sono in attesa!
            pnt->numScritt++;

        //Posso lasciare il monior, infatti la scrittura, così come anche la consumazione, vanno fatte fuori dal monitor!
        //Inolte, questo permette anche ad altri scrittori di mettersi in coda!
        pthread_mutex_unlock(&(pnt->mutex));

        //Vado a produrre il mio messaggio!

        for(int i=0; i<lung; i++){
            msg[i]= 'a' + rand()%26;
        }

        msg[lung] = '\0'; 

        printf("Ho Scritto il messaggio: %s\n", msg); 

        //Vado a copiare il messaggio che ho scritto nella struttura
        strcpy(pnt->str, msg);

        //A questo punto, Devo rientrare nel monitor
        //Per poter bilanciare la starvation, devo prima controllare se ci sono scrittori in attesa (eventualmente sbloccandoli)
        //se non ci sono, devo andare a sbloccare i lettori!
        pthread_mutex_lock(&(pnt->mutex));

            //Modifico il valore di scrittori che sono presenti nel monitor
            pnt->numScritt--; 

            if(pnt->scritt_wait>0){
                pthread_cond_signal(&(pnt->v_scritt));

            }

            else{

                //Tramite questa funzione, risveglio tutti i lettori che sono in attesa!
                pthread_cond_broadcast(&(pnt->v_lett));
            }



            //Posso fare una signal ai lettori!
            pthread_cond_signal(&(pnt->v_lett));
        
        //Di conseguenza, posso lasciare il monitor!
        pthread_mutex_unlock(&(pnt->mutex));

    }


    pthread_exit((void *) 0);

}



void * Lettura(void *arg){

    //La funzione di lettura è molto simile!
    
    data* pnt = (data*) arg; 

    int lung = pnt->strlen;

    char msg[lung];

    for(int i=0; i<3; i++){

        //Entro nel monitor
        pthread_mutex_lock(&(pnt->mutex));

            //Controllo se ci sono scrittori
            while(pnt->numScritt>0){
                //Aumento il numero di lettori in attesa sulla condizione
                pnt->lett_wait++;

                //Se sono presenti, mi sospendo sulla condizione dei lettori
                pthread_cond_wait(&(pnt->v_lett), &(pnt->mutex));

                pnt->lett_wait--;
            }

            //Se sono qui, vul dire che sono stato sbloccato
            //incremento dunque il numero di lettori
            pnt->numLett++;

        //Posso dunque uscire dalla sezione, in modo che altri lettori, se necessario, si possano mettere in attesa
        pthread_mutex_unlock(&(pnt->mutex));

        //Fuori dalla sezione, leggo il messaggio che ho ricevuto
        strcpy(msg, pnt->str);

        printf("Ho letto il messaggio: %s\n", msg);

        //Devo rientrare nella sezione critica, per diminuire il numero di lettori presenti e, se necessario, "liberare" gli 
        //scrittori che si sono messi in attesa!
        pthread_mutex_lock(&(pnt->mutex)); 

            pnt->numLett--;

            //Controllo di essere l'ultimo lettore per segnalare gli scrittori!
            if(pnt->numLett==0){
                //printf("Sono ultimo lettore, sblocco scrittori!\n"); 
                pthread_cond_signal(&(pnt->v_scritt));
            }

        //Posso uscire dal monitor!
        pthread_mutex_unlock(&(pnt->mutex));
    
    }

    pthread_exit((void *) 0);


}