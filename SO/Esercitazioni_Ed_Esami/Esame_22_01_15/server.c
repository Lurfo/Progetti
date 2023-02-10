//Il server, ha bisogno della memoria condivisa, del semaforo, della coda di messaggi

#include "header.h"


#include <time.h>


#define TOT_RICEVUTE 4

int main(){

    int ret;

    Mess m;

    //Impostazione della memoria condivisa, che contiene il buffer
    key_t kMem = ftok(PATH, CHAR_M); 

    int idMem = shmget(kMem, sizeof(Buffer), 0); 

        if(idMem<0){
            perror("Errore idMem\n"); 
                exit(1);
        }

        //Eseguo shmat, per ottenre il riferimento della memoria condivisa
    Buffer *p = (Buffer *) shmat(idMem, NULL, 0);

    //Impostazione del semaforo
    key_t kSem  = ftok(PATH, CHAR_S);

    int idSem = semget(kSem, NUM_SEM, 0); 

        if(idSem<0){
            perror("Errore idSem\n"); 
                exit(1);        
        }


    //Impostazione della coda di messaggi
    key_t kMess = ftok(PATH, CHAR_C); 

    int idMess = msgget(kMess, 0); 

        //printf("[SERVER %d] Coda ottenuta, con id: %d, chiave: %d\n", getpid(), idMess, kMess);


    //Dunque il server effettua 4 iterazioni
    for(int i=0; i<TOT_RICEVUTE; i++){
        
        //Il server si mette prima in attesa del messaggio
        ret = msgrcv(idMess, (void *) &m, SIZE(Mess), SDT_TYPE, 0); 

            printf("[SERVER %d] Richiesta ricevuta, valori: %d, %d\n", getpid(), m.val1, m.val2);

        //Dunque, effettuo una wait sul semaforo per entrare nella sezione critica 
        wait_sem(idSem, MUTEX); 

            //Inizio la sezione critica, modificando i parametri della memoria condivisa
            p->val1=m.val1; 
            p->val2=m.val2; 

            printf("[SERVER %d] Richiesta soddisfatta, valori: %d, %d\n", getpid(), p->val1, p->val2);

        //Posso dunque lasciare la sezione critica
        signal_sem(idSem, MUTEX); 

    }

}