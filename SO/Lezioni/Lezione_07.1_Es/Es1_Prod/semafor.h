//Definizione dell'header dove sono specificate le funzioni di wait e signal!
#ifndef SEMAFOR_H
#define SEMAFOR_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int wait_sem(int semID, int semNum);

int signal_sem(int semID, int semNum);

#endif