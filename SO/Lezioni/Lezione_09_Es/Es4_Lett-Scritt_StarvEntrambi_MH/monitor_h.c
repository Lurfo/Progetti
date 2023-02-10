//Implementazione del monitor

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>

#include "monitor_h.h"

//Definisco le funzioni "Private" che possono essere utili solo al monitor 
static void wait_sem(int id_sem, int num_sem);
static void signal_sem(int id_sem, int num_sem);
static int queue_sem(int id_sem, int num_sem); //Questa serve a restituire il numero di processi fermi al semaforo!

//----------------------------------------------------------------------------------------------------------------------//

//Funzione che inizializza il monitor, l'unica cosa di cui ha bisogno in ingresso è il numero di variabili condition
void init_monitor(Monitor* m, int num_var){

    /*NOTA
        ~Il primo passo da fare è inizializzare tutti i semafori che mi occorrono    
    */


    //Inizializzo il semaforo per l'accesso al monitor, lo pongo ad 1!
    m->mutex=semget(IPC_PRIVATE, 1, IPC_CREAT|0660);

    semctl(m->mutex, 0, SETVAL, 1); //Il primo processo può sempre entrare


    //Inizializzo il semaforo urgente, posto a 0!
    m->urgent_sem=semget(IPC_PRIVATE, 1, IPC_CREAT|0660);

    semctl(m->urgent_sem, 0, SETVAL, 0);


    //Inizializzo i semafori per le variabili condition!
    m->num_var_cond=num_var;

    m->id_conds=semget(IPC_PRIVATE, num_var, IPC_CREAT|0660);

    for(int i=0; i<num_var; i++){
        semctl(m->id_conds, i, SETVAL, 0);
    }


    /*NOTA
        Devo quindi andare ad allora la memoria condivisa per i contatori!    
    */

   //Allora una memoria per comprendere i contatori delle var cond e della coda urgent
   m->id_shared=shmget(IPC_PRIVATE, (num_var+1)*sizeof(int), IPC_CREAT|0660);

   printf("Size della sharedMem Monitor: %ld\n", (num_var+1)*sizeof(int));

   //Attach dell'array
   m->cond_count = (int*) (shmat(m->id_shared, 0, 0));

   printf("m->cond:count: %p\n", m->cond_count);

   //Imposto il puntatore al contatore per la coda urgente
   //Sommado al puntatore precedente il numero di "slot" di memoria destinati alle varie var condition
   m->urgent_count = m->cond_count + m->num_var_cond;

   printf("m->urgent_count: %p\n", m->urgent_count);

    //Non resta altro che inizializzare i valori
    for(int i=0; i<num_var; i++){
        m->cond_count[i]=0;
    }

    *(m->urgent_count)=0;

}

//Funzioni principali per sfruttare il monitor

void enter_monitor(Monitor* m){
    //La funzione di enter monitor è quella più semplice, devo effettuare una 
    //wait sul mutex di ingresso
    wait_sem(m->mutex, 0);

}


void leave_monitor(Monitor* m){
    //La funzione di leave è altrettando semplice, devo effettuare un controllo sul contatore!

    //Se il numero di processi urgenti in coda è maggiore di zero, allora effettuo una signal sul semaforo per gli urgenti
    if(*(m->urgent_count)>0){
        signal_sem(m->urgent_sem, 0);
    }

    //Altrimenti, se non ho processi urgenti in attesa, posso andare a lasciare gli altri processi
    else{
        signal_sem(m->mutex, 0);
    }
}



void remove_monitor(Monitor* m){
    //La funzione di rimozione del monitor, deve andare a rimuovere tutte le strutture create
    //Rimozione dei semafori
    semctl(m->mutex, 0, IPC_RMID, 0);
    semctl(m->urgent_sem, 0, IPC_RMID, 0);
    semctl(m->id_conds, m->num_var_cond, IPC_RMID, 0);

    //Rimozione della memoria condivisa
    shmctl(m->id_shared, IPC_RMID, NULL);
}


void wait_condition(Monitor* m, int var){

    //Incremento il numero di processi che si accoda a quella variabile
    m->cond_count[var]+=1;

    //A questo punto, prima di effettuare la wait sull varabile condition, devo lasciare il monitor, in base
    //all'implementazione del monitor che ho scelto

    //Devo verificare se lasciare i processi urgenti
    if(*(m->urgent_count)>0){
        signal_sem(m->urgent_sem, 0);
    }

    //Altrimenti lascio gli altri 
    else{
        signal_sem(m->mutex, 0);
    }

    //Posso dunque effettuare una wait sul semaforo della variabile condition che ho considerato
    wait_sem(m->id_conds, var);

    //Quando poi verrò sblocato, riprendo da qui e vado a decrementare il valore dei processi incoda a quella condizione
    m->cond_count[var]-=1;



}

//Le medesime considerazioni anche per la signal
void signal_condition(Monitor* m, int var){
    
    //La signal condition è molto simile, solo che devo considerare che il processo segnalante deve poi andarsi ad accordare
    //alla coda dei processi urgenti che sono in attesa!
    //Perchè sto usando un monitor di hoare!
    
    //Incremento il numero di elementi urgenti
    (*(m->urgent_count))++;

    
    //Controllo il numro di elementi urgenti che sono in attesa su quella condizione
    if(m->cond_count[var]>0){
        //Se ho più elementi in attesa, sblocco il semaforo su quella condizione
        signal_sem(m->id_conds, var);
    


        //A questo punto, il processo si mette in attesa sulla coda urgent
        //Aspettando i processi che erano in attesa su quella condizione!
        wait_sem(m->urgent_sem, 0);

    }

    //Quando verrò sbloccato, vado a decrementare il numero di processi urgenti in attesa
    (*(m->urgent_count))--;

}



//Funzione molto semplice, devo andare a restituire il numero di elementi che sono accodati alla var_cond
int queue_condition(Monitor* m, int var){
    return m->cond_count[var];
}



//************************IMPLEMENTAZIONE DELLE FUNZIONI SUI SEMAFORI***************************************************
//Queste sono delle funzioni che occorrono solo alla struttura monitor, che quindi non ho necessità di implementare anche 
//all'esterno di essa!



void wait_sem(int id_sem, int num_sem){
    
    struct sembuf buf; 

    buf.sem_num=num_sem;
    buf.sem_flg=0; 
    buf.sem_op=-1;

    semop(id_sem, &buf, 1);

}


void signal_sem(int id_sem, int num_sem){

    struct sembuf buf; 

    buf.sem_num=num_sem; 
    buf.sem_flg=0;
    buf.sem_op=1;

    semop(id_sem, &buf, 1);

}


//Questa funzionerestituisce il numero di elementi che sono accodati nel semaforo!
//Uso un particolare flag  GETNCNT che specifica alla funzione semctl di restituire il numero di elementi in attesa!
int queue_sem(int id_sem, int num_sem){
    return(semctl(id_sem, num_sem, GETNCNT, NULL));
}
