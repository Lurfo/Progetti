//Definizione del main: 
//Impostazione della shm
//Impostazione del semaforo
//Impostazione della coda di messaggi
//Genero 3 processi Client e 3 Server
//Attesa della terminazione 
//Rimozione memoria e semaforo

#include <sys/wait.h>

#include "header.h"


#define NUM_CLIENT 3 
#define NUM_SERVER 3


int main(){

    //Impostazione della memoria condivisa, che contiene il buffer
    key_t kMem = ftok(PATH, CHAR_M); 

    int idMem = shmget(kMem, sizeof(Buffer), IPC_CREAT|0660); 

        if(idMem<0){
            perror("Errore idMem\n"); 
                exit(1);
        }

        //Eseguo shmat, per ottenre il riferimento della memoria condivisa
    Buffer *p = (Buffer *) shmat(idMem, NULL, 0);

    //Impostazione del semaforo
    key_t kSem  = ftok(PATH, CHAR_S);

    int idSem = semget(kSem, NUM_SEM, IPC_CREAT|0660); 

        if(idSem<0){
            perror("Errore idSem\n"); 
                exit(1);        
        }

        //RICORDA: Imposto il valore inziale del semaforo, usando la funzione semctl
    
    semctl(idSem, MUTEX, SETVAL, VAL);

    //Impostazione della coda di messaggi
    key_t kMess = ftok(PATH, CHAR_C); 

    int idMess = msgget(kMess, IPC_CREAT|0660); 

    printf("[MAIN] Ti mostro le risorse\n"); 
    printf("[MAIN] Memoria -> Chiave: %d, Id: %d\n", kMem, idMem); 
    printf("[MAIN] Semafori-> Chiave: %d, Id: %d\n", kSem, idSem);
    printf("[MAIN] Messaggi -> Chiave: %d, Id: %d\n", kMess, idMess);

    printf("[MAIN] Genero i processi\n");

    //Dunque, vado a generare i processi

    pid_t pid;

    for(int i=0; i<NUM_CLIENT; i++){
        pid = vfork(); 

            if(pid<0){
                perror("Errore vfork\n"); 
                    exit(1);
            }

            if(pid==0){

                if(execl("./client", "client", NULL)<0){
                    perror("Errore exec client\n"); 
                        exit(1);
                }
            }
    }

    for(int i=0; i<NUM_SERVER; i++){

        pid = vfork(); 

            if(pid<0){
                perror("Errore vfork client\n"); 
                    exit(1);
            }

            if(pid==0){

                if(execl("./server", "server", NULL)<0){
                    perror("Effore vfork server\n"); 
                        exit(1);
                }
            }
    }


    //Attendo la terminazione dei processi client e server 
    for(int i=0; i<NUM_CLIENT+NUM_SERVER; i++){
        wait(NULL);    
    }

    //Procedo con la rimozione della memoria condivisa, semaforo e code di mess
    semctl(idSem, 0, IPC_RMID); 

    shmctl(idMem, IPC_RMID, NULL); 

    msgctl(kMess, IPC_RMID, NULL);

    return 0;

}