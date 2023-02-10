#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

#include "header.h"

#define NUM_CLIENT 2

int main() {

    //Ottento la chiave della coda di messaggi
    key_t kMess = ftok(PATH, CHAR);

        if(kMess<0){
            perror("Errore ftok main\n"); 
                exit(1);
        }

    int id_coda = msgget(kMess, IPC_CREAT|0660); 

        if(id_coda<0){
            perror("Errore msgget main\n"); 
                exit(1);
        }

    printf("[MAIN] Chiave: %d, Id: %d\n", kMess, id_coda);

    pid_t pid;

    int ret;

    for(int i=0; i<NUM_CLIENT; i++) {

        /* TBD: Creare i processi figli "client", e
         *      fargli eseguire il programma "main_client"
         */

        pid = vfork(); 

            if(pid<0){
                perror("Errore vfork client\n"); 
                    exit(1);
            }

            if(pid==0){
                
                ret  = execl("./main_client", "main_client", NULL); 

                    if(ret<0){
                        perror("Errore exec client\n"); 
                            exit(1);
                    }

            }


    }


    /* TBD: Creare i processi figli "client", e
     *      fargli eseguire il programma "main_client"
     */

    pid = vfork(); 

        if(pid<0){
            perror("Errore vfork del server\n"); 
                exit(1); 
        }

        if(pid==0){

            ret = execl("./main_server", "main_server", NULL); 
                
                if(ret<0){
                    perror("Errore execl\n"); 
                        exit(1);
                }

        }


    /* TBD: Attendere la terminazione dei processi figli */

    int stato; 

    for(int i=0; i<NUM_CLIENT+1; i++){
     
        pid = wait(&stato);

        printf("Terminato processo %d, con stato: %d\n", pid, stato);

    }

    /* TBD: De-allocare la coda di messaggi */

    //Elimino la coda di messaggi con msgctl
    msgctl(id_coda, IPC_RMID, NULL);

    return 0;

}
