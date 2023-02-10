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


void generatore_produttore(struct ProdConsGen *pc){
    
    message msg;

    int i, len_str;
    enter_monitor(USEM(pc));

    while (pc->num_mess == DIM_QUEUE) {
        wait_condition(USEM(pc), VARCOND_GEN_PRODUTTORI);
    }

    msg.type = MSG_TYPE;

    len_str = STRING_MIN_DIM + rand() % (STRING_MAX_DIM - STRING_MIN_DIM);
    for (i = 0; i < len_str; i++) {
        msg.stringa[i] = 'a' + rand() % 26;
    }
    msg.stringa[i] = '\0';

    for (i = 0; i < INT_MAX_DIM; i++) {
        msg.array[i] = rand() % 10;
    }

    msg.var = 0;

    pc->msg[pc->testa] = msg;
    pc->testa = (pc->testa + 1) % DIM_QUEUE;
    pc->num_mess += 1;

    printf("[generatore_produttore] Messaggio generato!\n");
    printf("[generatore_produttore] ...............msg.stringa: %s\n", msg.stringa);
    printf("[generatore_produttore] ...............msg.array[0]: %d\n", msg.array[0]);
    printf("[generatore_produttore] ...............msg.array[1]: %d\n", msg.array[1]);
    printf("[generatore_produttore] ...............msg.var: %d\n", msg.var);

    signal_condition(USEM(pc), VARCOND_GEN_CONSUMATORI);

    leave_monitor(USEM(pc));
}

void generatore_consumatore(struct ProdConsGen *pc, int ds_queue_gen_filter){
    message msg;

    enter_monitor(USEM(pc));

    while (pc->num_mess == 0) {
        wait_condition(USEM(pc), VARCOND_GEN_CONSUMATORI);
    }

    msg = pc->msg[pc->coda];
    pc->coda = (pc->coda + 1) % DIM_QUEUE;
    pc->num_mess -= 1;

    printf("[generatore_consumatore] Messaggio CONSUMATO!\n");
    printf("[generatore_consumatore] ...............msg.stringa: %s\n", msg.stringa);
    printf("[generatore_consumatore] ...............msg.array[0]: %d\n", msg.array[0]);
    printf("[generatore_consumatore] ...............msg.array[1]: %d\n", msg.array[1]);
    printf("[generatore_consumatore] ...............msg.var: %d\n", msg.var);
    
    int ret = msgsnd(ds_queue_gen_filter, &msg, SIZEMSG(message), 0);
    
    if (ret<0){
            perror("msgsnd del messaggio on ds_queue_gen_filter FALLITA!");
            exit(-1);
    }
    printf("[generatore_consumatore] Messaggio INVIATO!\n");

    signal_condition(USEM(pc), VARCOND_GEN_PRODUTTORI);

    leave_monitor(USEM(pc));
}

