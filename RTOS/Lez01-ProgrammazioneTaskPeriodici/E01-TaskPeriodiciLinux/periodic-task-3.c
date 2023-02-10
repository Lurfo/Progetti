#include <sys/time.h>
#include <time.h>
#include <stdint.h>
#include <stdio.h>

/* 
NOTA BENE: Mediante l'uso di una funzione di nanosleep, posso andare ad eliminare il problema dello sleep relativo
in questo modo, il task attende (è sospeso) fino al tempo ASSOLUTO successivo, rispetto ad un valore inziale
*/

//Le due varibili globali mi occorrono servono a:

//-Mantenere l'istante iniziale della prima attivazione del task
//viene quindi usato per calcolare i successivi istanti di attivazione
static struct timespec r;

//-Questa mantiene il periodo di attesa
static int period;

//Utilizzo questa funzione per andare ad aggiungere nanosecondi al tempo di risveglio, in modo da calcolare
//l'istante della successiva attivazione
#define NSEC_PER_SEC 1000000000ULL
static inline void timespec_add_us(struct timespec *t, uint64_t d)
{
    d *= 1000;
    t->tv_nsec += d;
    t->tv_sec += t->tv_nsec / NSEC_PER_SEC;
    t->tv_nsec %= NSEC_PER_SEC;
}

//La funzione di wait, va a chiamare la nanosleep e va a modificare l'istante della successiva attivazione aggiungendo il periodo
void wait_next_activation(void)
{

    //La nanosleep, fa addormentare il processo fino al tempo che viene indicato nella variabile usata "r"
    clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &r, NULL);

    //Va ad aggiornare il valore della successiva attivazione aggiungendo il periodo (tramite la funzione apposita)
    timespec_add_us(&r, period);
}

void start_periodic_timer(uint64_t offs, int t)
{
    //La funzione start, è molto semplice: 

    //-Legge il tempo attuale
    clock_gettime(CLOCK_REALTIME, &r);

    //-Aggiunge l'offset, in modo che il task venga bloccato per il tempo iniziale che ho definito
    timespec_add_us(&r, offs);

    //-Salva il valore del periodo
    period = t;
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


/*
ATENZOINE: Rispetto alle soluzioni precedenti, questa risulta

-Più efficienti in termini di latenza, infatti è non ho dei segnali da gestire, non ho quindi l'overhead

-Più semplice, in quanto non devo impostare il timer come nelle precedenti verisioni, inoltre, come si vede anche dalle funzioni
si può facilmente notare che le funzioni che ottengo, usando questa metodologia, risultano essre anche molto più snelle

TUTTAVIA: Fa uso di variabili globali, che non dovrebbero essere utilizzate per evitare delle problematiche, che si possono
avere specialment equando uso i thread, che possono generare dei problemi quando vanno a modificare la variabile

*/