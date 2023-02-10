#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/shm.h>


#include "semafor.h"


void inizio(int semID, insieme* val);
void fine (int semID, insieme* val);


int main(int argc, char* argv){
    

    //Ottengo i valori delle memorie
    
    //Definisco la memoria che contiene la struttura 

    int struttChiave = ftok(".", 'b'); 

    int struttID=shmget(struttChiave, sizeof(insieme), 0);

    insieme* p = shmat(struttID, NULL, 0); 

    int dimensione = p->dimensione;

     printf("Memoria con i valori ottenuta\n");

    //Ottengo la memoria che contiene la stringa

    int chiaveString  = ftok(".", 'a'); 

    int stringID = shmget(chiaveString, (dimensione)*sizeof(char), 0); 

    char* stringa = (char*) shmat(stringID, NULL, 0); 

    printf("Ho ottenuto la memoria che contiene la stringa\n"); 


    //Definisco i semafori di cui ho bisogno!

    int semChiave=ftok(".", 'c'); 

    int semID=semget(semChiave, 3, 0);

    printf("Ho ottenuto i semafori\n");

    printf("------------------------------------------\n");


    //Elaboratore, deve convertire il valore della stringa da maiuscolo a minuscolo, faccio in modo che salvi i valori poi
    //modifica quelli che ha salvato, senza toccare i valor in memoria!

    //Definisco una stringa della stessa dimensione di quella in memoria!
    char buff[dimensione]; 

for(int i=0; i<VOLTE; i++){

    sleep(3);

    //Comincio la lettura 
    inizio(semID, p);

        //Mi salvo nella mia stringa i valori della stringa contenuta nella memoria!
        //Uso la funzione di libreria
        strcpy(buff, stringa);

    //Posso concludere la lettura
    fine(semID, p);


        printf("Stringa acquisita, ti mostro i valori in maiuscolo\n");

        //Rendo tutte le lettere maiuscole
        for(int i=0; i<dimensione; i++){
            buff[i]-=32; 
            printf("%c; ", buff[i]);
        }
    
        printf("\n---------------------------------------\n");

}


    
}


void inizio(int semID, insieme* val){
    //Parte iniziale della lettura
    
    //Accedo alla variabile del numero di lettori 
    wait_sem(semID, MUTEX_L); 

        //Incremento numero di lettori 
        val->Num_Lettori++; 

        //Controllo se sono il primo
        if(val->Num_Lettori==1){
            //Se sono il primo blocco gli scrittori 
            wait_sem(semID, SYNCH);
        }

    //Esco dalla sezione, faccio arrivare altri lettori!
    signal_sem(semID, MUTEX_L);
}


void fine (int semID, insieme* val){

    //Ho una situazione molto simile alla fase di inizio lettura
    wait_sem(semID, MUTEX_L); 

        //Decremento il numero di lettori
        val->Num_Lettori--; 

        //Controllo se sono l'ultimo lettore 
        if(val->Num_Lettori==0){
            //Sblocco gli scrittori 
            signal_sem(semID, SYNCH);
        }

    //Esco dalla sezione, lascio uscire anche gli altri lettori!
    signal_sem(semID, MUTEX_L);
}
