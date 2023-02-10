//Con questo programma voglio fare in modo che esso esegue il programma definito nella lezione 3 che effettua delle operazione su
//un array di numeri!

#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#include <errno.h>

int main(){
    int pid;

    printf("Ti lancio subito il programma\n");

    pid=fork();

    //Istruzione di controllo del risultato della funzione fork!
    if(pid<0){
        perror("Non sono riuscito ad eseguirela fork!\n");
        exit(1);
    }

    if(pid==0){

        printf("Sono il processo figlio, con pid: %d. Eseguo il tuo programma!\n", getpid());

        //Uso in questo caso la funzione execl, poichè gli passo il nome del file e assume come path che esso sia nella 
        //cartella dove è presente anche il file main!
        if(execl("start", "start", NULL)<0){
            perror("La funzione exec non è andata a buon fine!\n");
            exit(1);
        };

    }

    if(pid>0){

        int stat; 

        //Facico in modo che il padre aspetti il figlio!
        wait(&stat); 

        //Eseguo un controllo sullo stato di terminazione del figlio!
        if(WIFEXITED(stat)){
            printf("Il figlio ha terminato correttamente!\n");
        }

        printf ("Sono dinuovo il padre\n");

    }

}