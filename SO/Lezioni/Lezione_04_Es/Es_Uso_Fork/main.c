#include <stdio.h>

//Per usare la funzione fork, includo
#include <sys/types.h>
#include <unistd.h>
//Libreria per exit
#include <stdlib.h>

//Libreria che mi occorre per usare la system call wait!
#include <sys/wait.h>

//La funzione Fork è quella che permette di "creare" nuovi processi. Essa è una funzione molto costosa: 
//Infatti, questa crea una copia esatta del processo padre, ho una dupicazione!
//Questo vuole dire che il figlio eredita: 
// L'area dati globale, Lo stack, l'area heap, condivdono solo l'area testo!
//I due processi operano su zone di memoria differenti: dunque tutte le modifiche apportate da uno dei due, riguarda solo le
//proprie variabili!

//Il processo figlio, eredita anche gli stessi registri dal processo padre, compreso il PC, dunque il processo esegue: 
//Dall'istruzione subito successiva alla fork!

//Per comprendere se sto usando il padre o il figlio, la fork restituisce un valore: 
// 0 -> Sono nel contesto del figlio
// >0 -> Sono nel contesto del padre 
// -1 -> Ho avuto un errore, ad esempio non ho abbastanza spazio per allocare un muovo processo!

int main(){

    int pid = fork();

    
    if(pid==-1){
        printf("È accaduto un errore durante la fork!\n"); 
        //Exit, una systemcall che mi permette di andare a terminare il programma in caso di errore
        exit(1);
    }

    if(pid==0){
        printf("Sono nel processo figlio, con il pid: %d\n", getpid());
        printf("Mio padre è: %d\n", getppid());

        /*
        Lascio questa area commentata, per far vedere come funziona il valore della funzione wifexited, definita sotto
        int a[1];

        printf("Valore di un numero che non devo conoscere: %d\n", a[35858]);*/

        //Pongo un istruzione di exit quando voglio che il figlio concluda il suo compito!
        exit(1);
        //Importante è il valore che inserisco nella funzione exit:
        //Il valore 0 indica che la funzione si è conclusa volontariamente: mi dice che ha eseguito tutto quello
        //che doveva fare
        //Il valore =0, indica che si è arrestata a causa di un errore inaspettato o aspettato!

        //Se non dovessi mettere la funzione di exit, il figlio continua a seguire le istruzioni dopo gli if che ho inserito!
        //Che magari sono istruzioni che vorrei far eseguire al padre!

    }

    if(pid>0){
       
        //Uso la Sistem Call Wait per aspettare prima il completamento del figlio
        //Utilizzo questo intero come segnalibro, per andare a vedere il valore che viene definito dalla funzione wait
        int prova;

        //La funzione wait restituisce come valore il pid del processo che ho atteso!
        printf("È appena terminato il figlio, con il pid: %d\n", wait(&prova));

        //Inoltre pid scrive un valore nall'interno di prova, che posso andare a vedere usando un altra funzione chiamata
        //WIFEXITED, restiuisce come valore "true", se il figlio è terminato in modo corretto!
        if(WIFEXITED(prova)){
            printf("Il figlio è terminato correttamente!\n");
        }

        //Se tolo il commento all'istruzione sopra, dove provo ad accedere ad una locazione dell'array, vedo che verrà eseguita
        //questa istruzione, questo indica che WIFEXITED(), ha restituito il valore FALSE, dunque il processo non è terminato correttamente
        //(Cosa che è scontata dal fatto che stavo provando ad accedere ad una locazione di memoria che non gli appartiene!)
        if(!WIFEXITED(prova)){
            printf("Il processo figlio non è terminato correttamente\n");
        }

       
        //printf("Sono il padre di: %d\n", pid);
        printf("Io ho il pid: %d\n", getpid());

    }

    //Voglio che questa istruzione sia eseguita solo dal padre e non dal figlio, posso vedere che se non metto exit, alla riga
    //49, questa verrà eseguita sempre da entrambi i processi, padre e figlio!
    printf("Sono il processo che ha come id: %d\n", getpid());

    
}