#define TICK_TIME 100000
#define SENSOR_QUEUE_NAME   "/sensor_queue"
#define ACTUATOR_QUEUE_NAME "/actuator_queue"
#define REFERENCE_QUEUE_NAME "/reference_queue"
#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 1000
#define MAX_MSG_SIZE 16
#define BUF_SIZE 5

//Definizione del nome della coda del thread di guardia
#define GUARD_QUEUE_NAME "/wd_queue"

#define GUARDIA_QUEUE_RESPONSE "/wd_response"