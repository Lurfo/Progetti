//Definisco un programma al quale passare come argomenti il percorso ed il nome di alcuni file o di comandi da tastiera, in modo che 
//questo possa eseguitli!

#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <errno.h>

int main(int argc, char* argv[]){

    int pid; 

    printf("Sono il Processo padre: %d\n", getpid()); 

    //Genero un processo figlgio!
    pid=fork(); 
    
    //Struttura di controllo 
    if(pid<0){
        perror("Non sono ruscito a creare il processo\n"); 
        exit(1);
    }

    if(pid==0){
        printf("Sono nel processo figlio, eseguo il tuo programma!\n");

        //In questo caso posso usare la funzione execlp, poichè sto usando un programma che risiede già nei path di sistema, dunque sono
        //sicuro di non dover specificare tutto il percorso!
        //Imposto come massimo numero di parametri da poter passare alla funzione execlp 2 parametri!
        //Questi sono già impostati come valori di defualt dalla funzione di libreria!
        if(execlp(argv[1], argv[1], argv[2], argv[3], NULL)<0){
            perror("Non sono riuscito ad eseguire i tuo programma!\n"); 
            exit(1);
        };
    

    }

    int stat;

    wait(&stat);

    if(WIFEXITED(stat)){
        printf("Il tuo programma ha terminato correttamente l'esecuzione!\n");
    }

    printf("Sono di nuovo il padre, con il pid: %d\n", getpid());

}