#include <stdio.h>
#include <conio.h>
#include <time.h>


//Includo le funzionlità che mi occorrono da freeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

//Definisco il periodo dell'encoder che vado a MODIFICARE OPPORTUNAMENTE per ogni task!
//Esso è pari a 5 ms, ma lo definisco in funzione del tick di sistema!
//Lo vado a definire come un intero unsigned long!
#define ENC_PERIOD pdMS_TO_TICKS(5UL)

//definisco anche la priorità dell'encoder
//Lo pongo usando una priorità intermedia tra i livelli di priorità disponibili
#define ENC_PRIORITY (tskIDLE_PRIORITY+4)

//----------------------------------------------------------------------------
//Definisco le satruture che devono utilizzare i vari task

//Struttura per l'encoder
struct enc_str
{
    uint32_t slit;		//valori oscillanti tra 0 e 1
    uint32_t home_slit;	//1 se in home, 0 altrimenti

    //Vado a definire il lock nella struttura
    //ATTENZIONE: Nel main si deve chiamare la funione "xSemaphoreCreateMutex" per ottenere
    //un handle con cui fare riferimento al semaforo!
    SemaphoreHandle_t lock;
};
//Dichiaro la struttura come globale (può essere vista da tutti i thread e statica)
static struct enc_str encData;


//Struttura per il conteggio dei fronti di salita
struct _rising_edge {
    //Conteggio fronti di salita
    uint32_t conteggio;

    //Mutex per mutua esclusione
    SemaphoreHandle_t lock;
};
static struct _rising_edge contFronte;


//Struttura che conteggia il tempo tra due posizioni di home!
struct _round_time {
    //Misura il tempo trascorso in home, uso un valore intero, in quanto esprimo il valore in nanosecondi!
    uint32_t diff;

    //Mutex 
    SemaphoreHandle_t lock;
};
static struct _round_time contGiro;


//Aggiungo la struttura necessaria per il calcolo dello slack time dei task
struct slackTime {
    uint32_t value;

    SemaphoreHandle_t lock;

};

//Devo dichiarare due struct per lo slack del task che conteggia i fronti e quello per la home!
static struct slackTime slackFront; 
static struct slackTime slackHome;

//ATTENZIONE: Quanto detto per il lock della struttura endData, vale ovviamente anche per le restanti!


//---------------------------------TASKS' SIGNATURES---------------------------------------------------

//Di seguito sono riportate le signature dei vari task, seguendo uno standard proprio di FreeRTOS

//Task che conta i fornti di salita
static void frontCount(void* pvParameters);

//Task che conta il tempo tra due posizioni di home!
static void homeCount(void* pvParameters);

//Task di controllo che stampa a video i valori delle strutture
static void view(void* pvParameters);

//ATTENZIONE:  Di seguito dichiaro la signature dell'encoder, il task che genera dunque i fornti
//e anche le posizioni di home
static void encoderTask(void* pvParameters);

//Definisco il task di diagnostica che mi va a stampare a video gli slack time sei task
static void diagnostic(void* pvParameters);

//---------------------------------MAIN-----------------------------------------

