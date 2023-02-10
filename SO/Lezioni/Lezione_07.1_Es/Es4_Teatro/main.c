//Definizione della funzione principale 
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <time.h>

#include "function.h"
#include "semafor.h"

int main(){
    //Specifica della memoria che contiene 80 posti!
    //Uso ftok, perchè deve essere condivisa tra più processi!
    key_t postiChiave = ftok(".", 'a'); 

    int postiID = shmget(postiChiave, DIM*sizeof(seduta), IPC_CREAT|0660); 

    seduta* posti = (seduta*) shmat(postiID, NULL, 0);

    printf("Sedute create!\n"); 

    printf("Inizializzo le sedute!\n"); 

        for(int i=0; i<DIM; i++){
            posti[i].stato=LIBERO;
        }

    printf("Sedute inizializzate!\n"); 

    //Definisco la variabile della disponibilità, inizializzata a DIM! 
    //La imposto usando una chiave privata, poichè sarà una variabile condivisa solo tra i processi!

    key_t dispChiave = ftok(".", 'c');

    int dispID=shmget(dispChiave, sizeof(int), IPC_CREAT|0660);

    int* disp = shmat(dispID, NULL, 0); 

    printf("Disponibilità di memoria creata, Inizializzo\n"); 

        (*disp)=DIM; 

    printf("Disponibilità di posti: %d\n", *disp);


    printf("Procedo con la creazione del semafori!\n"); 

    //Uso sempre la chiave ottenuta con ftok!
    
    key_t semaforChiave = ftok(".", 'b'); 

    //Devo ottenre l'id del semaforo

    int semID = semget(semaforChiave, 4, IPC_CREAT|0660);

    //Inizializzo i semafori al loro valore

    //I mutex li posso inizializzare ad 1, poichè il primo che arriva può direttamente accedere!
    semctl(semID, MUTEX_POSTO, SETVAL, 1);
    semctl(semID, MUTEX_DISPONIB, SETVAL, 1);

    //Inizializzo anche quello che controlla che ci siano posti prenotati
    //Se non ci sono posti prenotati, il visualizzatore si blocca e attende che ci sia almeno un elemento!
    semctl(semID, ATTENDERE, SETVAL, 0);

    semctl(semID, PROSEGUO, SETVAL, 1);

    printf("Semafori inizializzati!\n"); 
    printf("Ho un id uguale a: %d\n", semID);

    printf("##################################################\n"); 

    //A questo punto, vado a generare i vari processi per la prenotazione!

    //Genero anche il processo che ha il compito di andare a visualizzare 
    pid_t pidd=vfork();

        if(pidd==0){
            printf("Ti genero il visualizzatore\n"); 
            execl("vedo", "./vedo", NULL);
        }



    for(int i=0; i<NUM_PROCESSI; i++){
        int pid = fork(); 
            if(pid==0){
                srand(getpid()*time(NULL));
                cliente2(posti, disp, semID); 
                exit(0);
                                
            }
    }


    //Il main attende che tutti i processi siano conclusi, compreso il visualizzatore!
    for(int i=0; i<NUM_PROCESSI + 1; i++){
       wait(NULL);
    }

    printf("#######################################################\n");

    printf("Ti mostro chi è riuscito a prenotare un posto!\n");

    //Mostro i processi che sono riusciti a prenotare i posti!
    for(int i=0; i<DIM; i++){
        sleep(1);
        printf("Ti mostro il posto: %d, occupato da: %d\n", i+1, posti[i].ID_cliente);
    }


    printf("Applicazione in chiusura\n");

    //Vado ad eliminare tutte le memorie!
    semctl(semID, 0, IPC_RMID);
    shmctl(postiID, IPC_RMID, 0); 
    shmctl(dispID, IPC_RMID, 0); 


}