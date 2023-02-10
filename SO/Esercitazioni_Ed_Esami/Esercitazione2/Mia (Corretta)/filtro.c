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

        int  controllo = 0;
      
        for (i=0; i<NUM_MESSAGES; i++){

                //Il filtro può effettuare una recieve bloccante, poichè deve ricevere tutti i messaggi che gli arrivano
                //dal generatore
                ret = msgrcv(ds_queue_gen_filter, &(mess), SIZE, 0, 0);

                if(ret<0) {
                        perror("msgrcv on ds_queue_gen_filter FALLITA!");
                        exit(-1);
                }

                printf("[filtro] Ricevuto #%d messaggio dal generatore...\n", i+1);
                //ricerca del carattere 'x'
                printf("[filtro] Ricerca carattere 'x' sulla stringa: %s...\n", mess.str);
            
                if(strchr(mess.str, 'x') == NULL){
                      
                        printf("[filtro]La stringa %s, non ha una x, la inoltro\n", mess.str); 

                        //Invio la stringa sempre con una send non bloccante!
                        ret = msgsnd(ds_queue_filter_checksum, &(mess), SIZE, IPC_NOWAIT);

                        if(ret<0){
                                perror("Errore nell' invio della strigna!\n"); 
                                        exit(-1);
                        }

                        controllo++;

                }
        }

        printf("[FILTRO] HO INVIATO %d MESSAGGI\n", controllo);
    
        exit(0);
}

