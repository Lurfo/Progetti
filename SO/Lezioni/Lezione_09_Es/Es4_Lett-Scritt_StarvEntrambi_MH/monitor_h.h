//Definizione delle procedure per implementare il costrutto monitor

//Realizzo il monitor mediante una struct
typedef struct{

    //Definisco l'id del semaforo che uso per controllare l'accesso al monitor e dunque che gestisce la competizione
    //tra i processi
    int mutex;

    //Siccome implemneto un monitor di hoare, definsco anche l'id del semaforo urgente 
    int urgent_sem; 

    //Specifico il numero di variabili condition che uso
    int num_var_cond; 

    //Siccome realizzo le variabili con un semaforo, specifico l'id del gruppo semafori per le var_cond
    int id_conds;

    //Ho bisogno di una memoria condivisa, che permette ai processi di aggiornare i contatori delle variabili condition e
    //della coda urgent 
    int id_shared; 

    //Definisco un array che tiene il conto, per ogni variabile condition, il numero di processi che sono in attesa su di essa
    int* cond_count; 

    //Faccio lo stesso anche per i processi urgenti
    int* urgent_count;


}Monitor;

//Definito la struttura, specifico le funzioni necessarie per il monitor

//Funzione che inizializza il monitor, l'unica cosa di cui ha bisogno in ingresso è il numero di variabili condition
void init_monitor(Monitor* m, int num_var);

//Funzioni principali per sfruttare il monitor
void enter_monitor(Monitor* m);
void leave_monitor(Monitor* m);
void remove_monitor(Monitor* m);

//Funzioni principali per le variabili condition
//Oltre al monitor, ho anche bisogno della var cond su cui devo effettuare la wait!
void wait_condition(Monitor* m, int var);

//Le medesime considerazioni anche per la signal
void signal_condition(Monitor* m, int var); 

//Definizo una funzione che controlla il numero di processi che sono accodati a quella variabile condition
int queue_condition(Monitor* m, int var);


