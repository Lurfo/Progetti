//Definizione del main
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "function.h"
#include "semafor.h"

//Il main deve andare a specificare la memoria condivisa e il semaforo, andando ad inizializzarli!



int main(){

    srand(time(NULL));

   printf("Inizializzazione del buffer condiviso\n");

    //Poichè sto considerando processo padre e i suoi figli, allora posso andare a definire la chiave come IPC_PRIVATE

    int shmID = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|IPC_EXCL|0664);

        if(shmID<0){
            perror("Errore shmget\n"); 
                exit(1);
        }

    //Eseguo l'attachment

    int* buff = (int*) shmat(shmID, NULL, 0);

    printf("Memoria condivisa inizializzata\n");
    printf("Chiave privata: %d\n", IPC_PRIVATE); 
    printf("ID: %d\n", shmID); 
    printf("Indirizzo: %p\n", buff);

    printf("##################################################\n");

    //Inizzializzo i due semafori!

        sleep(2);

    printf("Mi occupo dei semafori\n"); 

    //Uso sempre come chiave IPC_PRIVATE

    int semID = semget(IPC_PRIVATE, 2, IPC_CREAT|IPC_EXCL|0664);

        if(semID<0){
            perror("Errore semget\n"); 
                exit(1);
        }

    //Devo dunque inizializzare i due semafori prima di poterli usare!
    
    //Imposto ad 1 il semaforo che definisce se la memoria è disponibile per essere, scritta
    semctl(semID, SPAZIO_DISP, SETVAL, 1); 

    //Imposto a 0 il semaforo che definisce che il valore della memoria è vuoto, poichè presuppongo che 
    //inizialmente non ci sia nessun messaggio da consumare!
    semctl(semID, MESSAGGIO_DISPONIBILE, SETVAL, 0);

    printf("Inizializzato il semaforo, con ID : %d\n", semID);

    //Semafori inizializzati!

    printf("################################################################\n"); 

        sleep(2);

    printf("Ti posso mostrare che tutto è andato a buon fine!\n"); 
    
    int pid=vfork(); 

        if(pid<0){
            perror("Errore vfork\n");
                exit(1);
        }


        if(pid==0){
            
            if(execlp("ipcs", "ipcs", NULL)<0){
                perror("errore exec\n"); 
                    exit(1);
            }
        }

    int status;

    wait(&status); 

    printf("Ho concluso il processo, %d, con stato: %d\n", pid, status);

    printf("##############################################################\n");

        sleep(2);


    printf("Avvio il processo di produzione e consumazione\n\n"); 

    //Modificando il numero sottostante, posso andare a modificare il numero di processi figli che genero!
    //In particolare, scelgo di "trasformare" i processi pari in consumatori e quelli dispari in produttori!

    

   
    for(int i=0; i<2; i++){

        srand(time(NULL));



        int pid1=fork();
           
            if(pid1<0){
                perror("Fork, non eseguita\n"); 
                    exit(1);
            }

            if(pid1==0){
              
                if(i%2==0){
                    //Il primo che viene eseguito è il consumatore, che subito effettua una wait sul semaforo, per controllare
                    //che il messaggio sia disponibile, siccome inizialmente non ho alcun messaggio, dopo la wait, il processo
                    //consumatore viene sospseso, viene ripreso solo dopo che il processo produttore effettua una signal sul semaforo
                    //che indica che il messaggio è stato prodotto
                    consumatore(buff, semID);
                        exit(0);
                }

                else{
                    //Il processo produttore è quello che viene eseguito subito dopo, come prima cosa fa una wait sul semaforo adibito a
                    //gestire la competizione tra i vari produttori, se presenti, se è il primo produttore, allora può produrre, altrimenti
                    //deve aspettare prima che un consumatore abbia consumato In questo modo può intervenire e modificare il valore della variabile!
                    //Per poi lasciare il posto ad un altro consumatore!
                    produttore(buff, semID);
                        exit(0);
                }
            }
    }




    for(int i=0; i<2; i++){
        wait(NULL); 
    }

    printf("Processo finito!\n"); 


    //Vado a eliminare i semafori e la memoria condivisa
    shmctl(shmID, IPC_RMID, NULL); 
    semctl(semID, 0, IPC_RMID);
   // semctl(semID, MESSAGGIO_DISPONIBILE, IPC_RMID);
}