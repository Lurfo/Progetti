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

void filtro(int ds_queue_gen_filter, int ds_queue_filter_checksum){

        int ret, i;
        message mess;

        int cont=0;

        for (i=0; i<NUM_MESSAGES; i++){

                ret = msgrcv(ds_queue_gen_filter, (void*)(&mess), SIZE, MSG_TYPE, 0);

                if(ret<0) {
                        perror("msgrcv on ds_queue_gen_filter FALLITA!");
                        exit(-1);
                }

                printf("[filtro] Ricevuto #%d messaggio dal generatore...\n", i);
                //ricerca del carattere 'x'
                printf("[filtro] Ricerca carattere 'x' sulla stringa: %s...\n", mess.string);
            
                //Verifico la presenza del carattere x, se non presente inviarlo al check sum
                if(strchr(mess.string, 'x')==NULL){
                        printf("[filtro] La stringa non contiene una 'x', la invio al prossimo processo\n"); 
                        msgsnd(ds_queue_filter_checksum, (void*)(&mess), SIZE, IPC_NOWAIT);
                        cont++;
                }
        }

        printf("[FILTRO] HO FILTRATO %d MESSAGGI\n", cont);
    
        exit(0);
}

