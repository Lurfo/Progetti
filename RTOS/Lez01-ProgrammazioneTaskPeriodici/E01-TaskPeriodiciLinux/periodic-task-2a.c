#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
//In questo caso, la soluzione prevede l'uso di timer UNIX periodici, andando a prevenire il problema principale dell'uso della
//funzione di sleep: IL RELATIVE SLEEP (vedi i file pdf per le note riguardo questo problema)

//Una delle prima cose da fare è "sovrascrivere" la funzione wait_next_activation, con la funzione messa a disposizione dalla
//libreria posix "PAUSE" che fa dormire il processo fino a che non arriva un segnale
//(RICORDA: Questa tipologia di timer usa un segnale per andare e risvegliare un task, tuttavia occorre gestirlo appositamente)
//Il suo scopo è appunto quello di mettere in pausa il task fino a che non arriva tale segnale
#define wait_next_activation pause

//LA GESTIONE DEL SEGNALE, deve essere implementata mediante un apposito heandler, in questo caso, siccome non abbiamo bisogno
//che faccia qualcosa di particolare, possiamo anche lasciare il suo corpo vuoto, ma dobbiamo comunque andarlo a specificare
    //--ATTENZIONE: Se si vuole evitare di utilizzare un heandler vuoto, si può anche andare ad includere una funzione sigwait()
    //nella wait_next_activation (tuttavia, il comportamento risulta essere analogo a questo)
static void sighand(int s)
{
}

//La funzioen di start, va ad impostare tutti i parametri necessari al timer
void start_periodic_timer(uint64_t offs, int period)
{
    //Mi definisco una struct per specificare il timer che vado ad utilizzare
    struct itimerval t;
    
    //Imposto il valore a cui il timer deve inizialmente scattare (Nel caso analizzato, parte dopo 2s)
    t.it_value.tv_sec     = offs   / 1000000;
    t.it_value.tv_usec    = offs   % 1000000;

    //Imposto il periodo di ripetizione del timer, ogni quanti secondi deve scattare dopo
    //l'istantte iniziale (Nel nostro caso, scatta ogni 5ms)
    t.it_interval.tv_sec  = period / 1000000;
    t.it_interval.tv_usec = period % 1000000;

    //Questa funzione serve per permettere l'associazione di un apposito handler al segnale specificato
    //IN QUESTO CASO: Collego al segnale SIGALARM (quello che viene generato dal timer RT di UNIX)
    //l'handler vuoto creato
    signal(SIGALRM, sighand);

    //Dunque vado ad invocare la funzione UNIX, per andare ad impostare correttamente il timer, ponendolo come un timer collegato al 
    //clock real-time del sistema, tramite l'apposito flag, posto come primo parametro della funzione
    //Ovviamente occorre anche fornigli la struttura del timer prima definita
    setitimer(ITIMER_REAL, &t, NULL);
}


//Come nel caso precedente, il job body risulta essere analogo
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


//Il main ha sempre la medesima struttura
int main()
{
    //Chiamo la funzione per inizializzare il timer periodico, inserendo gli appositi parametri
    start_periodic_timer(2000000, 5000);

    while(1) {

        //Chiamo la funzione wait, che in realtà è la funzione "pause" di UNIX, mettendo in pausa il task fino all'arrivo del
        //segnale SIGALARM, generato alla scadenza del timer
        //OVVIAMENTE: Pongo qui la wait, in modo che si possa trovare allineata con il tempo prestabilito di attesa dei 2 secondi
        wait_next_activation();

        //Alla riattivazione, posso andare ad eseguire il job
        job_body();
    }

    return 0;
}


/*
ATTENZIONE: Nonostante questa soluzione risulti comunque essere molto efficiente, si hanno comunque una serie di problematiche

-Posso avere UN UNICO TIMER REAL-TIME PER PROCESSO
    QUINDI: Se ho un processo composto da una serie di thread, risulta essere complesso andare a gestire il timer per ognuno di questi
    (in ogni caso non sarebbe più un timer periodico poichè andrebbe a scattare per intervalli completamente differenti, dovento quindi
    andarlo a settare di volta in volta per ogni timer)

-Si ha un aumento di latenza e di Overhead, causato dalla GESTIONE del segnale generato

-In precedenza si avevano anche una serie di problematiche legate alla risoluzione del timer, che risultava comunque limitata alla
capacità del processore, ma oggi non è più un problema

*/
