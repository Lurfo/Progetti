#ifndef _PARAMETERS_H
#define _PARAMETERS_H

#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <fcntl.h>
#include <string.h>
#include <sched.h>


struct shared_int
{
	int value;
	pthread_mutex_t lock;
};

cpu_set_t cpu;

#define TICK_TIME 100000
#define SENSOR_QUEUE_NAME "/sensor_queue"
#define ACTUATOR_QUEUE_NAME "/actuator_queue"
#define REFERENCE_QUEUE_NAME "/reference_queue"
#define WATCHDOG_QUEUE_NAME "/wdog_queue"
#define PREVIUOS_QUEUE_NAME "/previous_queue"
#define DSREQUEST_QUEUE_NAME "/req_ds"
#define DSRESPONSE_QUEUE_NAME "/res_ds"

#define QUEUE_PERMISSIONS 0660
#define MAX_MESSAGES 500
#define MAX_MSG_SIZE 16
#define BUF_SIZE 5

#endif
