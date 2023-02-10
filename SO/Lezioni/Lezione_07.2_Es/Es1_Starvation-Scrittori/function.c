//Specifica delle funzioni
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "semafor.h"
#include "function.h"

//Comincio con la specifica dello scrittore
void scrittore(buffer* mem, int semID){

    //Il produttore, effettua una wait sul semaforo di sinconizzazione
    //In questo modo blocco i lettori e anche gli scrittori, facendo una wait sul semaforo che si occupa di ciò!
    wait_sem(semID, SYNCH); 

            //Voglio produrre il mio messaggio
                mem->messaggio=rand()%39532+1;

                sleep(1);
                printf("Ho prodotto il valore: %lu\n", mem->messaggio);

    //Sblocco il semafoto
    signal_sem(semID, SYNCH);     

} 




void lettore(buffer* mem, int semID){

    //La gestione del lettore è leggermente più complessa
    //come primo passo, devo andare ad incrementare il valore della variabile del numero di lettori!
    wait_sem(semID, MUTEXL); 

        //A questo punto posso cambiare la variabile 
        mem->numLettori++; 
    
        //A QUESTO PUNTO, POSSO VEDERE SE BISOGNA ESCLUDERE GLI ALTRI PRODUTTORI!
        if(mem->numLettori==1){
            //printf("Sono il primo lettore, ti escludo gli scrittori!\n"); 
            //In questo caso, quando uno scrittore arriva subito dopo un lettore, quando fa la wait sul semaforo, verrà 
            //bloccato, poichè c'è già un altro processo che sta "occupando" la memoria!
            wait_sem(semID, SYNCH);
        }
    
    //Posso quindi lasciare questa sezione critica, in modo da fare posto ad un altro lettore
    signal_sem(semID, MUTEXL);
    sleep(1);
    //In questo caso, posso quindi andare a leggere!
    printf("Valore letto: %ld, restano %d lettori\n", mem->messaggio, mem->numLettori);

    //Comincia la fare di conclusione della lettura, devo fare le medesime cose, della fare di inizio lettura 

    //wait sul semaforo della mutua esclusione tra lettori
    wait_sem(semID, MUTEXL); 

        //modifico il numero di lettori
        mem->numLettori--; 

        //controllo se sono l'ultimo lettore
        if(mem->numLettori==0){
            //printf("Sono l'ultimo lettore, quindi sblocco gli scrittori!\n"); 
            signal_sem (semID, SYNCH);
        }

    //Libero anche gli altri lettori
    signal_sem(semID, MUTEXL);


}
