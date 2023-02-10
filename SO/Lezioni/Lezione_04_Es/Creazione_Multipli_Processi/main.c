//Esempio di gestione della creazione dei processi. 
//Voglio che un padre generi un cero numero di figli, che quindi fanno capo al medesimo padre!

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>

#include <sys/wait.h>

int main(){
    
    int pid;

    printf("Sono il padre, con il pid: %d, ti mostro i miei figli:\n", getpid());

    //Voglio andare a genere 10 figli!
    for(int i=0; i<10; i++){
        //Non posso lasciare semplicemente questa fork in questo modo, potrei generare una FORK BOMB, vale a dire che ogni processo generato
        //continuerà con la produzione di altri processi figli, quindi non si genereranno solo 10 processi figli, ma molti di più
        //fino, ad andare ad occupare moltissmo spazio in memoria
        pid=fork();

        //Devo quindi impostare un controllo, in modo da impedire che il processo figlio generi a sua volta altri processi
        if(pid==0){
            //In questo caso sono nel processo figlio, dunque imposto il valori di conteggio direttamente uguale, in questo caso
            //a 10, in modo che non viene eseguito nuovamente il for!
            printf("Sono il figlio numero %d, con il pid: %d, con il padre: %d\n", i+1, getpid(), getppid()); 
            i=10; 
        }

        
    }

    //Faccio in modo che solo il padre possa eseguire queste istruzioni!
    if(pid>0){
        //Voglio però che il padre veda ad aspettare TUTTI i suoi figli, devo quindi andare ad impostare un while, con il quale il
        //padre attenda che tutti i suoi figli terminino il loro compito!
        
        //Ricordando che wait restituisce il valore del pid del processo che è terminato!
        //Inoltre imposto il NULL come condizione, poichè non mi interessa conoscere se il figlio ha terminato correttamente la sua
        //esecuzione o si è arrestato in modo anomalo!
        while(wait(NULL)>0);        

        printf("Sono ancora il padre: %d, tutti i miei figli hanno termianto!\n", getpid());


    }




}