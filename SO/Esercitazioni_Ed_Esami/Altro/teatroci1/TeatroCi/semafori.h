#ifndef _PROCEDURE_H_
#define  _PROCEDURE_H_

#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>

int Wait_Sem(int id_sem, int numsem);
int Signal_Sem(int id_sem, int numsem);

#endif 

