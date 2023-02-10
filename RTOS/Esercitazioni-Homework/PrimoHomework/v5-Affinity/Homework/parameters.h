#define TICK_TIME 100000
#define SENSOR_QUEUE_NAME   "/sensor_queue"
#define ACTUATOR_QUEUE_NAME "/actuator_queue"
#define REFERENCE_QUEUE_NAME "/reference_queue"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 500
#define MAX_MSG_SIZE 16
#define BUF_SIZE 5

//Definizione delle code che usate dal thread di guardia e dal thread di segnalazione
#define GUARD_QUEUE_NAME "/wd_queue"
#define GUARDIA_QUEUE_RESPONSE "/wd_response"

//PARAMETRI CHE OCCRORRONO AL DS:  
//Coda da usare sia per le richieste che per le risposte al DS!
#define DS_QUEUE_REQUEST "/req_ds"
#define DS_QUEUE_RESPONSE "/res_ds"
    
