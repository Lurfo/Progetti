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


void generatore_produttore(struct ProdConsGen *pc){

    char string[STRING_MAX_DIM];

    enter_monitor(&(pc->m)); 
       
        //Effettuo un controllo sulla varcond
        while(pc->spazio_occupato==1){
            wait_condition(&(pc->m), VARCOND_GEN_PRODUTTORI);
        }

        //Se sono qui, sono stato sbloccato
        //Modifico il valore delle var_cond
        pc->spazio_libero=0;
        pc->spazio_occupato=1;
        
        //Esco dal monitor per poter produrre il messaggio
    
    leave_monitor(&(pc->m));

    //Imposto il tipo del messaggio
    pc->buff[pc->testa].type=MSG_TYPE;

    //Produco il messaggio
    for(int i=0; i<STRING_MAX_DIM-1; i++){
        string[i] = 'a' + rand()%26;
    }

    //Inserisco il carattere terminatore
    string[STRING_MAX_DIM]='\0';

    //Inserisco il valore della stringa nel buffer prodcons
    strcpy(pc->buff[pc->testa].string, string);

    //Inserisco i valori nell'array
    for(int i=0; i<INT_MAX_DIM; i++){
        pc->buff[pc->testa].arr[i]=rand()%9;
    }

    //Inizializzo il valore della variabile intera
    pc->buff[pc->testa].var=0;

    
    printf("[generatore_produttore] Messaggio generato!\n");
    printf("[generatore_produttore] ...............msg.stringa: %s\n", pc->buff[pc->testa].string);
    printf("[generatore_produttore] ...............msg.array[0]: %d\n", pc->buff[pc->testa].arr[0]);
    printf("[generatore_produttore] ...............msg.array[1]: %d\n", pc->buff[pc->testa].arr[1]);
    printf("[generatore_produttore] ...............msg.var: %d\n", pc->buff[pc->testa].var);

    //Ho inserito i valori nel buffer, dunque rientro nel monitor per concludere
    enter_monitor(&(pc->m)); 

        //Modifico il valore di testa
        pc->testa=(pc->testa+1) % DIM_QUEUE;

        //Faccio una signal ai consumatori che possono consumare nello spazio precedente
        signal_condition(&(pc->m), VARCOND_GEN_CONSUMATORI); 


    //Lascio il monitor
    leave_monitor(&(pc->m));

}

void generatore_consumatore(struct ProdConsGen *pc, int ds_queue_gen_filter){

    message m;

    m.type=MSG_TYPE;

    //Entro nel monitor
    enter_monitor(&(pc->m)); 

        //Controllo la var_cond
        while(pc->spazio_libero==1){
            wait_condition(&(pc->m), VARCOND_GEN_CONSUMATORI);
        }

        //Se arrivo qui, sono stato sbloccato
        //Modifico i valori
        pc->spazio_libero=1;
        pc->spazio_occupato=0;

    //Lascio il monitor
    leave_monitor(&(pc->m));
    
    printf("[generatore_consumatore] Messaggio CONSUMATO!\n");
    printf("[generatore_consumatore] ...............msg.stringa: %s\n", pc->buff[pc->coda].string);
    printf("[generatore_consumatore] ...............msg.array[0]: %d\n", pc->buff[pc->coda].arr[0]);
    printf("[generatore_consumatore] ...............msg.array[1]: %d\n", pc->buff[pc->coda].arr[1]);
    printf("[generatore_consumatore] ...............msg.var: %d\n", pc->buff[pc->coda].var);

    strcpy(m.string, pc->buff[pc->coda].string);

    for(int i=0; i<INT_MAX_DIM; i++){
        m.arr[i]=pc->buff[pc->coda].arr[i];
    }

    m.var=pc->buff[pc->coda].var;


    int ret = msgsnd(ds_queue_gen_filter, (void*)(&m), SIZE, IPC_NOWAIT);
    
    if (ret<0){
            perror("msgsnd del messaggio on ds_queue_gen_filter FALLITA!");
            exit(-1);
    }
    printf("[generatore_consumatore] Messaggio INVIATO!\n");
    
    //Entro nel monitor
    enter_monitor(&(pc->m)); 

        //Modifico il valore di coda
        pc->coda = (pc->coda + 1) %DIM_QUEUE;

        //Faccio una signal ai produttori
        signal_condition(&(pc->m), VARCOND_GEN_PRODUTTORI);

    //Lascio il monitor
    leave_monitor(&(pc->m));
}

