//Definizione del main
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <wait.h>
#include <string.h>

#include "function.h"


int main(){
    //Inizializzo la coda dove inserisco i messaggi che devo produrre/consumare 
    int queue=msgget(IPC_PRIVATE, IPC_CREAT|0660);

    //Chiamo le funzioni che devono gestire le code per la sincronizzazione
    initService();

    //Posso dunque andare a creare i processi!

    pid_t pid = fork();

    if(pid==0){
        printf("Sono il figlio produttore %d\n", getpid()); 
        sleep(2);
        produttore(queue);

        exit(0); 
    }

    pid = fork(); 

    if(pid==0){
        printf("Sono il figlio consumatore %d\n", getpid()); 
        sleep(1);
        consumatore(queue); 

        exit(0);
    }

    
    //Il padre attende i figli
    for(int i=0; i<2; i++){
        printf("Si è concluso il figlio: %d\n", wait(NULL));
    }

    //Devo eliminare le code di messaggi di servizio e quella in cui ho conservato i messaggi da scambiare
    removeService(); 

    msgctl(queue, IPC_RMID, NULL);

}