//Programma svolto in classe

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Nel caso della memoria condivisa devo includere questi due header
#include <sys/shm.h>
#include <sys/ipc.h>

#include <sys/wait.h>
#include <sys/types.h>

int main(){
    //Definizione della chiave di memoria usando in questo caso il frag che mi permette di usare una chiave privata
    key_t chiave = IPC_PRIVATE; 

    //Specifico il descrittore della memoria condivisa, che immagino sia un certo numero di interi usando la funzione get
    int ds = shmget(chiave, 10*sizeof(int), IPC_CREAT | 0664); //Ho definito una zona di memoria condivisa pari a 1KB

    //Qui posso anche inserire un controllo dell'errore e controllare che ds non sia minore di 0!!!!

    //Dopo la creazione devo necessariaente andare a fare una funzione di attachment
    int* p = shmat(ds, NULL,0); //Qui devo anche fare il casting

    //Eseguo la fork, in modo da generare un figlio

    printf("[PADRE] Ho il pid ugusle a: %d\n", getpid());


    int pid = fork();

    //Controllo che sia il figlio
    if(pid==0){
        printf("Sono il figlio, che ha il pid: %d \n", pid); 
        printf("Sono figlio di: %d\n", getppid());

        //Inseiserisco un certo numero di interi
        
        //Nella prima locazione di memoria
        p[0]=10;
    }

    //Uso una wait in modo che il padre aspetti il figlio
    wait(NULL); 

    printf("Ho il pi: %d\n", getpid());

    //Il padre stampa quello che ha scritto il figlio
    printf("[PADRE] Sto leggendo la locazione di meoria: %p, con un valore uguale a: %d\n", p+4, p[0]);

    //A questo punto devo fare il detachment per andare a scollegare la memoria condivisa

}
