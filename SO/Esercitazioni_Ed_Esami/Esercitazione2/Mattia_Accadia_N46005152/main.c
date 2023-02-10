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

int main()
{
    pid_t pid;
    int status;

    int ds_queue_gen_filter, ds_queue_filter_checksum, ds_queue_checksum_visual;
    int total_process = NUM_GENERATORS + NUM_FILTER + NUM_CHECKSUM + NUM_VISUAL;

    int key_queue_gen_filter = IPC_PRIVATE;
    int key_queue_filter_checksum = IPC_PRIVATE;
    int key_queue_checksum_visual = IPC_PRIVATE;

    ds_queue_gen_filter = msgget(key_queue_gen_filter, IPC_CREAT | 0664);
    ds_queue_filter_checksum = msgget(key_queue_filter_checksum, IPC_CREAT | 0664);
    ds_queue_checksum_visual = msgget(key_queue_checksum_visual, IPC_CREAT | 0664);

    printf("[master] Code create...\n");
    printf("[master] ...........ds_queue_gen_filter: %d\n", ds_queue_gen_filter);
    printf("[master] ...........ds_queue_filter_checksum: %d\n", ds_queue_filter_checksum);
    printf("[master] ...........ds_queue_checksum_visual: %d\n", ds_queue_checksum_visual);

    key_t shm_key = IPC_PRIVATE;

    int ds_shm = shmget(shm_key, sizeof(ProdConsGen), IPC_CREAT | 0664);

    if (ds_shm < 0)
    {
        perror("SHM errore");
        exit(1);
    }

    ProdConsGen *pc = (void *)shmat(ds_shm, NULL, 0);
    if (pc == (void *)-1)
    {
        perror("SHM attach errore");
        exit(1);
    }

    for (size_t i = 0; i < DIM_QUEUE; i++)
    {
        pc->msg[i].var = 0;
        for (size_t j = 0; j < INT_MAX_DIM; j++)
            pc->msg[i].array[j] = 0;
    }

    pc->libero = 1;
    pc->occupato = 0;
    pc->testa = pc->coda = 0;
    init_monitor(&pc->m, 2);

    int i;
    for (i = 0; i < NUM_GENERATORS; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            if (i % 2 == 0)
            {
                printf("GENERATORE PROD PID: %d\n", getpid());
                int j;
                for (j = 0; j < 4; j++)
                {
                    srand(time(NULL) * getpid() + j);
                    generatore_produttore(pc);
                }
                exit(0);
            }
            else
            {
                printf("GENERATORE CONS PID: %d\n", getpid());
                int j;
                for (j = 0; j < 4; j++)
                {
                    srand(time(NULL) * getpid() + j);
                    sleep(1);
                    generatore_consumatore(pc, ds_queue_gen_filter);
                }
                exit(0);
            }
        }
    }

    for (i = 0; i < NUM_FILTER + NUM_CHECKSUM + NUM_VISUAL; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            if (i == 0)
            {
                printf("FILTRO PID: %d\n", getpid());
                sleep(3);
                filtro(ds_queue_gen_filter, ds_queue_filter_checksum);
                exit(0);
            }
            else if (i == 1)
            {
                printf("CHECKSUM PID: %d\n", getpid());
                sleep(5);
                checksum(ds_queue_filter_checksum, ds_queue_checksum_visual);
                exit(0);
            }
            else if (i == 2)
            {
                printf("VISUALIZZATORE PID: %d\n", getpid());
                sleep(7);
                visualizzatore(ds_queue_checksum_visual);
                exit(0);
            }
        }
    }

    sleep(10);
    for (i = 0; i < total_process; i++)
    {
        wait(&status);
        if (status == -1)
            perror("Error on killing process");
        else
            printf("Child #%d terminated with status %d\n", i + 1, status);
    }

    remove_monitor(&pc->m);

    msgctl(ds_queue_gen_filter, IPC_RMID, 0);
    msgctl(ds_queue_filter_checksum, IPC_RMID, 0);
    msgctl(ds_queue_checksum_visual, IPC_RMID, 0);
    shmctl(ds_shm, IPC_RMID, 0);

    printf("[master] Rimozione code OK!\n");
    printf("[master] Rimozione monitor OK!\n");

    return 0;
}
