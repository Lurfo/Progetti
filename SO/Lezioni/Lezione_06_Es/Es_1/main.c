//Specifica di un programma in cui ogni figlio incrementa per cento volte un valore presente all'interno della shared memory!
//Per gestire la concorrenza dei due processi sulla memoria concorrente uso dei semafori

//Per usare le funzioni di wait e signal, uso la loro implementazione nel file che ho definito!
#include "semafor.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//Libreria per l'uso della shared memory, da notare che alcune delle librerie di cui ho bisogno, sono state già definite nel
//header file semafor.c
#include <sys/shm.h>

#include <errno.h>
 
#include <sys/wait.h>

void eseguito(int);
void vedo_mem();


int main(){

    //Definizione della shared memory!
    //Siccome vado ad usare due processi figli, posso usare la chiave come IPC_PRIVATE!
    
    int desc; 

    //Definsco la il descrittore tramite la funzione shmget
    //La memoria deve avere la dimensione di un intero, poichè è quello che vado ad incrementare!
    

    desc = shmget(IPC_PRIVATE, sizeof (int), IPC_CREAT|IPC_EXCL|0660);

    //I flag indicano: 
    // -Creare la memoria se non esiste
    // -Generare un errore se la memoria è presente
    // -Permessi di lettura e scrittura sulla memoria!

    //Conctrollo operaizone!
    //Considerando che non mi interessa usare una memoria già presente
    eseguito(desc); 

    //A questo punto eseguo l'attachmente
    //Eseguendo sempre un casting!
    int* p = (int*) shmat(desc, NULL, 0);

    //Contrllo della corretta esecuzione del'attachment!

    if(p==(void*)-1){
        perror("Non son riuscito a fare l'attachment!\n");
        exit(1);
    }

    printf("I valori della tua Memoria condivisa sono:\n");
    printf("Ha la chiave: %d\n", IPC_PRIVATE); 
    printf("Ha come descrittore: %d\n", desc); 
    printf("Si trova all'indirizzo: %p\n", p);

    printf("----------------------------------\n");
    printf("Controlla che è presente la memoria con descrittore uguale a: %d\n", desc); 

    vedo_mem();

    int status1; 

    wait(&status1); 

    if(!WIFEXITED(status1)){
        printf("Il processo ha completato in modo anomalo!");
        exit(1);
    }

    sleep(10);

    printf("-----------------------------------------\n");

    //Definita la memoria, definisco il semaforo di cui ho bisogno, per andare a sfruttarlo con i processi!

    printf("Definisco i semafori!\n");

    //Per definire il semaforo, devo comunque usare una chiave, ma posso comunque usare IPC_PRIVATE
    //poichè sto usando dei processi figli che interagiscono con una memoria!
    
    //Come nel caso della memoria condivisa, devo usare la funzione semget, per ottenre l'id(o descrittore) del semaforo
    int semid; 

    semid=semget(IPC_PRIVATE, 1, IPC_CREAT|IPC_EXCL|0660);

    //Nota che la funzione semget ha argomenti molto simili alla funzione shmget
    //Quest ha bisogno di: 
    // -La chiave, che è stata impostata con IPC_PRIVATE
    // -Il numero di semafori di cui ho bisogno (Nel caso in esame solo uno poichè devo gestire la sola concorrenza!)
    // -I vari flag che mi interessano + i permessi necessari

    //Effettuo un controllo che il semaforo sia stato creato correttamente!
    eseguito(semid);

    //A questo punto, devo andare ad inizializzare il semaforo per poterlo usare
    //L'inizializzazione la devo svolgere con la funzione setctl! Ha bisogno come argomenti!
    // -L'id dell'inseme dei semafori
    // -Il numero del semaforo che dev inizializzare dell'array
    // -Il flag setval (la funzione inizializza il semaforo al valore del quarto parametro!)
    semctl(semid, 0, SETVAL, 1);
    
    //Ho inizializzato il semaforo con il valore 1, pochè la memoria condivisa è già pronta per essere incrementata!

    printf("----------------------------------\n");
   
    printf("Puoi controllare che è presente il semaforo con id: %d\n", semid); 

    vedo_mem(); 

    int status; 

    wait(&status); 

    if(!WIFEXITED(status)){
        printf("Il processo ha completato in modo anomalo!\n");
        exit(1);
    }
    
    sleep(10);

    printf("--------------------------------\n");

    int iniz=0;

    printf("Dimmi a quando vuoi inizializzare la memoria condivisa prima di procedere!\n");
        scanf("%d", &iniz); 

    *p=iniz;

    printf("Valore della memoria considiva inizializzato a: %d\n", *p);

    printf("-------------------------------------\n");

    //A questo punto definisco i due processi figli che devono andare ad eseguire l'incremento!
    
    //Per definire i due processi, uso una fork inserita all'interno di un ciclo for!

    for(int i=0; i<2; i++){
        
        int pid=fork(); 

        //Controllo della correttezza dell'operazione!
        eseguito(pid);

        //Entro nell'ambito del figlio!
        if(pid==0){
            
            //Il figlio deve andare ad incrementare per 100 volte il valore della memoria condivisa!
            //Uso dunque un ciclo for!

            for(int j=0; j<100; j++){
                //A questo punto il processo figlio esegue una wait sul semaforo per vedere se può andare ad incrementare 
                //la memoria oppure c'è già l'altro processo che la sta occupando (in questo caso verrà sospeso fino a quando
                //non sarà disponibile)!
                wait_sem(semid, 0);

                //Dopo la wait il processo figlio entra nella sezione critica:
                //Cioè è la SEZIONE DOVE SI PUÒ VERIFICARE LA CONCORRENZA TRA I DUE PROCESSI!

                //In questa sezione il processo non deve fare altro che andare ad incrementare il valore nella memoria
                (*p)++; 

                //Dopo aver superato la sezione critica, il figlio esegue una signal sul semaforo per segnalare che ha 
                //concluso il suo compito e quindi la memoria è libera!
                signal_sem(semid, 0);   

                //Il processo ciclerà in questa sezione per 100 volte, eseguendo ogni volta una wait e una signal sul semaforo      
            }

            //Concluso il suo compito, eseguo una exit, in questo modo non rischio una fork bomb perchè il processo figlio
            //comincerà a generare a sua volta altri processi!
            exit(0);
        }
    }

    //Dopo la conclusione dei processi, faccio in modo che il padre aspetti entrambi, avendo creato due processi, effettuo un for 
    for(int i=0; i<2; i++){
        int stato;
        wait(&stato); 

        if(!WIFEXITED(stato)){
            perror("Il processo non ha terminato correttamente!\n"); 
            exit(1);
        } 
    }

    printf("Ho finito gli incrementi!\n");
    printf("Ora il valore nella memoria è uguale a: %d\n", *p);

    //La rimozione del semaforo, avviene sempre tramite la funzione di semctl!
    eseguito(semctl(semid, 0, IPC_RMID));
    //Le passo sempre l'id dell'inseime, il numero del semaforo che devo eliminare e il flag che indica l'eliminazione!
    //In caso di essore restituisce sempre il valore -1, per questo l'ho inserita nella funzione di controllo!

    eseguito(shmctl(desc, IPC_RMID, NULL));

}


void eseguito(int contr){
    
    if(contr<0){
        perror("Mi discpiace, ci sono stati errori nell'esecuzione della funzione!"); 
        exit(1);
    }
    return;

}


//Uso questa funzione per richiamare un processo esterno che mi mostra le risorse condivise!
void vedo_mem(){

    int pid=vfork(); 

    eseguito(pid);

    if(pid==0){
        execlp("ipcs", "ipcs", NULL);
    }

    return;
}