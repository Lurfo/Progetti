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

void checksum(int queue_filter_checksum, int queue_checksum_visual){

        int ret, i, j, _checksum;
        message mess;

        for (j=0; j<NUM_MESSAGES; j++){
                sleep(1);

                printf("[checksum] Ricevo dal processo Filter...\n");

                ret = msgrcv(queue_filter_checksum, &mess, SIZEMSG(message), MSG_TYPE, IPC_NOWAIT);
            
                if(ret<0) {
                        if (errno == ENOMSG){
                                printf("Non ci sono più messaggi da ricevere dal processo filter...exit!\n");
                                break;
                        }
                        else{
                                perror("ERROR!!!");
                                exit(-1);
                        }
                }
                
                _checksum = 0;
                
                for (i = 0; mess.stringa[i] != '\0'; i++) {
                    _checksum += mess.stringa[i];
                }
                
                for (i = 0; i < INT_MAX_DIM; i++) {
                    _checksum += mess.array[i];
                }

                mess.var = _checksum;
                
                printf("[checksum] Invio messaggio di CHECKSUM al Visualizzatore...\n");

                ret = msgsnd(queue_checksum_visual, &mess, SIZEMSG(message), 0);

                if(ret<0) {
                    perror("msgsnd on ds_queue_checksum_visual FALLITA!");
                    exit(-1);
                }
        }
        
        exit(0);
}

