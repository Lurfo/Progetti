#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

/*ATTENZIONE:
Questa è la medesima soluzione precednete in cui vado a usare un timer RT UNIX, ma in questo caso, non uso un handler vuoto
infatti nella funzione di wait, faccio in modo che il processo si sospenda, con la funzione apposita "sigwait" fino a quando non
scatta il segnale apposito, specificato nella variabile apposita "sigset" 
*/

//Questa è la struttura che deve andare a contenere tutti i valori del segnale 
static sigset_t sigset;


//La funzione di wait, va ad eseguire appunto la funzione di sigwait
void wait_next_activation(void)
{
    //La variabile deve contenere il valore numerico restituito dal segnale che ho specificato
    int dummy;

    //Fa in modo di sospendere il processo, fino a che non arriva il segnale deifnito in sigset, inserendo il numero del segnale
    //nella variabile dummy
    sigwait(&sigset, &dummy);
}


//Nella funzione di inizializzazione del timer periodico, che contiene le medesime istruzioni della precedente verisone
//si inseriscono una serie di comandi per la gestione della variabile siset, che contiene la tipologia di segnale
void start_periodic_timer(uint64_t offs, int period)
{
    struct itimerval t;

    t.it_value.tv_sec     = offs   / 1000000;
    t.it_value.tv_usec    = offs   % 1000000;
    t.it_interval.tv_sec  = period / 1000000;
    t.it_interval.tv_usec = period % 1000000;

    //Tramite queste funzioni vado a "pulire" la variabile sigset e vado a specificare la tipologia di segnale che
    //devo andare a gestire
    sigemptyset(&sigset); 
    sigaddset(&sigset, SIGALRM);

    //Con questa vado invece ad impostare la maschera del segnale
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    setitimer(ITIMER_REAL, &t, NULL);
}

static void job_body(void)
{
    static int cnt;
    static uint64_t start;
    uint64_t t;
    struct timeval tv;

    if (start == 0) {
        gettimeofday(&tv, NULL);
	start = tv.tv_sec * 1000ULL + tv.tv_usec / 1000ULL;
    }
        
    gettimeofday(&tv, NULL);
    t = tv.tv_sec * 1000ULL + tv.tv_usec / 1000ULL;
    if (cnt && (cnt % 100) == 0) {
        printf("Avg time: %f\n", (double)(t - start) / (double)cnt);
    }
    cnt++;
}

int main()
{
    start_periodic_timer(2000000, 5000);

    while(1) {
        wait_next_activation();
        job_body();
    }

    return 0;
}
