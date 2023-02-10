//Specifica delle funzioni

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>


#include "function.h"
#include "semafor.h"


//Funzioni ausiliarie 

void inizioLettura(buffer* mem, int semID){

    wait_sem(semID, MUTEXL); 

        //Aumento il valore 
        mem->Num_Lettori++;
        
        //Controllo se sono il primo
        if(mem->Num_Lettori==1){
            printf("Blocco gli scrittori\n");
            //Se sono il primo, blocco gli scrittori!
            wait_sem(semID, SYNCH);
        }

    signal_sem(semID, MUTEXL);

}



void fineLettura(buffer* mem, int semID){

    //Decremento il numero di lettori 
    wait_sem(semID, MUTEXL); 

        mem->Num_Lettori--; 

        //Controllo se sono l'ultimo 
        if(mem->Num_Lettori==0){
            printf("Sblocco gli scrittori\n");
            //Sblocco gli scrittori
            signal_sem(semID, SYNCH);
        }

    //Posso concludere
    signal_sem(semID, MUTEXL);
}






void inizioScrittura(buffer* mem, int semID){

    //Incremento il numero della variabile num_scrittori
    wait_sem(semID, MUTEXS);
        
        mem->Num_Scrittori++;
    
        //Controllo se sono il primo 
        if(mem->Num_Scrittori==1){
            printf("Blocco i lettori\n");
            //Se sono il primo, blocco i lettori
            wait_sem(semID, SYNCH);
        }


    //Esco dalla sezione critica per la variabile Num_Scrittori
    signal_sem(semID, MUTEXS);

    //Posso accedere alla zona di memoria e andare a scrivere il messaggio
        //Accedo in mutua esclusione al valore
    wait_sem(semID, MUTEX);

}


void fineScrittura(buffer* mem, int semID){

    signal_sem(semID, MUTEX); 

    //A questo punto devo concludere la scrittura, andando a decrementare il valore del numero di scrittori presenti
    wait_sem(semID, MUTEXS); 

        mem->Num_Scrittori--; 

        //Controllo, se sono l'ultimo scrittore, libero i lettori
        if(mem->Num_Scrittori==0){
            printf("Sbocco i lettori\n");
            signal_sem(semID, SYNCH);
        }

    signal_sem(semID, MUTEXS);

}


//Funzione dello scrittore
void scrittori(buffer* mem, int semID){
    
    inizioScrittura(mem, semID);
        
        mem->numero=rand()%1000 +1;

        sleep(1);
        printf("Ho prodotto il valore: %lu\n", mem->numero);
    
    //Esco dalla sezione critica
    fineScrittura(mem, semID);

}




//Per i lettori, il discorso è molto simile, devo compitere le azioni medesime!
void lettori(buffer* mem, int semID){
    //Appena arrivo, aggiorno il numero di lettori presenti
    //Sempre in mutua esclusione, altrimenti potrebbero crearsi errori tra i vari lettori che vogliono modificare 
    //allo stesso momento la variabile!
    inizioLettura(mem, semID);

    sleep(1);
    //Le lettura, posso anche non farla in mutua esclusione poichè i lettori, possono accedere contemporaneamente alla risorsa
    printf("Ho letto il valore: %lu, num lettori: %d\n", mem->numero, mem->Num_Lettori);

    //La fase di fine lettura e simile a quella iniziale
    fineLettura(mem, semID);
}