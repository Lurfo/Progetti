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

        //Prima di cominciare il check sum attende qualche secondo
        sleep(3);

        for (j=0; j<NUM_MESSAGES; j++){

                checksum = 0;

                printf("[checksum] Ricevo dal processo Filter...\n");

                //Il checksum, effettua una receive non bloccante!
                //Altrimenti, se non ci sono altri messagg in attesa, non finisce mai il suo compito
                ret = msgrcv(queue_filter_checksum, &(mess), SIZE, 0, IPC_NOWAIT);
            
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
                
                //Sommo la stringa
                for(int i=0; i<STRING_MAX_DIM; i++){
                        checksum+=mess.str[i];
                }

                //Aggiungo i due numeri
                for(int j=0; j<INT_MAX_DIM; j++){
                        checksum+=mess.arr[j];
                }

                mess.var=checksum;
                
                printf("[checksum] Invio messaggio di CHECKSUM al Visualizzatore...\n");

                //Invio il messaggio al visualizzatore
                ret = msgsnd(queue_checksum_visual, &(mess), SIZE, IPC_NOWAIT);

                if(ret<0){
                        perror("È stato impossibile inviare il messaggio\n"); 
                                exit(-1);
                }


        }
        
        exit(0);
}

