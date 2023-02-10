#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main (){

    char* c = (char*) malloc(15); 

    strcpy(c, "Sono il padre, primo"); 

    printf("Valore iniziale: %s\n", c);
    printf("Valore che puto: %p\n", c); 
    printf("Sono allocato in %p\n", &c); 


    pid_t pid; 

    pid = fork(); 

    if(pid<0){
        perror("Errore, fork\n"); 
            exit(1);
    }

    if(pid==0){
        printf("++++++++++++++++++++++++++++++\n");
        printf("Sono il figlio: %d\n", getpid()); 
        
        printf("Valore della stringa presa da mio padre: %s\n", c); 
        printf("Punta alla zona: %p\n",c);
        printf("Si trova alla zona: %p\n", &c);

        printf("Modifico valore alla stringa\n");
        strcpy(c, "Modificato dal figlio\n");
        printf("Il valore nuovo: %s", c);
        printf("++++++++++++++++++++++++++++++\n");

        exit(0);
    }

    wait(NULL); 

    printf("Sono di nuovo il padre: %d\n", getpid()); 
    printf("Valore che leggo ora: %s\n", c);
    printf("Valore che punto: %p\n", c); 
    printf("Sono allocato in %p\n", &c); 




}