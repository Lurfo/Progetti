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

void filtro(int ds_queue_gen_filter, int ds_queue_filter_checksum)
{

        int ret, i;
        message mess;

        for (i = 0; i < NUM_MESSAGES; i++)
        {
                /* TODO: ricevere il messaggio dai processi generatori consumatori */
                ret = msgrcv(ds_queue_gen_filter, (void *)&mess, SIZE, MSG_TYPE, 0);

                if (ret < 0)
                {
                        perror("msgrcv on ds_queue_gen_filter FALLITA!");
                        exit(-1);
                }

                printf("[filtro] Ricevuto #%d messaggio dal generatore...\n", i);
                
                printf("[filtro] Ricerca carattere 'x' sulla stringa: %s...\n", mess.stringa);
                /* TODO: effettuare la ricerca del caratter 'x' e inviare il messaggio al processo checksum nel caso di carattere non trovato */
                if (strchr(mess.stringa, 'x') == NULL)
                {
                        msgsnd(ds_queue_filter_checksum, (void *)&mess, SIZE, 0);
                        printf("Messaggio filtrato, non c'erano 'x'!\n");
                }
        }

        exit(0);
}