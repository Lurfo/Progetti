/*************************************Monitor*************************************************/
// Implementazione di un Monitor Signal and Continue 
//Specifica delle funzioni

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include "monitor_signal_continue.h"


//Funzioni di utilita' private alla libreria Monitor
static void Wait_Sem(int, int);
static void Signal_Sem (int,int);
static int Queue_Sem (int,int);   //restituisce il num di processi in attesa su un semaforo


/********************IMPLEMENTAZIONE DELLE PROCEDURE***********************/

void init_monitor (Monitor *M,int num_var){

    //Definizione del semaforo per accedere al monitor 
    //Inizializzato ad 1, il primo processo che arriva, può accedere liberamente al suo interno   
    M->mutex=semget(IPC_PRIVATE,1,IPC_CREAT|0664);

    semctl(M->mutex,0,SETVAL,1);


    //Alloco il semaforo per le variabili condivise e le inizializzo a 0
    M->id_conds=semget(IPC_PRIVATE,num_var,IPC_CREAT|0664);

    for (int i=0;i<num_var;i++){
         semctl(M->id_conds,i,SETVAL,0);
    }

    //Alloco una memoria dinamica che va a contenere i contatori per ogni var_cond
    M->id_shared=shmget(IPC_PRIVATE,num_var*sizeof(int),IPC_CREAT|0664);


    //Faccio l'attach dell'array dei contatori
    M->cond_counts=(int*) (shmat(M->id_shared,0,0));

    M->num_var_cond = num_var;



    //Inizializzo i contatori!
    for (int i=0; i<num_var; i++)
        M->cond_counts[i]=0;

} 



void enter_monitor(Monitor * M){

    //La enter monitor, come nel caso del monitor di hoare, effettua una semplice wait sul mutex di ingresso al monitor!
    Wait_Sem(M->mutex,0);

}


void leave_monitor(Monitor* M){

    //Leave è molto più semplice del caso del monitor di hoare, perchè devo andare semplicemente ad effettuare una signal
    //sul mutex di ingresso al semaforo
    Signal_Sem(M->mutex,0);
}


void remove_monitor(Monitor* M){

    //Nella remove, devo semplicemente rimuovere tutte le strutture che ho creato per il monitor!
    semctl(M->mutex,0,IPC_RMID,0);
    semctl(M->id_conds,M->num_var_cond,IPC_RMID,0);
    shmctl(M->id_shared,IPC_RMID,0);

}

void wait_condition(Monitor* M,int id_var){

    //Come prima cosa, incremento il numero di elementi che si trovano in coda alla variabile condition
    M->cond_counts[id_var]=M->cond_counts[id_var]+1;

    //Lascio il monitor in modo che possano entrare anche altri processi
    Signal_Sem(M->mutex,0);
     
    //A questo punto, posso effettuare la wait per la var_condition, sul semaforo ad essa corrispondente
    Wait_Sem(M->id_conds,id_var);


   //Effettuo una wait sul mutex di ingresso al monitor in modo da rimettermi in coda insieme agli altri processi che attendono
    Wait_Sem(M->mutex,0);
}

//Specifica della funione di signal della variabile condition
void signal_condition(Monitor* M,int id_var){
    
    //La signal condition è molto semplice, vado infatti a controllare che ci siano effettivamente dei processi che sono
    //in attesa della variabile

    if(M->cond_counts[id_var] > 0){
        
        //Se ci sono dei processi in attesa, entro nell'if

        //La prima coda da fare è decrementare il valore delle var condition in attesa sul semaforo
        M->cond_counts[id_var]--;

        //Effettuo quindi una signal sul semaforo di quella var condition
	    Signal_Sem(M->id_conds,id_var);

        //La signal non fa nient'altro, il processo che segnala continua la sua esecuzione
        //Il processo segnalato, al contrario, si trova in attesa di entrare nel monitor, appena sarà il suo turno, esso può
        //entrare. 
        //Per questa ragione, il controllo della condizione, deve essere effettuato con un while, perchè la condizione
        //potrebbe essere modificata da altri processi
    }

}

//Questa funzione, serve a restituire il numero di processi che sono in attesa di una variabile!
int queue_condition(Monitor * M, int id_var){
	return M->cond_counts[id_var];
}


/********************IMPLEMENTAZIONE DELLE PROCEDURE SEMAFORICHE***********************/

//Le istruzioni dei semafori, sono analoghe a quelle del monitor di hoare

void Wait_Sem(int id_sem, int numsem)     {
       struct sembuf sem_buf;

       sem_buf.sem_num=numsem;
       sem_buf.sem_flg=0;
       sem_buf.sem_op=-1;
       semop(id_sem,&sem_buf,1);   //semaforo rosso
}

// restituisce il numero di processi in attesa sul semaforo
int Queue_Sem(int id_sem, int numsem)     {
	return (semctl(id_sem,numsem,GETNCNT,NULL));
}

void Signal_Sem (int id_sem,int numsem)     {
       struct sembuf sem_buf;

       sem_buf.sem_num=numsem;
       sem_buf.sem_flg=0;
       sem_buf.sem_op=1;
       semop(id_sem,&sem_buf,1);   //semaforo verde
}
