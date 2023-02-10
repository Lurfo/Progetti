/* Standard includes. */
#include <stdio.h>
#include <conio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "semphr.h"

/* Numero di task */
#define TASK_NUM 6

/* Cardinalità del contatore */
#define COUNTER_CARDINALITY 8

/* Periodo di Base */
#define BASE_PERIOD_MS 10

/* Indice del task di stampa (Polling Server) */
#define PRINT_TASK_POSITION 0

/* Priorit� dei task */
#define	FIRST_COUNTER_TASK_PRIORITY		( tskIDLE_PRIORITY + TASK_NUM )
#define PRINT_TASK_PRIORITY		( tskIDLE_PRIORITY + FIRST_COUNTER_TASK_PRIORITY + 1 ) 

/*-----------------------------------------------------------*/

/* Definizione dei task da implementare */
static void countTask(void* pvParameters);
static void printTask(void* pvParameters);

/*-----------------------------------------------------------*/

/* Array dei periodi */
static int periods[TASK_NUM];

//To do...
/* 
 * Definire la risorsa condivisa contatore "counter" (vettore di interi) 
 * e un mutex "xSemaphore" per gestire la mutua esclusione nell'accesso al contatore
 */

//Vettori di interi da usare, per mantenere il 
struct {

	int counter[6];
	SemaphoreHandle_t xSemaphor;

} sharedCounter;



/*-----------------------------------------------------------*/

void main_counter(void)
{
	/* Inizializzare i periodi dei task */
	for (int i = 0; i < TASK_NUM; i++) {

		if (i == 0) {
			periods[i] = BASE_PERIOD_MS;
		}
		else {
			periods[i] = periods[i - 1] * COUNTER_CARDINALITY;
		}
	}

	// To do...
	/*
	 * Inizializza il contatore "counter" a 0
	*/

	for (int i = 0; i < 6; i++) {
		sharedCounter.counter[i] = 0;
	}
	
	// To do...
	/* 
	 * Creare il Mutex tramite le API freeRTOS e
	 * Verificare che il Mutex sia stato creato correttamente
	*/

	sharedCounter.xSemaphor = xSemaphoreCreateMutex();

	if (sharedCounter.xSemaphor == NULL) {
		perror("Semaforo non creato correttamente\n"); 
		exit(1);
	}


	
	// To do...
	/* 
	 * Creare i task periodici secondo Rate Monotonic
	 * Creare il Polling Server con priorit� pi� alta di tutti i task periodici
	 * Avviare lo scheduler 
	*/

	//Creazione dei task di conteggio
	for (int i = 0; i < 6; i++) {
		
		xTaskCreate(countTask, "CountTask" + i, configMINIMAL_STACK_SIZE, (void *) i, FIRST_COUNTER_TASK_PRIORITY-i, NULL);
	}


	//Vado a creare il Polling Server
	xTaskCreate(printTask, "PollingServer", configMINIMAL_STACK_SIZE, (void*)PRINT_TASK_POSITION, PRINT_TASK_PRIORITY, NULL);

	//Necessario andare a far partire lo scheduler!
	vTaskStartScheduler();


	for (;; );
}
/*-----------------------------------------------------------*/

static void countTask(void* pvParameters)
{
	// To do...
	/*
	 * Inizializzare le variabili utili all'implementazione di un task periodico e
	 * Gestire il parametro di ingresso
	*/

	//Mi definisco il valore della prossima attivazione
	TickType_t xNextWakeTime;

	int index = (int) pvParameters;

	const TickType_t xBlockTime = pdMS_TO_TICKS(periods[index]);

	for (;; )
	{
		// To do...
		/*
		 * Incrementare periodicamente il contatore utilizzando il mutex per mantere la mutua esclusione
		*/

		vTaskDelayUntil(&xNextWakeTime, xBlockTime);

		//Prendo il semaforo
		xSemaphoreTake(sharedCounter.xSemaphor, portMAX_DELAY);

			//Eseguo il conteggio

		//Controllo, se � 7, lo porto nuovamente a 0
		if (sharedCounter.counter[index] >= COUNTER_CARDINALITY - 1) {
			sharedCounter.counter[index] = 0;
			}

		//Altrimenti incremento
		else {
			sharedCounter.counter[index]++;
		}

		xSemaphoreGive(sharedCounter.xSemaphor);

	}
}
/*-----------------------------------------------------------*/

static void printTask(void* pvParameters)
{
	// To do...
	/* 
	 * Inizializzare le variabili utili all'implementazione del Polling Server e
	 * Gestire il parametro di ingresso
	*/
	TickType_t xNextWakeTime;

	int index = (int)pvParameters;

	//Imposto il periodo minore rispetto a tutti gli altri, avendo questo la priorit� maggiore
	const TickType_t xBlockTime = pdMS_TO_TICKS(periods[index]/ 2);

	for (;; )
	{
		//To do...
		/* 
		 * Implentare il comportamento periodico 
		*/

		//Attendo la prossima attivazione
		vTaskDelayUntil(&xNextWakeTime, xBlockTime);

		/* Verificare che � stata premuto un input da tastiera */
		if (_kbhit() != 0)
		{
			/* Rimuovere il carattere letto dall'input buffer */
			(void)_getch();

			// To do....
			/* 
			 * Stampare il contenuto del contatore utilizzando il semaforo per accedere in maniera mutuamente esclusiva alla risorsa 
			*/

			//Entro nel mutex e mi prendo i valori del buffer
			xSemaphoreTake(sharedCounter.xSemaphor, portMAX_DELAY); 
			
				printf("Valori: ");

				for (int i = 5; i!=0; i--) {
					printf("%d", sharedCounter.counter[i]);
				}
			
				printf("\n"); 

			xSemaphoreGive(sharedCounter.xSemaphor);

			

		}
	}
}