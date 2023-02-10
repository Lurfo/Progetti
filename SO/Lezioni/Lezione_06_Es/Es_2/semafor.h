#ifndef SEMAFOR_H
#define SEMAFOR_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int wait_sem(int, int); 
int signal_sem(int, int);

#endif
