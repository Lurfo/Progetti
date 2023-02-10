#include "semafor.h"

int wait_sem(int semid, int semNum){
    struct sembuf buf;

    buf.sem_num=semNum; 
    buf.sem_flg=0; 
    buf.sem_op=-1; 

    if(semop(semid, &buf, 1)<0){
        return -1;
    }

    else{
        return 0;
    }

}

int signal_sem(int semid, int semNum){
    struct sembuf buf;

    buf.sem_num=semNum;
    buf.sem_flg=0;
    buf.sem_op=1;

    if(semop(semid, &buf, 1)<0){
        return -1;
    }

    else{
        return 0;
    }
    
}