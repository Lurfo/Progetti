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

int main(){

        pid_t pid;
        int ds_queue_control_proxy, ds_queue_proxy_gestori;
    
        //create queues
        int key_queue_control_proxy = IPC_PRIVATE;
        int key_queue_proxy_gestori = IPC_PRIVATE;
    
        ds_queue_control_proxy = msgget(key_queue_control_proxy, IPC_CREAT|0660);
        ds_queue_proxy_gestori = msgget(key_queue_proxy_gestori, IPC_CREAT|0660);
    
        /* Creare le code di servizio per implementare la send sincrona */
        initServiceQueues();
        
        printf("[master] Code create...\n");
        printf("[master] ...........ds_queue_control_proxy: %d\n", ds_queue_control_proxy);
        printf("[master] ...........ds_queue_proxy_gestori: %d\n", ds_queue_proxy_gestori);
    

        for (int i=0; i<4; i++){
          
            /* TBD: Creare i 4 processi:
             * - Processo Controllore;
             * - Processo Proxy;
             * - Processo Gestore Arrivi
             * - Processo Gestore Partenze
             */

            pid = fork();

            if(pid<0){
                perror("Errore fork processo\n"); 
                    exit(1);
            }

            if(pid==0){

                //Uso uno switch, per andare a generare i vari processi
                switch(i){
                case 0:

                    controllore(ds_queue_control_proxy);
                    break;

                case 1:
                    proxy(ds_queue_control_proxy, ds_queue_proxy_gestori);
                    break;

                case 2:
                    gestore_arrivi(ds_queue_proxy_gestori);
                    break;

                case 3:
                    gestore_partenze(ds_queue_proxy_gestori);
                    break;
                
                default:
                    break;
                }

                exit(0);

            }


        }
    
        for (int i=0; i<4; i++){
            /*TBD: Attendere la terminazione dei processi creati in precedenza */
            wait(NULL);
        }

        /* TBD: Deallocare le code create */
        msgctl(ds_queue_control_proxy, IPC_RMID, NULL); 
        msgctl(ds_queue_proxy_gestori, IPC_RMID, NULL);

        removeServiceQueues();

        printf("[master] Rimozione code OK!\n");
    
        return 0;
}
