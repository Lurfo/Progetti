#include <stdio.h>

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "function.h"
#include "semafor.h"




void produttore(int* buffer, int semID){
  
    //La prima cosa che deve effettuare il produttore è una wait sul semaforo che controlla se la memoria è disponibile
    printf("Sono il produttore che Esegue la Wait!\n");
    wait_sem(semID, SPAZIO_DISP);
    

    printf("Sono il Produttore, sbloccato, vado a definire il tuo messaggio!\n");


    //A questo punto sono nella sezione critica, vado dunque a modificare il messaggio contenuto nel buffer
    
    //Imposto il seed del valore random!
    

    *buffer=rand()%100;

        printf("Ho impostato il valore:  %d\n", *buffer);


    printf("-------------------------------------------\n");
    

    //Ho quindi impostato il valore nel buffer e posso andare a sbloccare i consumatori eventualmente bloccati
    signal_sem(semID, MESSAGGIO_DISPONIBILE);
    
}





void consumatore(int* buffer, int semID){


    //Il consumatore, effettua una signal sul semaforo che indica che il messaggio sia disponibile!
    printf("Consumatore, vedo se posso consumare!\n\n");
    wait_sem(semID, MESSAGGIO_DISPONIBILE);

    printf("Sono il consumatore! Posso consumare\n");


    //Il consumatore ha accesso alla memoria e dunque può leggere il semaforo!
   
    printf("Il messaggio nella memoria è: %d\n", *buffer);
        printf("Lacio il posto al prossimo produttore!\n");

    printf("-------------------------------------------------\n");
    
  
    //effettuo quindi una signal sul semaforo che blocca i produttori!
    //Serve a segnalare che il prossimo produttore può accedere alla memoria!
    signal_sem(semID, SPAZIO_DISP);

}   