//Specifica di un programma che usa una memoria condivisa, immagazzinando una stringa di caratteri!
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Necessaria alla funzione fork, insieme ad alcune delle librerie precedenti!
#include <sys/types.h>

//Libreria per la funzione exit
#include <wait.h>

//Libreria per la funzione perror
#include <errno.h>

//Librerie necessarie per la risorsa condivisa (shared memory)
#include <sys/ipc.h>
#include <sys/shm.h>

#include <stdbool.h>

//Definizione della libreria che mi permette di manipolare le stringhe!
#include <string.h>

void eseguito(int);

int main(){

    //Definizione del descrittore della memoria condivisa
    //Uso la chiave come privata poichè essa deve essere condivisa solo dal processo padre  e figlio!
    //In questo caso voglio che la mia memoria riesca a contenere 1000 caratteri, per questo faccio in modo di moltiplicare
    //la dimensione di un char  (1 byte), per il numero di caratteri che voglio immagazzinare!

    //NOTA: Come permessi, do solo lettura e scrittura, senza dare il permesso di esecuzione!
    int desc = shmget(IPC_PRIVATE, 1000*sizeof(char), IPC_CREAT|IPC_EXCL|0660);

    //Effettuo il controllo
    //In questo caso, non voglio usare una memoria condivisa già esistente, ma voglio crearne una personale!
    eseguito(desc);


    //Eseguo l'attachment!
    //È necessario eseguire un casting per il puntatore!

    char* p = (char*) shmat(desc, NULL, 0);
                        //Alla funzione di attachment devo inviare anche il descrittore della memoria condivisa!

    //La funzione shmat restituisce -1 in caso di essore, dunque effettuo il controllo 
    
    //Effettuo un controllo sulla funziona shmat!
    if(p==(void*)-1){
        perror("Non sono riuscito a fare l'incollamento\n"); 
        exit(1);
    }


    printf("La tua memoria condivisa è stata creata\n"); 
    printf("Locazione scelta: %p\n", p); 
    printf("Chiave scelta: %d\n", IPC_PRIVATE);
    printf("Descrittore della memoria: %d\n", desc);

    printf("----------------------------------------\n");

    //Verifico che la memoria condivisa sia stata effettivamente creata!

    int pid2=vfork();

    eseguito(pid2);

    if(pid2==0){
        //Utilizzo la funzione di execlp! Così posso usare l'apposito comando per verificare la creazione!
        eseguito(execlp("ipcs", "ipcs", NULL));
    
    }

    wait(NULL);

    printf("Hai ottenuto l'output desiderato, il descrittore: %d, si trova nella lista!\n", desc);

    printf("-------------------------------\n");

    //Invoco il processo figlio!

    int pid = fork(); 

    eseguito(pid); 

    if(pid==0){

        char* message; //Questo è il puntatore alla mia stringa! 

        //Alloco la memoria del mio puntatore
         
        message = (char*) malloc(sizeof(char)*1000);

        printf("Sono tuo figlio, dimmi tutto\n");

        //Inserisco il messaggio nella mia stringa!
        fgets(message, 1000, stdin); 
        //La funzione gets, permette di andare a considerare anche i vari spazi!

        int lung = strlen(message); 

        message[lung-1]= '\0';

        printf("Tutto chiaro, lo metto in memoria condivisione!\n");

        //Per salvare il messaggio nella memoria condivisa, uso la funzione di copia della libreria string!
        strcpy(p, message);

        printf("Ho finito il mio compito, addio!\n");        

        //Libero il mio puntatore 
        free(message);

        exit(0);
    }
    
    int status;

    wait(&status);

    if(!WIFEXITED(status)){
        perror("Ho avuto un problema e non ho terminato correttamente!\n");
        exit(1);
    }

    printf("-------------------------------\n");

    printf("Sono il padre, vediamo che dice quello stronzo di mi figlio\n"); 

    printf("Il messaggio che mi ha lasciato è: '%s'\n", p);

    //Tolgo la memoria condivisa ed eseguo il controllo che la memoria sia andara a buon fine! 
    eseguito(shmctl(desc, IPC_RMID, NULL));

}

//Fuzione di controllo per le variabili!
void eseguito(int var){
  
    if(var<0){
        perror("La funzione non è stata completata con successo!\n"); 
        exit(1);
      }
    
}

