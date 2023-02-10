#include "semafor.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/shm.h>

#include <time.h>

//In questo problema voglio che i processi figli possano accedere in mutua esclusione al buffer che devono andare a modificare
//per trovare il valore minimo all'interno dell'insieme dei numeri che inserisco nel vettore!

//Dunque, in questo problema, il semaforo serve a regolare l'accesso al buffer evitando così che ci siano due processi che vogliono
//modificare il buffer nel medesimo istante!
//(Causando dunque un eventuale errore!)

void eseguito(int);
void figlio(int*, int*, int, int, int, int);

int main(){

    printf("Mi occupo della memoria del vettore\n");

    //Definizione della memoria che deve contenere un certo numero di interi!
    int vetID = shmget(IPC_PRIVATE, 10000*sizeof(int), IPC_CREAT|IPC_EXCL|0660);

    if(vetID<0){
        perror("Errore shmget!\n"); 
        exit(1);
    }

    int* p = (int*) shmat(vetID, NULL, 0);

    if(p==(void*)-1){
        perror("Errore shmat\n");
        exit(1);
    }

    printf("Memoria creata!\n"); 
    printf("Chiave: %d\n", IPC_PRIVATE); 
    printf("Id: %d\n", vetID);
    printf("Indirizzo: %p\n", p);

    printf("################################################\n"); 

    int val;

    printf("Dimmi il massimo numero randomico che devo inserire nel vettore\n");
        scanf("%d", &val); 
    
    printf("Inizializzo!\n"); 

    srand(time(NULL));

    for(int i=0; i<10000; i++){
        
        p[i]=(rand()%val)+1;

        //printf("%d\n", p[i]);
    }

    printf("Inizializzato!\n");



    printf("##################################################\n"); 

    //Definizione del semaforo che deve gestire la concorrenza, tra processi padre e figlio!
    printf("Mi occupo del semaforo\n");

    int semID = semget(IPC_PRIVATE, 1, IPC_CREAT|IPC_EXCL|0660);
        if(semID<0){
            perror("Errore semget!\n");
            exit(1);
        }

    //Inizializzazione del semaforo
    //Lo inizializzo ad uno perchè sto effettuando una mutua escusione!
    //Dunque vuol dire che il primo processo che arriva è quello che può direttamente accedere alla risorsa!
    //Gli altri devono aspettare che questo finisca il suo compito!

    if(semctl(semID, 0, SETVAL, 1)<0){
        perror("Errore inizializzazione semaforo!\n");
        exit(1);
    }

    printf("################################################\n");

    printf("Mi occupo della memoria del buffer!\n");

    //Inizializzo il costruttore

    int bufDESC = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|IPC_EXCL|0660); 

    if(bufDESC<0){
        perror("Errore funzione del buffer!\n"); 
        exit(1);
    }
    
    //Faccio l'attachment
    int* buff = (int*)shmat(bufDESC, NULL, 0);
    
    if(buff==(void*)-1){
        perror("Problema attachment del buffer!\n"); 
        exit(1);
    }

    //Inizializzo il contenuto del buffer a zero!

    *buff=0; 


    printf("Ho ottenuto il buffer\n"); 
    printf("Chiave:%d\n", IPC_CREAT); 
    printf("Id: %d\n", bufDESC);
    printf("Indirizzo: %p\n", buff);
    printf("Inizializzato a: %d\n", *buff);

    printf("#############################################\n");

    //A questo punto devo definire quello che deve fare il figlio!
    //In questo caso, voglio che il figlio esegua il contenuto della funzione figlio!

    //Divido l'intervallo tra 10 intervalli differenti, ognuno di 1000 numeri
    //Ho bisongno dunque di effettuare 10 fork!

    for(int i=0; i<10; i++){
        
        int pid=fork(); 

        if(pid<0){
            perror("Errore nel fokr\n");
            exit(1);
        }

        if(pid==0){
            //Figlio deve chiamare la funzione apposita!
            figlio(p, buff, semID, 0, 1000*i, 1000);
            exit(0);
        }

    }

    //Il padre attende che vengano terminati tutti i figli!
    for(int i=0; i<10; i++){
        wait(NULL);
    }

    printf("Hanno concluso il loro lavoro, il valore minimo è: %d\n", *buff);

    //Rimozione di tutte le risorse condivise!
    shmctl(vetID, IPC_RMID, 0); 
    shmctl(bufDESC, IPC_RMID, 0);
    semctl(semID, 0, IPC_RMID);


}

void figlio(int* vett, int* buff, int IdSem, int semNum, int primoNum, int interv){
    //Il figlio deve trovare il minimo nell'intervallo che gli viene assegnato!
    int min=0; 

    //NOTA BENE:Non sto proteggendo il vettore dall'accesso dei figli, perchè questi non devono fare altro 
    //che leggere dalla risorsa, quindi non rischio che più processi vogliano modificare la risorsa!

    //Trovo il minimo nell'intervallo!
    for(int i=primoNum; i<primoNum+interv; i++){
        if(min==0 || vett[i]<min){
            min=vett[i];
        }
    }

    //A questo punto inizia la sezione critica in cui i figli vogliono modificare il valore del buffer, eseguo prima una wait
    //sul semaforo!

    printf("Ho trovato il minimo locale, uguale a: %d!\n", min);


    wait_sem(IdSem, semNum);

    //Effettuata una wait sul semaforo, posso andare a svolgere quello che mi serve!

    if(*buff==0 || min<*buff){
        *buff=min;
    }

    //Effettuo la signal sul semaforo per segnalare che ho finito il mio compito!
    signal_sem(IdSem, semNum);

    //Ho concluso quello che deve fare il figlio!

    return;

}

