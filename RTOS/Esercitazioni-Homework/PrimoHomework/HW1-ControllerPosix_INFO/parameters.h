//Definizioni

//Tempo con cui gira l'impianto pari a 100ms (Il tempo è in microsecondi)
#define TICK_TIME 100000

//Nomi per le code, permessi e grandezza delle code
#define SENSOR_QUEUE_NAME   "/sensor_queue"
#define ACTUATOR_QUEUE_NAME "/actuator_queue"
#define REFERENCE_QUEUE_NAME "/reference_queue"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 1000
#define MAX_MSG_SIZE 16

//Dimensione del buffer usato dal task di acquisizione!
#define BUF_SIZE 5

//Il controllore gira con un periodo di TICK_TIME*BUF_SIZE 