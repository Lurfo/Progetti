//Definizione della funzione iniziale!
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/shm.h>
#include <sys/wait.h>
#include <errno.h>

#include <time.h>

//Inclusione delle librerie necessarie per l'uso delle funzioni!
#include "function.h"
#include "semafor.h"

//Specifico il numero di produttori e il numero di consumatori!
#define NUMERO_PRODUTTORI 5
#define NUMERO_CONSUMATORI 5

typedef struct circular buffer;

int main(){
    
    //Definisco la shm
    //Uso i figli, quindi sfrutto la chiave privata!
    
    int shmID = shmget(IPC_PRIVATE, sizeof(buffer), IPC_CREAT|IPC_EXCL|0660); 

        if(shmID<0){
            //Non voglio usare una memoria già creata!
            perror("Errore shmID\n"); 
                exit(1);
        }

    //Proseguo con l'attachment della memoria!

    buffer* punt = (buffer*) shmat(shmID, NULL, 0);

        if(punt==(void*)-1){
            perror("Errore shmat\n");
                exit(1);
        }

    printf("Memoria creata\n");

    printf("#############################################################\n"); 


    printf("Definisco il semaforo!\n"); 

    //Ottengo l'id del semaforo!

    //Come definiti in function.h, ho bisogno di 4 semafori
    int semID = semget(IPC_PRIVATE, 4, IPC_CREAT|IPC_EXCL|0660); 

        if(semID<0){
            perror("Errore semget!\n"); 
                exit(1);
        }

    //Inizializzo i valori del semaforo

    //Semafori che gestiscono la sincronizzazzione tra produttori e consumatori

    //Il semaforo dello spazio disponibile deve essere inizializzato al valore di elementi che posso inserire nella lista
    semctl(semID, SPAZIO_DISPONIBILE, SETVAL, DIM); 

    //Il semaforo di messaggio disponibile, lo devo inizializzare a 0 poichè devo andare a considerare che inizialmente 
    //non ci sono elementi nella lista 
    semctl(semID, MESSAGGIO_DISPONIBILE, SETVAL, 0); 

    //I due semafori che gestiscono la mutua esclusione, devono essere entrambi inizializzati ad 1!
    //Questo perchè il primo che arriva può direttamente andare ad operare sulla memoria condivisa!
    semctl(semID, MUTEX_C, SETVAL, 1); 
    semctl(semID, MUTEX_P, SETVAL, 1);

    printf("Semafori inizializzati!\n");

    printf("################################################\n"); 

    printf("Avvio il processo di produzione e consumazione!\n"); 

    //Inizializzo i valori di testa e di coda della lista, li devo porre entrambi a 0, in modo da non ottenere dei valori
    //errati

    punt->testa=0;
    punt->coda=0; 

    //Inizio con la creazione dei processi!

    //Creazione dei processi produttore!

    sleep(1);

        for(int i=0; i<NUMERO_PRODUTTORI; i++){
            int pid=fork(); 
                
                if(pid<0){
                    perror("Errore fork produttori\n");
                        exit(1);
                }

                if(pid==0){

                    //printf("Inizio figlio produttore\n");
                    
                    //Faccio in modo di generare un seme sul quale andare a basare la produzione di numeri casuali! 
                    //sfruttando il pid e il tempo, ogni processo ha un seed differente, in modo da ottenere dei valori casuali
                    //sempre differenti
                    srand(getpid()*time(NULL));

                    produttore(punt, semID);
                        exit(0);
                }
        }    

    //Creazione dei processi consumatori
      
        for(int i=0; i<NUMERO_CONSUMATORI; i++){
                    
                int pid=fork(); 
                    
                    if(pid<0){
                        perror("Errore fork consumatori\n"); 
                            exit(1);
                    }

                    if(pid==0){


                        //printf("Inizio figlio consumatore\n");

                        consumatore(punt, semID);
                            exit(0);
                    }
        }

    

    for(int i=0; i<NUMERO_PRODUTTORI+NUMERO_CONSUMATORI; i++){
        wait(NULL);
    }

    printf("Ho concluso tutto il mio compito!\n");


    //Eliminazione della shared memory e dei semafori
    
    shmctl(shmID, IPC_RMID, NULL);
    semctl(semID, 0, IPC_RMID);
    

}

