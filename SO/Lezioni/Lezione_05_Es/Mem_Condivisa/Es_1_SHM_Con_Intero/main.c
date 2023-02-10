//Definizione di un programma che utilizza una shm contenete un intero
#include <stdio.h>
#include <stdlib.h>

//Definisco le due librerie necessarie per usare le funzioni della shm
#include <sys/ipc.h>
#include <sys/shm.h>

//Inserimento delle restanti librerie
#include <errno.h>

//Definizione delle librerie necessarie per fork
#include <unistd.h>
#include <sys/types.h>

#include <wait.h>

//Voglio definire un programma che inserisca un intero in una shm, visto che sto usando solo processi padre e figlio, uso
//come mezzo per ottenere la chiave, la macro IPC_PRIVATE!

int main(){

    //Definizione del descrittore della memoria condivisa
    //Per ottenerlo uso la funzione shmget!

    int ds_shm; 

    //Posso anche non impostare alcun flag, in questo caso, la chiave deve riferisi ad una memoria condivisa esistente, 
    //altrimenti la funzione genera un errore (Restituisce valore uguale a -1)!

    ds_shm = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|IPC_EXCL|0664);

        //Nella funzione get, devo andare ad inserire, oltre la chiave, in questo caso una privata anche, la dimensione della
        //memoria condivisa, nel mio caso deve bastare per un intero!
        //E inserisco anche appositi flag: 
        // IPC_CREAT, va a creare la memoria condivisa se questa non esiste, se esiste la shm con la medesima chiave, alla 
        //viene riutilizzata
        // IPC_EXCL, genera un errore se la memoria condivisa non viene generata (Non vado ad usare una memoria già esistente)
        // 0664, un numero in base ottale, che esprime i permessi di lettura e scrittura per l'utente!

    //Definisco un controllo per l'operazione 
    
    if(ds_shm<0){
        //La funzione shmget genera un -1 se vi è un errore!

        //Se si vuole usare una memoria già esistente, bisogna invocare il descrittore, con la medesima chiave, ma senza flag
        //Una situazione simile a 
        //      ds_shm = shmget(chiave, sizeof(int), 0);
        
        //Non voglio usare una memoria già esistente, dunque esco dal programma in caso di errore!

        perror("Non sono riuscito a creare la memoria condivisa!\n");
        //Faccio terminare il programma con un errore!
        exit(1);
    }

    //Come secondo passo, devo collegare la memoria condivisa!
    //Usando la funzione shmat, che da come risultato un puntatore a void, altrimenti in caso di errore, restituisce -1

    //Effettuo un casting!
    int* p = (int*) shmat(ds_shm, NULL, 0);

        //Alla funzione devo inviare: 
        // Il descrittore della memoria condivisa
        //L'indirizzo di memoria a cui effettuare il collegamento: ATTENZIONE, inviando NULL, come fatto sopra, sarà il kernel
        //che decide a quale indirizzo di memoria effettuare il collegamento, scegliendone uno libero!
        //Infine gli posso inviare differenti flag!

    //Faccio un controllo per essere sicuro che sia andata a buon fine l'operazione!
  
   if(p==(void*)-1){
        perror("C'è stato un errore nel collegamento della memoria, addio\n"); 
        exit(1);
    }

    //Se tutti i passaggi sono andati a buon fine, posso andare a mostrare all'utente tutti i parametri della memoria condivisa

    //La chiave
    printf("La tua memoria, ha come chiave: %d\n", IPC_PRIVATE); 

    //Descrittore
    printf("La tua memoria ha come descrittore: %d\n", ds_shm);

    //L'indirizzo di collegamento"
    printf("Dopo il collegamento, ho ottenuto un indirizzo di memoria uguale a: %p\n", p);

    //A questo punto posso usare la mia memoria condivisa tra due processi imparentati

    //Posso effettivamente andare a verificare, facendo eseguire un processo a se stante tramite console di comando che 
    //la zona di memoria condivisa è stata creata

    printf ("\n\nGuardiamo le Risorse per la comunicazione\n"); 

    //Devo eseguire una fork e poi chiamare una exec!
    int pid1=fork(); 
     
    if(pid1<0){
        perror("Mi dispiace, la creazione non è andata a buon fine\n"); 
        exit(1); 
    }

    if(pid1==0){
        //Vado ad eseguire una exec per mostrare a video il comando
        //Effettuo anche in controllo sulla riuscita della funzione exec
       if(execlp("ipcs", "ipcs", NULL)<0){
           perror("Non sono riuscito a far partire l'eseguibile!");
           exit(1);
       }
    }

    //Il padre aspetta il programma chiamato

    //Posso anche non mettere questa parte in un if, poichè la funzione exec termina direttamente con una exit, dunque 
    //questa parte del codice e quella successiva non vengono eseguite
    wait(NULL); 

    printf("Nota che effettivamente la memoria condivisa è stata creata!\n\n");

    
    //--------------------------------------------------------------------------------

    //In questa parte vado a generare un figlio che scrive nella memoria condivisa!

    //Genero un figlio
    int pid = fork();

    //Controllo

    if(pid<0){
        perror("Ci ha stato un error\n");
        exit(1); 
    }

    if(pid==0){
       
        printf("Sono tuo figlio, con pid: %d, ora posso tranquillamente farmi i fatti miei\n", getpid()); 

        int numero; 

        printf("Dimmi il numero da mettere nella memoria condivsa, con indirizzo: %p!\n", p); 
        scanf("%d", &numero);

        *p=numero;

        printf("Numero salvato, ritorno da mio padre\n");

        exit(0);
    }

    //A questo punto faccio in modo che il padre aspetti quello che fa il figlio

    //Definisco una variabile di stato per controllare se il figlio ha concluso il suo compito in maniera corretta!
    //posso anche ometterla!
    int stat; 

    printf("È terminato il compito di: %d\n", wait(&stat));

    if(WIFEXITED(stat)){
        printf("Il suo lavoro è stato completato egregiamente\n"); 
    }

    printf("Il valore della memoria condiviasa è infatti uguale a: %d\n", *p);
    
    printf("Ho completato le operazioni sulla memoria condivisa, devo quindi staccarla e rimuoverla!\n");

    //Per rimuovere la memoria condivisa devo usare la funzione di controllo!
    //La inserisco in una struttura di controllo per verificare che è stata eseguita correttamente!

    //Alla funzione di controllo shmctl, devo inviare: 
  
    //  Descrittore della memoria condivisa
  
    //  Comando che voglio eseguire sulla memoria (Per la rimozione, uso il comando IPC_RMID)
  
    //  Potrei anche passargli il puntatore ad una struttura del tipo shmid_ds, che viene creata nel kernel, nel caso in esame
    //  non specifico alcun puntatore!

    if(shmctl(ds_shm, IPC_RMID, NULL)==-1){
        perror("Ci ha stato un problema nella rimozione della memoria condivisa!\n");
        exit(1);
    }

    printf("-----------------------------------------------------\n"); 
    printf("Ti posso mostrare che effetivamente la memoria condivisa è stata cancellata!\n");

    //Eseguo una fork con un exec!

    int pid2=vfork();

    if(pid2<0){
        perror("La creazione non è andata a buon fine!\n"); 
        exit(1); 
    }

    if(pid2==0){

        wait(NULL);

       if(execlp("ipcs", "ipcs", NULL)<0){
           perror("Non sono riuscito a richiamare il processo!\n");
           exit(1);
       }
    }

    

}