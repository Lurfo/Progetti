//Specifica delle funzioni wait e signal del semaforo!
#include "semafor.h"


int wait_sem(int semID, int semNum){
  
    struct sembuf buf;

    buf.sem_num=semNum; 
    buf.sem_flg=0;
    buf.sem_op=-1;

    if(semop(semID, &buf, 1)<0){
        return -1;
    }

    else{
        return 0;
    }

}



int signal_sem(int semID, int semNum){
   
    struct sembuf buf; 

    buf.sem_num=semNum;
    buf.sem_flg=0; 
    buf.sem_op=1;

    if(semop(semID, &buf, 1)<0){
        return -1;
    }

    else{
        return 0;
    }


}