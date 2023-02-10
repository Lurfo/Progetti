//Specifica delle funzioni che mi occorono
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include  <time.h>

#include "header.h"


//Le funzioni di lettura e di scrittura, sono implementate usando un monitor
void scrittura(MeteoM *p, int *temp, unsigned int *umid, unsigned short *piog){

        //Per controllare i parametri passati alla funzione
        //printf("[METEO %d dentro scrittura] Temperatura: %d, umidità: %d, piog: %s\n", getpid(), *temp, *umid, ((*piog == 1) ? "si" : "no"));

    //Entro nel monitor 
    enter_monitor(&(p->m));

        //Controllo della condizione tramite un while 
        while(p->numLettori>0){
            //Ci sono lettori, mi sospendo 
            wait_condition(&(p->m), VC_Scrittori);

        }
        
        //Se sono qui, sono sbloccato, incremento il numero di scrittori
        p->numScrittori++; 

    //Posso lasciare il monitor per effettuare la scrittura 
    leave_monitor(&(p->m)); 

    //Produco i valori
    p->temperatura = *temp; 
    p->umidità = *umid; 
    p->pioggia  = *piog; 

    printf("[METEO %d, dentro scrittura] Temp: %d, umidità: %u, piogg: %s\n", getpid(), p->temperatura, p->umidità, ((p->pioggia==1) ? "si" : "no"));
    
    //Ritorno nel monitor per modificare le variabili 
    enter_monitor(&(p->m)); 

        //Diminuisco il numero di scrittori 
        p->numScrittori--; 

        //Segnalo tutti i lettori che attedono
        signal_all(&(p->m), VC_Lettori);

    //Posso lasciare il monitor
    leave_monitor(&(p->m));


}


void lettura(MeteoM *p, int *temp, unsigned int *umid, unsigned short *piog){

    //Entro nel monitor
    enter_monitor(&(p->m)); 

        //Controllo se ci sono degli scrittori
        while(p->numScrittori>0){
            //Se ci sono scrittori, mi sospeno sulla condizione
            wait_condition(&(p->m), VC_Lettori);
        }

        //Se sono qui, sono sbloccato, incremento il numero di lettori 
        p->numLettori++; 

    //Esco dal monitor ed effettuo la lettura 
    leave_monitor(&(p->m)); 

    *temp = p->temperatura; 
    *umid = p->umidità; 
    *piog = p->pioggia; 

        //Per controllare la consumazione corretta
        //printf("[UTENTE %d dentro lettura] Temperatura: %d, umidità: %d, piog: %s\n", getpid(), *temp, *umid, ((*piog == 1) ? "si" : "no"));

        
    //Ritorno nel montior 
    enter_monitor(&(p->m)); 

        //Diminuisco il numero di lettori
        p->numLettori--; 

            //Se sono l'ultimo lettore, segnalo gli scrittori
            if(p->numLettori==0){
                signal_condition(&(p->m), VC_Scrittori);
            }

    //Dunque, posso uscire dal monitor
    leave_monitor(&(p->m));

}

//Il processo meteo, genera le informazioni ogni 2 secondi
void meteo(MeteoM *m){

    srand(time(NULL)*getpid());

    //Specifica delle variabili che il processo va a modificare

    int tem;

    unsigned int umid; 

    unsigned short piog;

    //La funzione meteo, effettua 20 produzioni una volta ogni 2 secondi
    for(int i=0; i<NUM_SCRITTURE; i++){
        
        //Dunue, genero i valori causali
        tem = rand() % 101 - 50;

        umid = rand() % 101; 

        piog = rand() % 2;

            //Per controllare le variabili prodotte
            //printf("[METEO %d funz meteo] Temperatura: %d, umidità: %d, piog: %s\n", getpid(), tem, umid, ((piog == 1) ? "si" : "no"));

        //Invio i valori alla funzione di scrittura 
        scrittura(m, &tem, &umid, &piog);

        //Dunque attendo 2 secondi 
        sleep(2);

    }

}



void utenti(MeteoM *m){

    int tem; 
    unsigned int umid; 
    unsigned short piog; 

    //L'utente, effettua 10 letture, chiamando la funzione apposita
    for(int i=0; i<NUM_LETTURE; i++){

        lettura(m, &tem, &umid, &piog); 
            
            printf("[UTENTE %d funz utenti] Temperatura: %d, umidità: %d, piog: %s\n", getpid(), tem, umid, ((piog == 1) ? "si" : "no"));

        //prima della prossima lettura, l'utente aspetta sempre 1 sec
        sleep(1);

    }

}
