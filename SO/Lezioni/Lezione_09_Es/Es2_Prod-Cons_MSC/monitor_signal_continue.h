//*****************IMPLEMENTAZIONE MONITOR SIGNAL AND CONTINUE******************************************
#ifndef __MONITOR_H
#define __MONITOR_H

//A differenza del precedente, qui non compare la coda a priorità, perchè il processo che segnala, continua con la sua 
//esecuzione, fino a quando non ha terminato
typedef struct {
//id del semaforo per realizzare il mutex del monitor
  int mutex;

//numero di variabili condition
  int num_var_cond;

//id del di semafori per le var_cond
  int id_conds;

//id della memoria condivisa per i contatori delle variabili condition
  int id_shared;

//array che contiene il numero di processi in attesa sulle variabili condition
  int *cond_counts;

} Monitor;

//monitor e numero di variabili condition
void init_monitor (Monitor*, int); 
void enter_monitor(Monitor*);
void leave_monitor(Monitor*);
void remove_monitor(Monitor*);

void wait_condition(Monitor*,int);
void signal_condition(Monitor*,int);
int queue_condition(Monitor*,int); 


#endif
