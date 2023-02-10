#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

/*UNA TERZA SOLUZIONE CON I TIMER:
Consiste nell'uso dei timer Real-Time, della libreria posix
TUTTAVIA questa soluzione, nonostante sia comunque efficiente, risulta essere poco applicabile, in quanto è molto complessa da
utilizzare
*/


static sigset_t sigset;

//La wait è uguale a quella del caso precedente, contente cioè la funzione che fa sospendere il processo per attendere un segnale
//apposito
void wait_next_activation(void)
{
    int dummy;

    sigwait(&sigset, &dummy);
}

//La funzione di start del timer, risulta invece più complessa rispetto alla precedente
int start_periodic_timer(uint64_t offs, int period)
{
    //La struttura "itimerspec" è quella che definisce i valori del timer
    struct itimerspec t;

    //La struttura sigevent è quella che definisce come risvegliare il chiamante quando scatta il timer
    //e viene usata nella funzione "timer_create", per CREARE il timer
    struct sigevent sigev;

    //Variabiile che contine l'id del timer, in quanto, lo standart POSIX, prevede che il timer debba essere PRIMA creato
    //e poi impostato con i valori corretti
    timer_t timer;

    //Imposto alcune variabili che mi consetono di mantere una serie di informazioni per impostare il segnale
    const int signal = SIGALRM;
    int res;

    //Imposto il valore a cui deve inizalmente scattare il timer
    t.it_value.tv_sec     = offs    / 1000000;
    t.it_value.tv_nsec    = (offs   % 1000000) * 1000;

    //Imposto il valore a cui deve successivamente scattare il timer dopo la prima attivazione
    t.it_interval.tv_sec  = period  / 1000000;
    t.it_interval.tv_nsec = (period % 1000000) * 1000;

    //Vado ad impostare la variabile del segnale in modo apposito, usanto le medesime funzioni che ho usato nell'esempio
    //precedente
    sigemptyset(&sigset);
    sigaddset(&sigset, signal);
    sigprocmask(SIG_BLOCK, &sigset, NULL);

    //Imposto la modalità di risveglio del segnale andando a riversare lo spazio in memoria per la mia struttura
    //ed assegnanod i corrispettivi campi in modo corretto
    memset(&sigev, 0, sizeof(struct sigevent));
    sigev.sigev_notify = SIGEV_SIGNAL;
    sigev.sigev_signo = signal;

    //Vado a creare il timer, specificando anche il tipo di clock a cui voglio collegarlo
    res = timer_create(CLOCK_MONOTONIC, &sigev, &timer);
    if (res < 0) {
        perror("Timer Create");

	exit(-1);
    }

    //Imposto quindi il timer, specificando anche se si tratta di un timer assoluto o meno
    return timer_settime(timer, TIMER_ABSTIME, &t, NULL);
}

//Il job resta sempre il medesimo
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


//Il main, mantiene comunque la sua struttura
int main()
{
    int res;

    res = start_periodic_timer(2000000, 5000);
    if (res < 0) {
        perror("Start Periodic Timer");

        return -1;
    }

    while(1) {
        wait_next_activation();
        job_body();
    }

    return 0;
}
