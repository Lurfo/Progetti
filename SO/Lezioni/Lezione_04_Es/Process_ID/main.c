//Ogni processo viene identificato attraverso un Process Id, è possibile poter andare a conoscere il valore di tale ID
//Usando la funzione getpid(), inolte, siccome i processi sono organizzati in una gerarchia, posso anche conoscere il PID 
//del processo padre attraverso la funzione getppid()

//Bisogna considerare che il PID viene assegnato al processo dal KERNEL, quando questo viene creat, inoltre ho che il valore 
//del PID può assumere un valore, un intero, definito in un certo intervallo in base all'architettura che uso!

//Bisogna considerare che alcuni valori di PID sono VALORI RISERVATI! 
//Ad esempio il valore 0 è riservato allo scheduler
//Il valore 1 è riservato al Processo init ecc...

#include <stdio.h>

//Devo aggiungere queste due funzioni per usare le funzioni per ottenere il PID
#include <unistd.h>
#include <sys/types.h>

int main(){

    printf("Io sono il Processo figlio, con il PID: %d\n", getpid()); 

    printf("Il PID di mio padre è: %d\n", getppid());



}