#include <sys/time.h>
#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <sched.h>

//NOTA BENE: Di seguito si vede come è possibile poter andare ad impostare una determinata priorità ad un task, tramite una serie
//di primitive, questo permette di poter schedulare i vari task, usando una delle policy di scheduling analizzate nella teoria

//ESSENDO: Un taskp periodico, le funzioni che di seguito vengono utilizzate, sono le solite funzioni viste anche nei predenti esempi
static struct timespec r;
static int period;

#define NSEC_PER_SEC 1000000000ULL
static inline void timespec_add_us(struct timespec *t, uint64_t d)
{
    d *= 1000;
    t->tv_nsec += d;
    t->tv_sec += t->tv_nsec / NSEC_PER_SEC;
    t->tv_nsec %= NSEC_PER_SEC;
}

void wait_next_activation(void)
{
    clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &r, NULL);
    timespec_add_us(&r, period);
}

void start_periodic_timer(uint64_t offs, int t)
{
    clock_gettime(CLOCK_REALTIME, &r);
    timespec_add_us(&r, offs);
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

//NEL MAIN CI SONO LE MODIFCHE PRINCIPALI:
int main()
{
    //Viene introdotta una nuova struttura "sched_param", contente una serie di parametri utilizzati dallo scheduler
    //Ma quello che ci interessa è il parametro che indica la priorità che deve avere il task, in questo caso, impostiamo
    //la prima priorità tra i task RT
    struct sched_param sp;
    sp.sched_priority = 11;

    //CON QUESTA: Facciamo in modo di impostare quale policy di scheduling deve essere utilizzata per il task
    //(il cui PID deve essere il primo parametro della funzione, essendo lo stesso chiamante, posso mettere 0)
    //Specifico anche la policy di scheduling necessaria e fornisco come parametro la struttura sopra definita
    sched_setscheduler(0, SCHED_FIFO, &sp);

    //La restante parte del Main, risulta analoga
    start_periodic_timer(2000000, 5000);
    
    while(1) {
        wait_next_activation();
        job_body();
    }

    return 0;
}

//ATTENZIONE:
/*
Queste modifiche, NON SONO ABBASTANZA
Occorre infatti che il programma venga eseguito usando i privilegi di ROOT, poichè solo in questo modo è possibile andare
ad effettuare una modifica della priorità e della policy di scheduling, che altrimenti risultano invariati
*/
