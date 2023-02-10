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

        int ret, i, j, checksum;
        message mess;

        sleep(1);

        for (j=0; j<NUM_MESSAGES; j++){

                checksum=0;

                printf("[checksum] Ricevo dal processo Filter...\n");

                ret = msgrcv(queue_filter_checksum, (void*)(&mess), SIZE, MSG_TYPE, IPC_NOWAIT);
            
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
                
                //Sommo i valri dell'array
                for(int i=0; i<INT_MAX_DIM; i++){
                        checksum+=mess.arr[i];
                }

                //Sommo i valori della stringa
                for(int i=0; i<STRING_MAX_DIM; i++){
                        checksum+= mess.string[i];
                }

                mess.var=checksum;

                printf("[checksum] Invio messaggio di CHECKSUM al Visualizzatore...\n");

                msgsnd(queue_checksum_visual, (void*)(&mess), SIZE, IPC_NOWAIT);
        }
        
        exit(0);
}

