#include "parameters.h"

int main(int argc, char **argv)
{

    char req_message[] = "REQUEST DIAGNOSTIC";
    char res_message[MAX_MSG_SIZE * 20];

    mqd_t req_ds;
    mqd_t res_ds;
    
    if ((req_ds = mq_open(DSREQUEST_QUEUE_NAME, O_WRONLY)) == -1)
    {
        perror("diag: mq_open (req_ds)");
        exit(-1);
    }

    if ((res_ds = mq_open(DSRESPONSE_QUEUE_NAME, O_RDONLY)) == -1)
    {
        perror("diag: mq_open (res_ds)");
        exit(-1);
    }

    if (mq_send(req_ds, req_message, strlen(req_message) + 1, 0) == -1)
    {
        perror("diag: send request (req_ds)");
        exit(-1);
    }

    if (mq_receive(res_ds, res_message, MAX_MSG_SIZE * 20, 0) == -1)
    {
        perror("diag: receive diagnostic (res_ds)");
        exit(-1);
    }

    printf("%s", res_message);

    if (mq_close(req_ds) == -1)
    {
        perror("diag: mq_close req_ds");
        exit(-1);
    }
    if (mq_close(res_ds) == -1)
    {
        perror("diag: mq_close res_ds");
        exit(-1);
    }

    return 0;
}