//Definizione della funzione main!
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <errno.h>

//Includo anche la libreria dei miei file
#include "function.h"

int main(){
    //Definisco l'id della cosa dei messaggi
    //Ovviamente specifico i flag, in modo che la coda venga creata, se non presete, assegnandogli i permessi necessari
    int queue  = msgget(IPC_PRIVATE, IPC_CREAT|0660);

    if(queue<0){
        perror("Errore creazione coda\n"); 
            exit(1); 
    }

    //A questo punto, ho fatto tutto quello che dovevo fare, devo solo andare a creare i processi che mi interessano
    pid_t pid=fork();

    char m[100];

    if(pid==0){

            printf("Sono il figlio produttore: %d\n", getpid());

            //Creo 10 messaggi da andare ad inserire nella coda!
            for(int i=1; i<=10; i++){
                //Uso una funzione particolare, che mi permette di andare a inserire un certo valore all'interno di una stringa
                //Inserisce la stringa che gli ho inserito all'interno del messaggio
                sprintf(m, "Stringa %d", i); 

                usleep(100);

                //invoco la funzione di produzione, che mi inserisce il messaggio nella coda!
                produttore(queue,m); 
            }   

            exit(0);
    }

    //Creo il figlio consumatore
    pid=fork(); 

    if(pid==0){
        printf("Sono il figlio consumatore: %d\n", getpid());
        sleep(1);
        //Il figlio consumatore, deve andare a leggere il messaggio nella coda!
        for(int i=0; i<10; i++){
            //Invoco quindi la funzione in base al numero di messaggi che vado a scrivere nella coda
            constumatore(queue);
        }

        exit(0);

    }


    //Il padre attende la teriminazione dei figli dei figli!

    int status;

    for(int i=0; i<2; i++){

        printf("È terminato il figlio: %d\n", wait(&status)); 
        if(!WIFEXITED(status)){
            perror("Terminato in malo modo!\n"); 
        }

    }



    //Devo andare a rimuovere la coda dei messaggi!
    msgctl(queue, IPC_RMID, NULL);

}