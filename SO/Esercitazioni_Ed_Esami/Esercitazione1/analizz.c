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

    printf("Semafori ottenuti\n");

    printf("-------------------------------------\n");

    //Definisco un buffer in cui salvare la mia stringa
    char buffer[dimensione];

for(int i=0; i<VOLTE; i++){

    sleep(3);

    inizio(semID, p); 

        strcpy(buffer, stringa);

    //Sblocco gli scrittori
    fine(semID, p); 

        //Inverto l'ordine della mia stringa!

    char salvo; 

    int i=0;
    int j=dimensione-1; 


    printf("Ho ottenuto la stringa %s, te la inverto!\n", buffer);


    while((i<(dimensione/2)-1) && (j>(dimensione/2)-1)){
        salvo=buffer[i]; 
        buffer[i]=buffer[j]; 
        buffer[j]=salvo;
        i++;
        j--;
    }


    sleep(1);
    printf("Ho ottenuto la stringa finale: %s\n", buffer);
    printf("------------------------------------------------\n");

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