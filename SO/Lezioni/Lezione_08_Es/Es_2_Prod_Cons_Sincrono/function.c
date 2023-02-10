#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <wait.h>
#include <string.h>

#include "function.h"

//Specifico le variabili delle code, di servizio come variabili globali statiche, all'interno di questo file, poichè solo queste
//funzioni hanno bisogno di accedervi, non ho bisogno di specificarle nel main
static int service1;
static int service2;

//Funzioni di servizio
void initService(){
    //init mi occorre solo per ottenere il valore dell'id
    service1=msgget(IPC_PRIVATE, IPC_CREAT|0660); 
    service2=msgget(IPC_PRIVATE, IPC_CREAT|0660);

}

void removeService(){

    msgctl(service1, IPC_RMID, NULL);

    msgctl(service2, IPC_RMID, NULL);


}

//Specifica delle funzioni di send e receive
void sendSincrona(Messaggio* mess, int queue){
    Messaggio m1, m2; 

    //Il primo messaggio è quello per dire che si sta facendo una richiesta per inviare
    //lo faccio con un messaggio dal tipo vuoto
    m1.type=REQUEST_TO_SEND;

    //invio una send con un messaggio vuoto, per chiedere di inviare
    //La funzione di blocco se la coda è troppo piena
    msgsnd(service1, (void*) (&m1), SIZE, 0);

    //Aspetto che arrivi una conferma di invio sul secondo canale service2
    //La funzione di ricezione, controlla nella coda 2, se è presente un messaggio con un tipo uguale a OK_TO_SEND
    //in particolare, la funzione di ricezione è bloccante, attende che sia inviato un messaggio prima di proseguire
    msgrcv(service2, (void*) (&m2), SIZE, OK_TO_SEND, 0);

    //Se ottengo il permesso di poter inviare, lo invio
    msgsnd(queue, (void*) (mess), SIZE, 0);

}


//La receive bloccante ha una struttura molto simile!
void receiveBloccante(Messaggio* mess, int queue, int tipoMess){

    Messaggio m1, m2;

    //Riceve il messaggio che si è disponibili alla scrittura
    //La receive fa in modo che il consumatore attenda fino a che non ci si un produttore pronto ad inviare la richiesta
    msgrcv(service1, (void*)(&m1), SIZE, REQUEST_TO_SEND, 0);

    //Appena arriva la richiesta di produzione, invio la risposta che è possibile procedere
    //La invio sul canale 2
    m2.type=OK_TO_SEND;
    msgsnd(service2, (void*) (&m2), SIZE, 0);

    //Posso mettermi in attesa del messaggio!
    //Mi blocco fino a quando non ricevo il messaggio
    //Mi metto in attesa del messaggio con il tipo che mi interessa
    msgrcv(queue, (void*)(mess), SIZE, tipoMess, 0); 
}

void produttore(int queue){
    //Il produttore definisce il messaggio
   
    char mess[MAX];

    strcpy(mess, "Sono una persona che non sa");

    //Inserisco il messaggio nella sua struttura
    //Preparo il pacchetto
    Messaggio m; 

    m.type=MESSAGGIO; 
    strcpy(m.string, mess);

    //Invio il messaggio con la mia funzione di send
    sendSincrona(&m, queue);
    printf("Messaggio prodotto!\n");
}




void consumatore(int queue){
    Messaggio m; 

    //Attendo il messaggio con la receive bloccante
    receiveBloccante(&m, queue, MESSAGGIO);

    //Stamtpo il contenuto del messaggio
    printf("Ho letto il messaggio %s\n", m.string);
}