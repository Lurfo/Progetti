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

void generatore_produttore(ProdConsGen *pc)
{
    /* TODO: utilizzare il costrutto monitor per la produzione del messaggio */
    enter_monitor(&pc->m);

    while (pc->occupato == 1)
        wait_condition(&pc->m, VARCOND_GEN_PRODUTTORI);

    pc->occupato = 1;
    pc->libero = 0;

    pc->msg[pc->testa].type = MSG_TYPE;

    for (size_t i = 0; i < STRING_MAX_DIM - 1; i++)
        pc->msg[pc->testa].stringa[i] = 'a' + (rand() % 26);
    pc->msg[pc->testa].stringa[STRING_MAX_DIM - 1] = '\0';

    pc->msg[pc->testa].array[0] = rand() % 10;
    pc->msg[pc->testa].array[1] = rand() % 10;
    pc->msg[pc->testa].var = 0;

    printf("[generatore_produttore] Messaggio generato!\n");
    printf("[generatore_produttore] ...............msg.stringa: %s\n", pc->msg[pc->testa].stringa);
    printf("[generatore_produttore] ...............msg.array[0]: %d\n", pc->msg[pc->testa].array[0]);
    printf("[generatore_produttore] ...............msg.array[1]: %d\n", pc->msg[pc->testa].array[1]);
    printf("[generatore_produttore] ...............msg.var: %d\n", pc->msg[pc->testa].var);

    pc->testa = (pc->testa + 1) % DIM_QUEUE;
    leave_monitor(&pc->m);

    signal_condition(&pc->m, VARCOND_GEN_CONSUMATORI);
}

void generatore_consumatore(ProdConsGen *pc, int ds_queue_gen_filter)
{
    enter_monitor(&pc->m);

    while (pc->libero == 1)
        wait_condition(&pc->m, VARCOND_GEN_CONSUMATORI);

    pc->occupato = 0;
    pc->libero = 1;

    printf("[generatore_consumatore] Messaggio CONSUMATO!\n");
    printf("[generatore_consumatore] ...............msg.stringa: %s\n", pc->msg[pc->coda].stringa);
    printf("[generatore_consumatore] ...............msg.array[0]: %d\n", pc->msg[pc->coda].array[0]);
    printf("[generatore_consumatore] ...............msg.array[1]: %d\n", pc->msg[pc->coda].array[1]);
    printf("[generatore_consumatore] ...............msg.var: %d\n", pc->msg[pc->coda].var);

    int ret = msgsnd(ds_queue_gen_filter, (void *)&pc->msg[pc->coda], SIZE, 0);

    if (ret < 0)
    {
        perror("msgsnd del messaggio on ds_queue_gen_filter FALLITA!");
        exit(-1);
    }
    printf("[generatore_consumatore] Messaggio INVIATO!\n");

    pc->coda = (pc->coda + 1) % DIM_QUEUE;

    leave_monitor(&pc->m);

    signal_condition(&pc->m, VARCOND_GEN_PRODUTTORI);
}
