#include <stdio.h>
#include <errno.h>


#include "semafor.h"

int wait_sem(int semID, int semNum){
   
    struct sembuf buf;

    //Modifico i campi della struct che mi occorrono per effettuare l'operazione di wait

    buf.sem_num=semNum;
    buf.sem_flg=0; 
    buf.sem_op=-1;

    int err=semop(semID, &buf, 1);

    if(err<0){
        return -1;
    }

    else{
        return 0;
    }

}

int signal_sem(int semID, int semNum){
    //Effettuo le medesime operazioni come sopra!
    struct sembuf buf; 

    buf.sem_num=semNum; 
    buf.sem_flg=0;
    buf.sem_op=1;

    int err=semop(semID, &buf, 1);

        if(err<0){
            return -1;
        }

        else{
            return 0;
        }
  
}