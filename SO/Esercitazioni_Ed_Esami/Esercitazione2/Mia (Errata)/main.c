#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include <sys/ipc.h>
#include <sys/shm.h>

#include "header.h"

int main(){

        pid_t pid;
        int ds_queue_gen_filter, ds_queue_filter_checksum, ds_queue_checksum_visual;
        int total_process = NUM_GENERATORS + NUM_FILTER + NUM_CHECKSUM + NUM_VISUAL;

        //create queues
        int key_queue_gen_filter = IPC_PRIVATE;
        int key_queue_filter_checksum = IPC_PRIVATE;
        int key_queue_checksum_visual = IPC_PRIVATE;

        ds_queue_gen_filter = msgget(key_queue_gen_filter, IPC_CREAT|0660);
        ds_queue_filter_checksum = msgget(key_queue_filter_checksum, IPC_CREAT|0660);
        ds_queue_checksum_visual = msgget(key_queue_checksum_visual, IPC_CREAT|0660);
        
        printf("[master] Code create...\n");
        printf("[master] ...........ds_queue_gen_filter: %d\n", ds_queue_gen_filter);
        printf("[master] ...........ds_queue_filter_checksum: %d\n", ds_queue_filter_checksum);
        printf("[master] ...........ds_queue_checksum_visual: %d\n", ds_queue_checksum_visual);

        /* creazione shm per prod-cons generatori */
    
        key_t shm_key = IPC_PRIVATE;

        int ds_shm = shmget(shm_key, sizeof(Buff), IPC_CREAT|0660);

        if(ds_shm<0) { perror("SHM errore"); exit(1); }

        //Effettuo attach della memoria
        Buff* pc = shmat(ds_shm, NULL, 0);

        if(pc==(void*)-1){
            perror("Errore shmat\n");
                exit(1);
        }

        pc->spazio_libero=1;
        pc->spazio_occupato=0;

        //Inizializzo il monitor
        init_monitor(&(pc->m), NUM_VARCOND);
        
    
        int i;

        for (i=0; i<NUM_GENERATORS; i++){
        
                pid = fork();

                if (pid == 0){
                
                    if (i % 2 == 0){
                        
                        printf("GENERATORE PROD PID: %d\n", getpid());
                        int j;
                        for (j=0; j<4; j++){
                            srand(time(NULL)*getpid()+j);
                            generatore_produttore(pc);
                        }
                        exit(0);
                    }
                    else {
                        printf("GENERATORE CONS PID: %d\n", getpid());
                        int j;
                        for (j=0; j<4; j++){
                            srand(i*getpid()*time(NULL));
                            generatore_consumatore(pc, ds_queue_gen_filter);
                        }
                        exit(0);
                    }
                }        
        }        


        for (i=0; i<NUM_FILTER+NUM_CHECKSUM+NUM_VISUAL; i++){
                pid = fork();
                if (pid==0){
                        if (i==0){
                            printf("FILTRO PID: %d\n", getpid());
                            filtro(ds_queue_gen_filter, ds_queue_filter_checksum);
                        }
                        else if (i==1){
                            printf("CHECKSUM PID: %d\n", getpid());
                            checksum(ds_queue_filter_checksum, ds_queue_checksum_visual);
                        }
                        else if (i==2){
                            printf("VISUALIZZATORE PID: %d\n", getpid());
                            visualizzatore(ds_queue_checksum_visual);
                        }
                }
        }

       
        for (i=0; i<total_process; i++){
                wait(NULL);
        }

        //Rimuovo le code
        msgctl(ds_queue_gen_filter, IPC_RMID, NULL);
        msgctl(ds_queue_filter_checksum, IPC_RMID, NULL); 
        msgctl(ds_queue_checksum_visual, IPC_RMID, NULL);
            printf("[master] Rimozione code OK!\n");

        //Rimuovo il monitor
        remove_monitor(&(pc->m));
        printf("[master] Rimozione monitor OK!\n");

        //Rimuovo la memoria condivisa
        shmctl(ds_shm, IPC_RMID, NULL);
            printf("[master] Rimozione memoria OK!\n");         
    
        return 0;
}
