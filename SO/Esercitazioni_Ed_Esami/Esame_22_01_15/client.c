//Il client ha solo bisogno della coda di messaggi

#include "header.h"
#include <time.h>

#define TOT_INVII 4

int main(){

    srand(time(NULL)*getpid());

    //Ottengo chiave e id della coda di messaggi
    key_t kMess = ftok(PATH, CHAR_C); 

    int idMess = msgget(kMess, 0);

        //printf("[CLIENT %d] Coda ottenuta, con id: %d, chiave: %d\n", getpid(), idMess, kMess);

    Mess m;

    int ret; 

    m.type=SDT_TYPE;

    for(int i=0; i<TOT_INVII; i++){

        //Il client imposta il messaggio di richiesta, inserendo due numeri casuali
        m.val1 = rand() % 10;
        m.val2 = rand() % 10;

        //Invio il messaggio di richiesta
        ret = msgsnd(idMess, (void *) &m, SIZE(Mess), 0); 

            printf("[CLIENT %d] Messaggio inviato, con valori %d, %d\n", getpid(), m.val1, m.val2);

            if(ret<0){
                perror("Errore invio del messaggio di richiesta\n"); 
                    exit(1);
            }

        //Attesa di un tempo casuale 
        sleep(rand()%2+1);

    }

    //Dunque,termino il programma 
    return 0;

}