#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"


void generator(int queue){
    //Il generatore deve inviare due messaggi 

    srand(getpid()*time(NULL));

    //Definisco il messaggio
    Messaggio mess;

    //Imposto il tipo, che non deve variare
    mess.type=TYPE_GENERATOR;

    //Tramite il for, posso inviare il numero di messaggi necessari
    for(int i=0; i<NUM_INVII; i++){

       //printf("Comincio con la creazione del messaggio\n");

        //Come primi passaggi, vado ad impostare i valori del messaggio
        //Imposto i valori casuali nella stringa
        for(int j=0; j<MAX; j++){
            //Posso dunque impostare valori casuali nella stringa 
            mess.string[j]= 'a' + rand()%26;
        }

            //printf("Stringa creata\n");

            //Imposto il carattere terminatore alla stringa
            mess.string[MAX]='\0';

        //Imposto i due numeri casuali da 0 a 9
        for(int k=0; k<2; k++){

            mess.arr[k]=rand()%1001;
        }

            //printf("Numero creati\n");

        //Imposto la variabile intera come nulla
        mess.var=0;

    /*    printf("*******************\n");

        printf("~Generatore, invio\n");
        printf("~Messaggio da: %ld\n", mess.type);
        printf("~Stringa: %s\nValori Array: %d, %d\nValore Finale: %d\n", mess.string, mess.arr[0], mess.arr[1], mess.var);
    */    


        //A questo punto, posso inviare il messaggio
        if(msgsnd(queue, (void*) (&mess), SIZE, 0)<0){
            perror("Errore send Generatore\n"); 
                exit(1);
        }


    }

    //printf("~Messaggi inviato\n");


}



void filtro(int queue){

    //Definisco la funzione di filtro
    Messaggio mess;

    int cont=0;
    
    //Controllo la lista per quante volte i processi inviano dei messaggi
    for(int i=0; i<NUM_GENERATORI*NUM_INVII; i++){

        //In particolare, posso fare in modo che il processo filtro, faccia una receive bloccante
        //questo perchè il processo filtro deve sempre controllare tutti i messaggi che gli arrivano dal processo generatore
        msgrcv(queue, (void*)(&mess), SIZE, TYPE_GENERATOR, 0);

        //printf("*Ho trovato il messaggio\n");

        //Cerco il carattere x nel messaggio

        if(strchr(mess.string, 'x')!=NULL){

            //Se sono qui vuol dire che ho incontrato una stringa con la x
            //Cambio il tipo del messaggio e lo invio al prossimo
            mess.type=TYPE_FILTRO;

            //Posso quindi inviare il messaggio
            msgsnd(queue, (void*) (&mess), SIZE, IPC_NOWAIT);

            //cont++;

            //printf("*Messaggio passato attraverso il filtro: %d\n", cont);

        }
    }


}





void checksum(int queue){

    Messaggio mess;

    sleep(3); 

    //Il campo checksum, deve andare a controllare la lista dei messaggi per almeno 6 volte
    
    //Controllo la lista per almeno 6 volte
    for(int i=0; i<NUM_GENERATORI*NUM_INVII; i++){
        
        sleep(1); 

        if(msgrcv(queue, (void*)(&mess), SIZE, TYPE_FILTRO, IPC_NOWAIT)>0){
        
          /*  
            printf("++++++++++++++++++++++\n");
            printf("+Trovato messaggio\n");
            printf("Stringa: %s\n", mess.string);

          */
            //printf("+Ho i valori: %d, %d\n", mess.arr[0], mess.arr[1]);
            
            //Se arrivo qui, ho trovato il messaggio, effettuo quindi la somma
            mess.var = mess.arr[0] + mess.arr[1];

            //printf("+Valore finale: %d\n", mess.var);
            
            for(int j=0; j<MAX; j++){
                //Faccio quindi la somma dei caratteri
                mess.var+= (int) mess.string[j];
            }

            //printf("+Finita somma: %d\n", mess.var);

            //Modifico il tipo del messaggio
            mess.type=TYPE_CHECKSUM;

            //Spedisco nuovamente il messaggio
            msgsnd(queue, (void*)(&mess), SIZE, 0);

            //printf("+Messaggio inviato\n");
        }

    }



}




void visualizzatore(int queue){
    
    Messaggio mess;

    int cont=0;


    sleep(4);

    //Eseguo sempre il controllo su tutti i messaggi
    //Eseguo il controllo per 6 volte
    for(int i=0; i<NUM_GENERATORI*NUM_INVII; i++){

        sleep(1);

        if(msgrcv(queue, (void*)(&mess), SIZE, TYPE_CHECKSUM, IPC_NOWAIT)>0){
            
            cont++;

            //Se sono qui, vuol dire che ho ricevuto il messaggio
            printf("++++++++++++++++++++++++++\n");
            printf("Ho ottenuto il messaggio: %ld\n", mess.type);
            printf("Stringa: %s\nValori Array: %d, %d\nValore Finale: %d\n", mess.string, mess.arr[0], mess.arr[1], mess.var); 
        }

    }

    printf("Mi sono arrivati %d messaggi\n", cont); 


}