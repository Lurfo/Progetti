//Definizione del processo generatore!
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <time.h>

//Includo l'header
#include "header.h"

//Mi definisco la funzione main!
//Il main, può prendere in ingresso determinati parametri che possono essere definiti successivamente!
int main(int argc, char* argv[]){

    srand(getpid()*time(NULL));

    int n = atoi(argv[1]);

    printf("Sono il generatore %d, genero i messaggi\n", n);


    Messaggio mess;

    //Ottengo la chiave della coda di messaggi
    key_t kMsg = ftok(PATH, CHAR);

    if(kMsg<0){
        perror("Erroe della ftok del generatore\n"); 
            exit(1);
    }


    //Id della coda
    //Metto 0 come flag perchè la coda è stata creata già
    int idMsg = msgget(kMsg, 0);

    if(idMsg<0){
        perror("Errore msgget generatore\n");
            exit(1);
    }

/*
    printf("*Chiave della coda: %d\n", kMsg); 
    printf("*Id della coda %d\n", idMsg);
*/
    
    //Ho ottenuto la coda, posso eseguire le operaioni necessarie
    
    //Imposto il tipo, che non deve variare
    mess.type=TYPE_GENERATOR;

    //Tramite il for, posso inviare il numero di messaggi necessari
    for(int i=0; i<NUM_INVII; i++){

       //printf("*Comincio con la creazione del messaggio\n");

        //Come primi passaggi, vado ad impostare i valori del messaggio
        //Imposto i valori casuali nella stringa
        for(int j=0; j<MAX; j++){
            //Posso dunque impostare valori casuali nella stringa 
            mess.string[j]= 'a' + rand()%26;
        }

            
            //printf("*Stringa creata\n");

            //Imposto il carattere terminatore alla stringa
            mess.string[MAX]='\0';

        //Imposto i due numeri casuali da 0 a 9
        for(int k=0; k<2; k++){

            mess.arr[k]=rand()%10;
        }

            //printf("*Numero creati\n");

        //Imposto la variabile intera come nulla
        mess.var=0;

    /*
        printf("*******************\n");

        printf("*Generatore, invio\n");
        printf("*Messaggio da: %ld\n", mess.type);
        printf("*Stringa: %s\n*Valori Array: %d, %d\n*Valore Finale: %d\n", mess.string, mess.arr[0], mess.arr[1], mess.var);
    */ 


        //A questo punto, posso inviare il messaggio
        if(msgsnd(idMsg, (void*) (&mess), SIZE, 0)<0){
            perror("Errore send Generatore\n"); 
                exit(1);
        }


    }

    //printf("*Messaggi inviato\n");

  

}