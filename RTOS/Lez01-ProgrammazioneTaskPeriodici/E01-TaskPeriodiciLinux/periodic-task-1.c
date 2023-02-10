#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
//La prima verisone, prevede l'uso della funzione di sleep (con la precisione dei microsecondi) per "spegnere" il processo, fino a
//che non si verifica nuovamente il momento dell'attivazione
//USO DELLE FUNZIONI DELLO STANDARD UNIX 

//Sono necessarie queste due variabili globali che vengono usate per andare a calcolare il tempo necessario per "dormire"
static long next_period;
static int period;

//Anche la wait risulta essere molto semplice
void wait_next_activation(void)
{
    //Mi definisco la struttura necessaria per poter considerare tutti i parametri
    struct timeval t1;

    //Prendo il tempo corrente e lo converso
	gettimeofday(&t1,NULL);
    
    //Imposto il valore di now, in base ai microsecondi
	long now = t1.tv_sec*1000000+t1.tv_usec;

    //Vado a calcolare il tempo restante per dormire, come differenza tra il valore dell'istante del periodo 
    //successivo e il tempo corrente
	long delay = next_period - now;

    //Aggiorno il valore del periodo al successivo, potendo quindi calcolare il ritardo per dormire
	next_period += period;

    //Eseguo una stampa a video, nel caso in cui ci sia un delaxy che è minore di 0, in questo caso vuol dire che si è
    //accumulato un ritardo
	if (delay<0) printf("delay: %ld\n",delay);

    //Eseguo la sleep per il tempo che mi avanza fino al prossimo periodo, sempre espresso in microsecondi
	usleep(delay);

    //ovviamente la sleep, quand le viene dato un valore negativo, non eseguirà
}


//La funzione di start è molto semplice, non fa altro che tenere a mente il periodo e il prossimo momento di attivazione
void start_periodic_timer(uint64_t offs, int t)
{
    //La struttura timeval è quella che viene usata nello standard UNIX, per tenere conto del periodo
	struct timeval t1;

    //Leggo l'ora attuale
	gettimeofday(&t1,NULL);

    //Converto il valore dei secondi in microsecondi, impostandoli in una variabile apposita
	long now = t1.tv_sec*1000000+t1.tv_usec;

    //A questo punto, imposto le variabili globali

        //Definisco il successivo istante di attivazione, andando a sommare al tempo attuale anche l'offset
	    next_period = now + offs;

        //Tengo traccia del valore del periodo prefissato e inviatomi dalla funzione main
        period = t;

}

//Quindi viene specificato il job del task, che esegue un conteggio rispetto al tempo medio
//tra l'inizio del job, una variabile che tiene conto del tempo attuale e un conteggio dei cicli
static void job_body(void)
{
 
    static int cnt;

    //Come si vede, per le variabili che devono ospitare il tempo in milliseconti, uso questa apposita variabile che mi permette
    //Solo start viene definito come static, perchè non deve essere cancellata quando esco dalla funzione (Lo stesso vale per
    //per il conteggio precedente)
    static uint64_t start;
    uint64_t t;

    struct timeval tv;

    //Alla prima attivanzione, mi vado a salvare l'istante della prima esecuzione del task
    if (start == 0) {
        gettimeofday(&tv, NULL);
        //Il valore viene considerato in millisecondi
		start = tv.tv_sec * 1000ULL + tv.tv_usec / 1000ULL; //ms
    }

    //Nel caso non sia la prima attivazione, vado a leggere l'ora attuale    
    gettimeofday(&tv, NULL);
    //Converto l'ora in milliseocndi, salvati in una variabile apposita
    t = tv.tv_sec * 1000ULL + tv.tv_usec / 1000ULL;

    //Condizione che viene eseguita solo ad ogni 100 cicli
    if (cnt && (cnt % 100) == 0) {
        //Il conteggio che viene qui eseguito, ogni 100 cicli, dovrebbe stampare il valore del periodo, quindi 10 ms
        //può essere usato come un meccanismo per verificare la correttezza
        printf("Avg time: %f\n", (double)(t - start) / (double)cnt);
    }
    cnt++;
}

int main()
{
    //Il main, inizializza i valori di partenza e del periodo
    //impostando la partenza dopo 2 secondi e il periodo a 10ms
    start_periodic_timer(2000000, 10000);

    while(1) {
        //Metto la wait, prima del corpo del job, in modo che questo possa partire in modo sincronizzato con le aspettative
        //attendendo quindi i 2 secondi
        wait_next_activation();
        
        job_body();
    }

    return 0;
}



/*ATTENZIONE
Non sempre questa soluzione è quella ottimale, in quanto potrebbe capitare che il task venga prelazionato quando si va a calcolare
il delay, in questo caso, quando vado a prendere l'ora corrnte con il get time, ho un valore maggiore rispetto a quello che ci si
aspetta
QUINDI -> Ho un accumulo di ritardo, che non potra più essere recuperato
*/
