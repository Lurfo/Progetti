#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/msg.h>

#include "auth.h"

void controlloPid(pid_t);

int main() {

    printf("Creazione code di messaggi\n");

    //Essendo che le code sono condivise tra dei processi padre-figlio, allora uso IPC_PRIVATE come chiave
    int id_coda_auth_req = msgget(IPC_PRIVATE, IPC_CREAT|0660);

    int id_coda_auth_resp = msgget(IPC_PRIVATE, IPC_CREAT|0660);
    
    int id_coda_elab_req = msgget(IPC_PRIVATE, IPC_CREAT|0660);
    
    int id_coda_elab_resp = msgget(IPC_PRIVATE, IPC_CREAT|0660);


    pid_t pid;


    printf("Avvio processo autenticatore\n");

    /* TBD: Avvio processo (funzione Auth) */
    pid = fork();

    controlloPid(pid); 

    if(pid==0){
        Auth(id_coda_auth_req, id_coda_auth_resp);
        exit(0);
    }



    printf("Avvio processo server\n");

    /* TBD: Avvio processo (funzione Server) */
    pid = fork(); 

    controlloPid(pid); 

    if(pid==0){
        Server(id_coda_elab_req, id_coda_elab_resp, id_coda_auth_req, id_coda_auth_resp);
        exit(0);
    }


    printf("Avvio processo client autenticato\n");

    /* TBD: Avvio processo (funzione ClientAuth) */
    pid = fork(); 

    controlloPid(pid); 

    if(pid==0){
        ClientAuth(id_coda_auth_req, id_coda_auth_resp, id_coda_elab_req, id_coda_elab_resp); 
        exit(0);
    }
    

    printf("Avvio processo client non-autenticato\n");

    /* TBD: Avvio processo (funzione ClientNonAuth) */

    pid = fork(); 

    controlloPid(pid);

    if(pid==0){
        ClientNonAuth(id_coda_elab_req, id_coda_elab_resp);
        exit(0);
    }

    printf("Attesa terminazione processi\n");

    /* TBD: Attesa terminazione */
    for(int i=0; i<4; i++){
        wait(NULL);
    }


    printf("Rimozione code di messaggi\n");

    /* TBD: Rimozione code */ 
    msgctl(id_coda_elab_req, IPC_RMID, NULL);

    msgctl(id_coda_elab_resp, IPC_RMID, NULL);    

    msgctl(id_coda_auth_req, IPC_RMID, NULL);

    msgctl(id_coda_auth_resp, IPC_RMID, NULL);

    
    return 0;
}

void controlloPid(pid_t pid){
    if(pid<0){
        perror("Errore nella fork\n"); 
            exit(1);
    }
}