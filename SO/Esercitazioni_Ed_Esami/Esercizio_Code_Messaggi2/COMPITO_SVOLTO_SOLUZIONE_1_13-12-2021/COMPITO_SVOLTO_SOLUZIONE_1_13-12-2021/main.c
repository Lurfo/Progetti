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

int coda_RTS;
int coda_OTS;

int main(){

        pid_t pid;
        int ds_queue_control_proxy, ds_queue_proxy_gestori;
    
        //create queues
        int key_queue_control_proxy = IPC_PRIVATE;
        int key_queue_proxy_gestori = IPC_PRIVATE;
    
        ds_queue_control_proxy = msgget(key_queue_control_proxy, IPC_CREAT | 0644);
        ds_queue_proxy_gestori = msgget(key_queue_proxy_gestori, IPC_CREAT | 0644);
    
        initServiceQueues();
        
        printf("[master] Code create...\n");
        printf("[master] ...........ds_queue_control_proxy: %d\n", ds_queue_control_proxy);
        printf("[master] ...........ds_queue_proxy_gestori: %d\n", ds_queue_proxy_gestori);
    

        int i;
        for (i=0; i<4; i++){
            pid = fork();
            if (pid==0){
                if (i==0){
                    controllore(ds_queue_control_proxy);
                }
                else if (i==1){
                    proxy(ds_queue_control_proxy, ds_queue_proxy_gestori);
                }
                else if (i==2){
                    gestore_arrivi(ds_queue_proxy_gestori);
                    
                }
                else if (i==3){
                    gestore_partenze(ds_queue_proxy_gestori);
                    
                }
            }
        }
    
        for (i=0; i<4; i++){
                wait(NULL);
        }

        msgctl(ds_queue_control_proxy, IPC_RMID, 0);
        msgctl(ds_queue_proxy_gestori, IPC_RMID, 0);
        removeServiceQueues();

        printf("[master] Rimozione code OK!\n");
    
        return 0;
}
