#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "header.h"

//Specifica della funzione di produzione del processo produttore


    //ATTENZIONE:
    //Ho fatto in modo che tutto il processi di consumazione, così come anche quello di produzione
    //avvengano all'interno del monitor

    //Ed è così che deve essere fatto




void generatore_produttore(struct ProdConsGen *pc){
        
    //Mi definisco un messaggio
    message m;

    m.type = MSG_TYPE;

    //Come primo passo, bisogna sempre entrare nel monitor
    enter_monitor(&(pc->m));

    //A questo punto effettuo un controllo sua mia condizione
    //Il processo produttore, deve sempre andare a conctrollare che il numero di posti disponibili non sia uguale al massimo numero di posti 
    //del buffer
    while(pc->numOccupati==DIM_QUEUE){
        //Se questo è vero, allora mi metto in attesa sulla mia condizione (Quella dei produttori)
        wait_condition(&(pc->m), VARCOND_GEN_PRODUTTORI);
    }
    
    //Incremento il numero di posti che saranno occupati
    pc->numOccupati++;

    //Vado a produrre il mio messaggio!

    //Genero la mia stringa
    for(int i=0; i<STRING_MAX_DIM; i++){
        m.str[i]= 'a' + rand() % 26;
    }

        //Alla fine devo sempre aggiungere il carattere di terminazione
        m.str[STRING_MAX_DIM]='\0';
    
    //Riempimento dell'array di ineri
    for(int j=0; j<INT_MAX_DIM; j++){
        m.arr[j]= rand() % 10;
    }

    //Inizializzo il valore della variabile libera a 0
    m.var=0;
    
    printf("[generatore_produttore] Messaggio generato!\n");
    printf("[generatore_produttore] ...............msg.stringa: %s\n", m.str);
    printf("[generatore_produttore] ...............msg.array[0]: %d\n", m.arr[0]);
    printf("[generatore_produttore] ...............msg.array[1]: %d\n", m.arr[1]);
    printf("[generatore_produttore] ...............msg.var: %d\n", m.var);

    //Inserisco il messaggio che ho generato alla testa del mio buffer
    pc->Buff[pc->testa]=m;

    //Incremento il puntatore di testa per spostarmi all'elemento successivo
    pc->testa = (pc->testa + 1) % DIM_QUEUE;

    //A questo punto, posso andare a segnalare ai consumatori che un messaggio c'è 
    signal_condition(&(pc->m), VARCOND_GEN_CONSUMATORI); 

    //Posso lasciare il monitor
    leave_monitor(&(pc->m));
}

void generatore_consumatore(struct ProdConsGen *pc, int ds_queue_gen_filter){

    message m;

    //Il processo consumatore, entra all'interno del monitor
    enter_monitor(&(pc->m)); 

        //Effettua un controllo sulla condizione, fino a quando essa non è verificare, deve uscire nuovamente dal monitor
        //per poi rimettersi in attesa
        while(pc->numOccupati == 0){
            //Fino a quando non c'è nessun posto occupato, il consumatore, si deve necessariamente mettere in attesa
            wait_condition(&(pc->m), VARCOND_GEN_CONSUMATORI);

        }

        //Quando sono qui, vuol dire che "Mi sono sbloccato!"

        //Diminuisco il numero di messaggi presenti
        pc->numOccupati--;

        //Leggo il mio messaggio partendo dalla coda
        m=pc->Buff[pc->coda];        
        
        printf("[generatore_consumatore] Messaggio CONSUMATO!\n");
        printf("[generatore_consumatore] ...............msg.stringa: %s\n", pc->Buff[pc->coda].str);
        printf("[generatore_consumatore] ...............msg.array[0]: %d\n", pc->Buff[pc->coda].arr[0]);
        printf("[generatore_consumatore] ...............msg.array[1]: %d\n", pc->Buff[pc->coda].arr[1]);
        printf("[generatore_consumatore] ...............msg.var: %d\n", pc->Buff[pc->coda].var);
        
        //A questo punto, non mi resta che andare ad effettuare l'invio del messaggio
        int ret = msgsnd(ds_queue_gen_filter, &(m), SIZE, IPC_NOWAIT);
        
        if(ret<0){
                perror("msgsnd del messaggio on ds_queue_gen_filter FALLITA!");
                exit(-1);
        }
        printf("[generatore_consumatore] Messaggio INVIATO!\n");
        
        //Vado a modificare il valore della coda
        pc->coda = (pc->coda +1) % DIM_QUEUE;

        //Posso fare la signal ai produttori che si è liberato un posto
        signal_condition(&(pc->m), VARCOND_GEN_PRODUTTORI); 

    //Dopo aver operato, non mi resta che andare a lasciare il monitor
    leave_monitor(&(pc->m));
}