void main_homework() {

    //Come prima cosa, imposto i lock delle strutture sopra dichiarate!
    encData.lock = xSemaphoreCreateMutex();
    if (encData.lock == NULL) {
        perror("Errore creazione lock encData\n"); 
        exit(1);
    }

    contFronte.lock = xSemaphoreCreateMutex(); 
    if (contFronte.lock == NULL) {
        perror("Errore creazione lock contFront\n");
        exit(1);
    }

    contGiro.lock = xSemaphoreCreateMutex();
    if (contGiro.lock == NULL) {
        perror("Errore creazione lock contGiro\n");
        exit(1);
    }

    slackFront.lock = xSemaphoreCreateMutex(); 

    if (slackFront.lock == NULL) {
        perror("Errore creazione del lock slackFront\n"); 
        exit(1);
    }

    slackHome.lock = xSemaphoreCreateMutex(); 

    if (slackHome.lock == NULL) {
        perror("Errore creazione del lock slackHome\n");
        exit(1);
    }



    printf("Creazione task encoder\n");

    //Creazione del task encoder
    xTaskCreate(encoderTask, "Encoder", configMINIMAL_STACK_SIZE, NULL, ENC_PRIORITY, NULL); 

    printf("Creazione task front\n");

    //Vado a creare il task che conteggia il fronte
    //NOTA: Questo task ha una priorità maggiore rispetto al task precednete in quanto il suo periodo risulta esser la metà del precedente
    //Questo è fondamentale in quanto gli permette di conteggiare sia quando il valore è alto, sia quando il valore è basso!
    xTaskCreate(frontCount, "FrontCounter", configMINIMAL_STACK_SIZE, NULL, ENC_PRIORITY +1, NULL);

    printf("Creazione task home\n");

    //Anche questo task, ha una priorità più alta del task encoder, avendo il medesimo periodo del front
    //così, posso essere sicuro di controllare l'istante in cui è 1 e l'istante in cui è 0, senza rischiare
    //di perdere qualche conteggio
    xTaskCreate(homeCount, "HomeCounter", configMINIMAL_STACK_SIZE, NULL, ENC_PRIORITY + 1, NULL);

    printf("Creazione task visualizzatore\n");
    //Creo il task che visualizza i dati
    //NOTA BENE: Questo ha una priorità minore rispetto all'encoder in quanto il suo periodo è DOPPIO
    //Infatti deve soltando andare a visualizzare dei valori, non è necessario che abbia un periodo molto breve
    xTaskCreate(view, "Visualizzatore", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY+1, NULL);


    printf("Creo il task di diagnostica\n");
    //Vado a creare il task di diagnostica
    xTaskCreate(diagnostic, "Diagnostica", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

    //A QUESTO PUNTO: Dopo la creazione dei task, è necessario AVVIARE LO SCHEUDLER
    vTaskStartScheduler(); 


    //Se lo scheduler sia avvia correttamente, il main si sospende e quindi le righe di cui sotto non verranno mai
    //eseguite!
    for (;;) {
        printf("ERROR!\n");
    }

}



//----------------------------SPECIFICA DEI VARI TASK!----------------------------------------
static void encoderTask(void* pvParameters) {

    printf("EncoderPartito\n");

    //Faccio un semplice uso dei parametri (che non ho fornito) in modo da evitare che il compilatore
    //mi segni un possibile errore
    (void) pvParameters;

    //Inizializzo i valori della mia struttura
    //Nella take e nella give del semaforo, non devo fornire alcun valore per quanto riguarda il tempo
    xSemaphoreTake(encData.lock, NULL);
    encData.slit = 0; 
    encData.home_slit = 0;
    xSemaphoreGive(encData.lock);

    //A questo punto posso andare a definire una serie di valori che mi occorrono per il conteggio
    uint32_t count = 0; 
    uint32_t slit_count = 0;
    uint32_t prev_slit = 0;

    //Mi raco un valore randomico per il calcolo degli RPM

    srand(time(NULL));
    
    uint32_t semi_per = (rand() % 10) + 1;

    //Mi definisco le variabili per il mio task periodico

    //Variabile che mantiene l'istante della prossima attivazione!
    //lo definisco come non costante in quanto varia ogni volta
    TickType_t xNextWake;

    //Variabile che mantiene il periodo del task!
    //Periodo definito prima usando una define!
    const TickType_t xBLockTime = ENC_PERIOD;

    //A questo punto, mi prendo il valore del tick attuale, da quando ho fatto perire lo scheduler
    xNextWake = xTaskGetTickCount();

    for (;;) {

        //printf("Encoder dorme\n");

        //Utilizzo la funzione di vTaskDelayUntil, che fa in modo che il task attenda la prossima attivazione
        //prima di eseguire il suo job
        //Con la chiamata di questa funzione xBlockTime viene sommato ad xNextWake e il task viene sospeso
        //proprio fino al valore di xNextWake
        vTaskDelayUntil(&xNextWake, xBLockTime);

        //printf("Encoder si risveglia\n");

        //Si può eseguire il job del task

        //Prendo il semaforo
        xSemaphoreTake(encData.lock, portMAX_DELAY);

        //Controllo il valore del fronte di salita
        prev_slit = encData.slit;

        //Mi definisco la funzione di onda quadra
        if (count % semi_per == 0) {
            encData.slit++;
            encData.slit %= 2;
        }

        //Effettuo un conteggio del fronte di salita
        if (prev_slit == 0 && encData.slit == 1) 					//fronte di salita
            slit_count = (++slit_count) % 8;

        //Appena sono arrivato ad 8 fronti di salita, arrivo nella posizione di home
        if (slit_count == 0){ 
            encData.home_slit = encData.slit;}

        //Altrimenti esco dall'home
        else encData.home_slit = 0;

        //printf("%d:\t\t %d %d\n",count,enc_data.slit,enc_data.home_slit);	//DEBUG encoder
        count++;

        //Posso quindi lasciare il semaforo!
        xSemaphoreGive(encData.lock);
    }
}

//Conteggio dei fronti di salta
static void frontCount(void* pvParameters) {

    printf("FrontCount partito\n");

    (void)pvParameters;

    xSemaphoreTake(contFronte.lock, portMAX_DELAY);
    contFronte.conteggio = 0;
    xSemaphoreGive(contFronte.lock);


    //Variabili che occorrono al task per il suo funzionamento, mantengono il fronte precedente e quello attuale
    uint32_t prevFront = 0; 
    uint32_t now;

    //Mi definisco i valori opportuni per il task periodico
    TickType_t xNextWake; 

    //Valore da usare per il calcolo dello slackTime;
    TickType_t fin;

    //Imposto il periodo come la metà di quello dell'encoder (2500)
    const TickType_t xBlockTime = ENC_PERIOD / 2;

    //Mi prendo il tempo attuale
    xNextWake = xTaskGetTickCount();

    //Faccio pertire il ciclo del job del task
    for (;;) {

        //printf("contatoreFronte dorme\n");

        //Eseguo la delay
        vTaskDelayUntil(&xNextWake, xBlockTime); 

        //printf("contatore fronte si risveglia\n");

        //Prendo il lock sul mutex
        xSemaphoreTake(encData.lock, portMAX_DELAY);

            //Prendo il valore attuale
            now = encData.slit;

            //Vado a varificare se effettuare il conteggio o meno
            if (now != prevFront && prevFront == 0) {
                //Solo in questo caso, vado ad aumentare il conteggio della struttura apposita
                xSemaphoreTake(contFronte.lock, portMAX_DELAY);
               
                contFronte.conteggio++;

                xSemaphoreGive(contFronte.lock);
            }

            //Modifico il valore del precedente valore con quello attualmente letto
            prevFront = now;

        xSemaphoreGive(encData.lock);

        //Dopo che ho concluso il mio job, posso calcolare lo slack (tempo rimanente) del processo
        //Prendo il TickCount attuale
        fin = xTaskGetTickCount();

        //Controllo che il valore di fine sia minore si quello del periodo
        if ((xNextWake+xBlockTime) >= fin) {
            xSemaphoreTake(slackFront.lock, portMAX_DELAY);
            slackFront.value = (xNextWake+xBlockTime) - fin;
            xSemaphoreGive(slackFront.lock);
        }

    }

}

static void homeCount(void* pvParameters) {

    printf("homeCount Partito\n");

    (void)pvParameters;

    //Mi definisco due valori che l'inizio e la fine del conteggio
    TickType_t start, arrival, fin;

    //Mi definisco i valori precedenti e attuali della home
    uint32_t prev = 0, now = 0;

    //Utilizzo un valore per verificare se è la prima volta che sono nella home!
    int32_t firstTime = 1;

    TickType_t xNextWake; 

    const TickType_t xBlockTime = ENC_PERIOD / 2;

    xNextWake = xTaskGetTickCount();

    for (;;) {

        //printf("Contatore home dorme\n");

        vTaskDelayUntil(&xNextWake, xBlockTime);

        //printf("Contatore home si sveglia\n");

        xSemaphoreTake(encData.lock, portMAX_DELAY);
            
        //Mi salvo il valore della home
        now = encData.home_slit;

        //Controllo se sono sul fornte di salita
        if (now != prev && prev == 0) {
            
            //Controllo se è la prima misura che sto effettuando
            if (firstTime) {
                
                start = xTaskGetTickCount();

                //printf("Start time:%u\n", start);

                firstTime = 0;

            }

            else {
                
                //Calcolo il tempo di arrivo
                arrival = xTaskGetTickCount();

                //printf("Arrival time %u\n", arrival);

                //Imposto la differenza nella struttura
                xSemaphoreTake(contGiro.lock, portMAX_DELAY);
                contGiro.diff = arrival - start;
                xSemaphoreGive(contGiro.lock);

                //Faccio in modo che l'arrival, diventi il nuovo valore di start!
                start = arrival;

            }

        }

        //Imposto il precedente valore della home
        prev = now;

        xSemaphoreGive(encData.lock);


        //Calcolo dello slack
        fin = xTaskGetTickCount();

        if ((xNextWake+xBlockTime) >= fin) {
            xSemaphoreTake(slackHome.lock, portMAX_DELAY);
            slackHome.value = (xNextWake+xBlockTime) - fin;
            xSemaphoreGive(slackHome.lock);
        }

    }


}

static void view(void* pvParameters) {

    printf("view partito\n");

    (void)pvParameters;

    //Variabili che occorrono al task
    uint32_t conteggio = 0;

    uint32_t val = 0;

    //Valore per verificare le rotazioni al minuto!
    uint32_t rmp = 0;

    //Valori per impostare il task
    TickType_t xNextWake;

    //In questo caso, il periodo del task è il doppio rispetto a quelli precedenti
    const TickType_t xBlockTime = ENC_PERIOD * 2;

    xNextWake = xTaskGetTickCount();

    while (1) {

        //printf("visualizzatore dorme\n");

        vTaskDelayUntil(&xNextWake, xBlockTime);

        //printf("Visualizzatore si sveglia\n");

        xSemaphoreTake(contFronte.lock, portMAX_DELAY); 
        conteggio = contFronte.conteggio;
        xSemaphoreGive(contFronte.lock);

        xSemaphoreTake(contGiro.lock, portMAX_DELAY);
        //Essendo val espresso come un multiplo del tick, allora per ottenere il valore in ms
        //posso andare a moltiplicarlo per il rate del tick!
        val = contGiro.diff * configTICK_RATE_HZ;
        xSemaphoreGive(contGiro.lock);

        if(val!=0) rmp = (unsigned int) (60 * 1000000 / val);

        printf("Valore di conteggio del thread RT1: %u\n", conteggio);
        printf("Valore della differenza di tempo di RT2: %u\n", rmp);
        


    }

}


//UNA NOTA SULLO SLACK TIME: Lo slack time medio, risulta avere un valore pari a 2 tick (cioè 2ms).
//Però, a causa della risoluzione del tick di sistema, non è possibile apprezzare le piccolissime variazioni di questo: di fatti il task, terminerebbe entro i primi microsecondi dalla sua esecuzione,
//questo quindi porterebbe ad un valore sicuramente minore di 2ms (cosa che al contrario è possibile verificare nella sua versione in c). Nel caso in esame, quando si prende il conteggio del tick finale
//risulta che esso sia ancora uguale al tick di attivazione, a causa della scarsa risoluzione, nonostante abbia eseguito per qualche microsecondo.
//Questo fa si che abbiamo uno slack time fisso di 2!
static void diagnostic(void* pvParameters) {

    (void)pvParameters;

    uint32_t avg = 0;

    int32_t  cnt = 0;

    TickType_t xNextWake;

    const TickType_t xBlockTime = ENC_PERIOD * 2;

    xNextWake = xTaskGetTickCount();

    for (;;) {

        vTaskDelayUntil(&xNextWake, xBlockTime);

        //Mi prendo i valori delle due variabili e li salvo nella variabile avg
        xSemaphoreTake(slackFront.lock, portMAX_DELAY); 
        xSemaphoreTake(slackHome.lock, portMAX_DELAY); 
        avg += (slackFront.value + slackHome.value) / 2;//Ottengo così la media espressa in millisecondi
        xSemaphoreGive(slackHome.lock);
        xSemaphoreGive(slackFront.lock);

        //Aumento il valore del conteggio
        cnt++;

        //printf("CONTEGGIO DIAGNOSTICA:%u\n", cnt);

        //Quando sono arrivato a 100, posso stampare la media di 100 slack time
        if (cnt == 100) {

            avg = avg / cnt;

            printf("******SLACKTIME: %u ticks******\n", avg);

            cnt = 0;
        }

    }

}