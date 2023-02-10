//Specifica della funzione cliente
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "function.h"
#include "semafor.h"


void cliente(seduta* mem, int* disp, int semID){
    //Il cliente attente prima da 0 a 5 secondi!
    //Un tempo casuale!

    sleep(rand()%6); 


    int num = rand()% 4 +1; 

    printf("Devo prenotare: %d, posti\n", num);

    
    //Prima azione del processo: CONTROLLARE LA DISPONIBILITÀ DI POSTI, per farlo devo necessariamente 
    //accedere in mutua esclusione alla memoria che contiene la disponibilità!
    //In questo caso non rischio che altri processi possano modificare il valore della memoria mentre io sto controllando 
    wait_sem(semID, MUTEX_DISPONIB);

        //Controllo il numero di posti!
        if((*disp==0) || num>(*disp)){
            //Se il numero di posti non è sufficiente, facico una exit e ritorno al processo padre!
            printf("Non ci sono abbastanza posti disponibili!\n");
            //Se voglio effettuare direttamente una exit o una return, devo andare a sbloccare qui il mutex!
            signal_sem(semID, MUTEX_DISPONIB); 
            //Se non faccio questo passaggio, quando avrò dei processi che cercano di riaccedere alla memoria della 
            //disponibilità, allora tutti si bloccheranno e nessun andrà più avanti!
            exit(1);
                
        }

        else{

                //Se sono qui vuol dire che ho abbastanza disponibilità di posti per prenotare 
                for(int i=0; i<num; i++){
                    int indice=0; 

                    //Faccio una wait sulla memoria che contiene i posti
                    wait_sem(semID, MUTEX_POSTO); 

                        //Cerco il primo posto libero per andare ad occuparlo!
                        while(indice<DIM && mem[indice].stato!=LIBERO){
                            indice++;
                        }

                        //Aggiorno il valore dello stato ponendo il fatto che sta venendo aggiornato il valore!
                        mem[indice].stato=AGGIORNAMENTO;
                    
                    //Esco dalla sezione critica per l'aggiornamento della memoria dei posti!
                    signal_sem(semID, MUTEX_POSTO); 

                    //sleep(1);

                    //Posso inserire i valori nel posto
                    mem[indice].ID_cliente=getpid(); 
                    mem[indice].stato=OCCUPATO;

                    //Infine decremento il valore di posti disponibili!
                    (*disp)--;

                }
            }

            printf("Restano %d, posti disponibili!\n", *disp);

        //Posso controllare la disponibilità rimasta
        //Usando un programma esterno, in questo caso devo andare a togliere dal commento questa sezione di codice!
       /* pid_t pid = vfork(); 

            if(pid==0){
                execl("visualizzo", "./visualizzo", NULL); 
            }
        
        wait(NULL);*/


    //Finito cioè esco dalla mutua esclusione per la memoria che contiene la disponibilità
    signal_sem(semID, MUTEX_DISPONIB);

    signal_sem(semID, ATTENDERE);

}

//Specifica della seconda funzione cliente
void cliente2(seduta* mem, int* disp, int semID){

    //Faccio una wait per vedere se posso proseguire 
    //wait_sem(semID, PROSEGUO);

    //Attesa prima della prenotazione
    sleep(rand()%5 +1);

    int num = rand()%4 + 1;

    int restanti;

    //Controllo se il numero di posti è ancora disponibile!
    wait_sem(semID, MUTEX_DISPONIB); 

        if((*disp)==0 || num>(*disp)){
            
            printf("Non ci sono abbastanza posti disponibili da prenotare!\n"); 
            //Prima di lasciare faccio una signal sul semaforo
            signal_sem(semID, MUTEX_DISPONIB);
            signal_sem(semID, ATTENDERE);
            exit(1);
        }

        //Se ho abbastanza posti disponibli, il processo toglie dall'insieme dei posti, quelli che gli interessano
        else{
            (*disp)-=num;
            restanti=(*disp);
        }
    
    //Concludo la concorrenza rispetto alla variabile disponibilità 
    signal_sem(semID, MUTEX_DISPONIB); 


    //Posso dunque andare a prenotare i primi posti che trovo disponibili!
    //Eseguo questa prenotazione ogni per un numero di volte necessario a soddisfare la richiesta

    int indice;

    for(int i=0; i<num; i++){

            indice=0;

        wait_sem(semID, MUTEX_POSTO); 
            //Cerco il primo posto libero
            while(indice<DIM && mem[indice].stato!=LIBERO){
                indice++;
            }

            //Trovata la posizione libera, vado a sengarla come in uso!
            mem[indice].stato=AGGIORNAMENTO; 
        
        signal_sem(semID, MUTEX_POSTO); 

        //A questo punto posso agire liberamente sulla struttura senza necessariamente utilizzare un semaforo
        //Ho già trovato l'indice del posto che mi interessa
        sleep(1); //Per simulare il tempo di occupazione
        mem[indice].ID_cliente=getpid(); 
        mem[indice].stato=OCCUPATO; 

    }

    //Alla fine, il processo segnala che ci sono dei posti occupati
    signal_sem(semID, ATTENDERE);

}