//All'interno di unix, posso fare in modo che un processo vada ad invocare un altro processo, in generale usando la funzione exec
//exec, viene anche definta come "SOSTITUZIONE DI CODICE", dopo la chiamata, infatti, ho che il processo che esegue è sempre lo steso 
//Infatti la funzione non va a modificare il pid del processo figlio!

//Questo indica che con exec, il processo: 
//Mantiene la stessa user area e lo stack del kernel
//tuttavia ha una nuova area dati e una nuova area heap
//La memoria viene sovrascritta con nuovi valori, in base a quelli che occorrono al processo chiamato
//Inoltre, al codice del processo figlio, viene sovrapposto quello del processo chiamato!

//In generale, nella maggior parte dei casi, viene eseguita una exec subito dopo una fork, essendo che fork è una chiamata 
//molto dispendiosa di risorse, poichè effettua una copia dei dati del programma, allora si ha che posso usare anche una differente chiamata 
//la vfork, che esegue una fork, subito seguita da una exec, spesso chiamata anche light fork

//Importante considerare che esistono differenti implementazioni della funzione exec in base ai parametri che le vengono passati!


#include <stdio.h>
#include <stdlib.h>

//Per usare il comando exec vado ad includere questa libreria!
#include <unistd.h>

//Uso questa libreria per la definizione della funzione perror!
#include <errno.h>

#include <wait.h>

int main(){

    //Voglio fare in modo che un processo figlio, utilizzi il comando ls sulla scell!

    int pid; 

    pid=fork();

    if(pid<0){
        perror("Sono spiacente ma la funzione non è andata a buon fine!\n");
        exit(1);
    }
    

    if(pid==0){
        printf("Eseguo il comando ls\n");

        //In questo caso uso la funzione execl, che mi permette di eseguite un programma specificando il suo percorso
        //Definisco poi il nome del comando "ls" e ci aggiungo anche altri un altro argomento che è il flag "-l"
        //Alla fine della serie degli argomenti devo andare a speficiare il terminatore che è il comando NULL!
        if(execl("/bin/ls", "ls", "-l", NULL)<0){
            //Ho effettuato un controllo, in quanto la funzione restituisce un valore negativo se ci sono stati errori all'atto dell'esecuzione!
            perror("La funzione di exec non è andata a buon fine\n");
            exit(1);
        }
    }

    if(pid>0){
        int status; 

        //Faccio in modo che il padre possa aspetti il figlio!
        wait(&status);

        if(WIFEXITED(status)){
            printf("Il processo ha terminato perfettamente!\n");
        }

    }




}