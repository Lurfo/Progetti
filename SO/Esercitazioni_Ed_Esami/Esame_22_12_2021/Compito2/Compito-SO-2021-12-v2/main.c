#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/shm.h>

#include "header.h"

#define NUM_PRODUTTORI 2
#define NUM_CONSUMATORI 5

#define PRODUZIONI 10
#define CONSUMAZIONI 4

void produttore(VettoreProdCons * vettore);
void consumatore(VettoreProdCons * vettore, BufferMutuaEsclusione * buffer);

int main() {

    //Per allorare le due strutture dati, devo utilizzare due shm 

    int idVett = shmget(IPC_PRIVATE, sizeof(VettoreProdCons), IPC_CREAT|0660); 

        if(idVett<0){
            perror("Errore creazione shm vettore\n"); 
                exit(1);
        }


    int idBuff = shmget(IPC_PRIVATE, sizeof(BufferMutuaEsclusione), IPC_CREAT|0660);

        if(idBuff<0){
            perror("Errore creazione shmbuff\n"); 
                exit(1);
        }

    //Ottengo i due riferimenti usando shmat

    VettoreProdCons * vettore = shmat(idVett, NULL, 0);

    BufferMutuaEsclusione * buffer = shmat(idBuff, NULL, 0);


    inizializza_vettore(vettore);
    inizializza_buffer(buffer);


    pid_t pid;

    for(int i=0; i<NUM_PRODUTTORI; i++) {

        /* TBD: Creare i processi produttori, e fargli chiamare la
         *      funzione "produttore()"
         */

        pid = fork(); 

            if(pid<0){
                perror("Errore generazione produttori\n"); 
                    exit(1);
            }

            if(pid == 0){

                printf("[PRODUTTORE %d] Avviato\n", getpid()); 

                produttore(vettore);

                exit(0);

            }
    }


    for(int i=0; i<NUM_CONSUMATORI; i++) {

        /* TBD: Creare i processi consumatori, e fargli chiamare la
         *      funzione "consumatore()"
         */

        pid = fork(); 

            if(pid<0){
                perror("Errore generazione consumatori\n"); 
                    exit(1);
            }

            if(pid==0){

                printf("[CONSUMATORE %d] Avviato\n", getpid()); 

                consumatore(vettore, buffer);

                exit(0);

            }

    }


    /* TBD: Attendere la terminazione dei processi figli */

    int stato;

    for(int i=0; i<NUM_PRODUTTORI+NUM_CONSUMATORI; i++){
        pid=wait(&stato);   

        printf("Termianto il processo %d, con stato: %d\n", pid, stato);

    }


    rimuovi_buffer(buffer);
    rimuovi_vettore(vettore);


    /* TBD: De-allocare le strutture dati */
    //Uso la funzione di controllo della memoria per rimuoverle
    shmctl(idVett, IPC_RMID, NULL);
    shmctl(idBuff, IPC_RMID, NULL);

    return 0;

}

void produttore(VettoreProdCons * vettore) {

    srand(getpid());
    
    for(int i=0; i<PRODUZIONI; i++) {

        int valore = rand() % 10;

        printf("[MAIN PRODUTTORE] Produzione: %d\n", valore);

        /* TBD: Chiamare il metodo "produci()" del monitor */

        produci(vettore, valore);
    }

}

void consumatore(VettoreProdCons * vettore, BufferMutuaEsclusione * buffer) {

    srand(getpid());

    for(int i=0; i<CONSUMAZIONI; i++) {

        int valore;

        /* TBD: Chiamare il metodo "consuma()" del monitor */

        valore = consuma(vettore);

        printf("[MAIN CONSUMATORE] Consumazione: %d\n", valore);

        /* TBD: Chiamare il metodo "aggiorna()", passandogli 
         *      il valore che è stato appena consumato
         */

        aggiorna(buffer, valore);
    }
}
