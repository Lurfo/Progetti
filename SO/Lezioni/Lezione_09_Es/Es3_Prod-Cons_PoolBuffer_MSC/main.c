#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <errno.h>
#include <time.h>


#include "function.h"

#define NUM_PROD 10
#define NUM_CONS 10

int main(){

    //Mi definisco la mem condivisa
    int idMem = shmget(IPC_PRIVATE, sizeof(Buff), IPC_CREAT|0660); 

    if(idMem<0){
        perror("Errore shmget\n");
            exit(1);
    }

    //Ottengo il puntatore alla memoria condivisa
    Buff* p = (Buff*) shmat(idMem, NULL, 0); 

    if(p==(void*)-1){
        perror("Errore attach\n");
            exit(1);
    }

    //Posso quindi inizializzare il monitor
    init_monitor(&(p->m), 2);

    //Dunque inizializzo tutti i valori
    p->numero_liberi=DIM_MAX;
    p->numero_occupati=0;

    //Inizializzo il vettore di stato con tutti posti liberi
    for (int i=0; i<DIM_MAX; i++){
        p->stato[i]=LIBERO;
    }


    //A questo punto, non mi resta altro che procedere con la creazione dei processi!

    int val; 

    pid_t pid;

    for(int i=0; i<NUM_PROD; i++){
        pid=fork();

            if(pid<0){
                perror("Errore fork produttori\n");
                    exit(1);
            }

            if(pid==0){

                sleep(3);

                srand(getpid()*time(NULL));

                printf("Sono il produttore: %d\n", getpid()); 

                val = rand()%100+1;

                produttori(p, val);

                exit(0);
            }

    }


    for(int i=0; i<NUM_CONS; i++){
        pid=fork(); 
            
            if(pid<0){
                perror("Errore fork consumatori\n");
                    exit(1);
            }

            if(pid==0){
                printf("Consumatore: %d\n", getpid());


                printf("Sono il consumatore, ho preso un valore: %d\n", consuma(p));

                exit(0);

            }
    }

    //Il padre attende tutti i suoi figli 
    for(int i=0; i<NUM_CONS+NUM_PROD; i++){
        printf("Terminato il processo: %d\n", wait(NULL));
    }

    //Vado ad eliminare tutte le strutture
    remove_monitor(&(p->m));

    shmctl(idMem, IPC_RMID, NULL);



}