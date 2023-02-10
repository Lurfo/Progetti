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

void filtro(int ds_queue_gen_filter, int ds_queue_filter_checksum) {
        int ret, i;
        message mess;

        for (i=0; i<NUM_MESSAGES; i++){

                ret = msgrcv(ds_queue_gen_filter, &mess, SIZEMSG(message), MSG_TYPE, 0);

                if(ret<0) {
                        perror("msgrcv on ds_queue_gen_filter FALLITA!");
                        exit(-1);
                }

                printf("[filtro] Ricevuto #%d messaggio dal generatore...\n", i);

                //ricerca del carattere 'x'
                printf("[filtro] Ricerca carattere 'x' sulla stringa: %s...\n", mess.stringa);
            
                if (strchr(mess.stringa, 'x') == NULL) {
                    printf("[filtro] Invio messaggio VALIDO al Checksum...\n");

                    ret = msgsnd(ds_queue_filter_checksum, &mess, SIZEMSG(message), 0);

                    if(ret<0) {
                        perror("msgsnd on ds_queue_filter_checksum FALLITA!");
                        exit(-1);
                    }
                }
                else {
                    printf("[filtro] Messaggio FILTRATO con successo...\n");
                }
                
        }
    
        exit(0);
}

