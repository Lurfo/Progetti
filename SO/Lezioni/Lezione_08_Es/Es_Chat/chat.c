//Definisco un processo che funziona come una chat tra due utenti, importo uno scambio di messaggi su due code distinte
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <errno.h>

#include "function.h"

//La funzione prende dei parametri di ingresso dalla console di comando, poichè deve impostare le due code
int main(int argc, char* argv[]){

    if(argc==1){
        perror("Argomenti insufficienti nella chiamata a funzione\n");
        printf("Uso: %s, <parametro> <parametro>\n", argv[0]);
            exit(0);
    }

    printf("Hai scelto come parametri: %s %s\n", argv[1], argv[2]);

    int a =  atoi(argv[1]);
    int b =  atoi(argv[2]);

    printf("a=%d\n", a); 
    printf("b=%d\n", b);

    //Come prima cosa, ottengo la chiave delle due code!
    key_t k_inv = ftok(".", a);
    key_t k_ric = ftok(".", b);

    printf("Chiave invio: %d\n", k_inv);
    printf("Chiave ricezione: %d\n", k_ric);

    if(k_ric<0 || k_inv<0){
        perror("Errore ftok\n");
            exit(1);
    }

    //Ottengo gli id per le due code
    int queue_inv = msgget(k_inv, IPC_CREAT|0660); 
    int queue_ric = msgget(k_ric, IPC_CREAT|0660); 

    printf("Desc invio: %d\n", queue_inv);
    printf("desc ric: %d\n", queue_ric);

    if(queue_inv<0 || queue_ric<0){
        perror("Errore msgget\n");
            exit(1);
    }

    //A questo punto devo effettuare due fork per andare a generare i processi che ricevono e inviano messaggi

    pid_t pid;

    for(int i=0; i<2; i++){
     
        pid=fork(); 

        //Effettuo un controllo sulla fork
        if(pid<0){
            perror("Errore nella fork\n");
                exit(1);
        }

        //Se sono il figlio, ho due strategie
        if(pid==0){
            
            //i pari faccio partire il processo che invia i messaggi
            if(i%2==0){
                printf("Avvio di quello che invia: %d\n", getpid());
                invio(queue_inv);
            }

            //i dispari faccio partire il processo che riceve i messaggi
            if(i%2!=0){
                printf("Avvio di quello che riceve: %d\n", getpid());
                ricezione(queue_ric);
            }

            exit(0);
        }
    }

    //Il processo padre, attende che i figli siano completati prima di procedere
    for(int i=0; i<2; i++){
        printf("Si è concluso il processo %d\n", wait(NULL));
    }

    //Vado a rimuovere le due code di messaggi
    msgctl(queue_inv, IPC_RMID, NULL);
    msgctl(queue_ric, IPC_RMID, NULL);



}