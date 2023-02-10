#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <stdio.h>

#define NUM_THR 4
#define INTERV 10

//Definisco la struttura!
typedef struct{

    int* a; 

    int* b;


    long int sum; 

    //Inserisco nella struttura l'intervallo di valori su cui deve "andare a lavorare" il thread
    int interv;

}dati; 

//Mi specifico la mia mia struttura
dati p;

//Mi creo la variabile da usare come mutex 
pthread_mutex_t mutex;

//Mi definisco la signature dello start point del thread
void* ProdScal(void *p); 


int main(){

    srand(time(NULL)); 

    //Mi specifico l'array che deve contenere l'identificatore dei thread che vado a creare!
    pthread_t idThr[NUM_THR];

    //Inizializzo la variabile che devo utilizzare come mutex
    pthread_mutex_init(&mutex, NULL);

    //Definizione della variabile attr, per specificare che il thread è joinable!
    pthread_attr_t attr; 

    pthread_attr_init(&attr); 

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE); 
    
    //Vado ad allocare i valori necessari!
    p.a = (int*) malloc(NUM_THR*INTERV*sizeof(int));

    p.b = (int*) malloc(NUM_THR*INTERV*sizeof(int));

    //Inizializzo le variabili della mia struttura
    p.sum=0; 
    
    p.interv=INTERV;

    //Vado a riempire i due vettori!
    for(int i=0; i<NUM_THR*INTERV; i++){
       
        p.a[i]=rand() %10 + 1; 
        p.b[i]=rand() %20 + 1;

    }

    //A questo punto, posso andare a creare i thread che mi occorrono!
    for(int i=0; i<NUM_THR; i++){

        //Invio al thread il suo numero, che gli permette poi di andare a "creare" il suo intervallo specifico!
        //Tendendo sempre presente che il numero di elementi che deve essere presente in ogni intervallo
        //è sempre presente all'interno della struttura che ho definito (interv)!
        //Utilizzando quello, il thread deve poi andarsi a costruire il suo intervallo specifico!
        if(pthread_create(&idThr[i], &attr, ProdScal, (void*) i)){
            perror("Errore nella creazione thread!\n"); 
                exit (1); 
        }

    }

    //La variabile che contiene lo stato, deve sempre essere un puntatore a void, la funziona pthread_exit, infatti restituisce
    //sempe questo tipo di variable!
    void *stato;

    //Il thread main, deve attendere la terminazione dei vari thread!
    for(int j=0; j<NUM_THR; j++){

        pthread_join(idThr[j], (void*) &stato);
        printf("Terminato il thread %d, con stato: %d\n", j, (int) stato);
    }

    //Il thread principale, mostra i vettori e il prodotto vettoriale
    printf("Ti mostro i vettori:\n"); 

    printf("Vettore a: ");

    for(int i=0; i<INTERV*NUM_THR; i++){
        printf("%d; ", p.a[i]);
    }

    printf("\n");

    printf("Vettore b: ");

    for(int i=0; i<INTERV*NUM_THR; i++){
        printf("%d; ", p.b[i]);
    }

    printf("\n");


    printf("Ti mostro il valore della somma: %ld\n", p.sum);

    //A questo punto, devo andare a liberare la mia memoria!
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&mutex);

    free(p.a);
    free(p.b);

    //Faccio terminare il thread principale!

    pthread_exit(0);

}



//Vado a specificare la starting function del thread!
void* ProdScal(void *arg){

    //Come parametro della fuzione ho il valore con cui ricavare l'offset
    int val = (int) arg;

    long mysum = 0; 

    int myStart, end, lung;

    lung=p.interv;

                            //Calcolo dell'intervallo di valori che mi occorre
    
    //Calcolo del punto di partenza
    myStart = val*(p.interv);

    //Calcolo l'offset del mio punto di arresto, considerando: 
        //Il punto di partenza
        //A cui devo sommare la lunghezza dell'intervallo di mio interesse
    end = lung+myStart;

    //NOTA BENE: 
        //La struttura, come detto prima, è direttamente accessibile dai thread, in particolare, quando devo accedere i
        //in lettura, non ho alcuna necessità di andare a utilizzare il mutex, proprio perchè non devo modificare nulla!

    //Una cosa corretta da fare, sarebbe "salvare" l'indirizzo di memoria puntato dal vettore, in modo da non dover accedere ogni
    //volta alla struttura!

    int *x, *y; 

    x=p.a;
    y=p.b;

    printf("Sono il thread %d, mi occupo dell'intervallo: [%d, %d]\n", val, myStart, end-1);

    //Faccio la somma sugli intervalli
    for(int i=myStart; i<end; i++){
        mysum+=(x[i]*y[i]);
    }

    printf("Valore della mia somma: %ld, thread: %d\n", mysum, val);

                            //La modifica della variabile della struttura, prevede invece l'uso di un mutex
                            //In modo da poter regolare la competizione tra i vari thread!

    //Entro nel mutex e modifico il valore della somma
    pthread_mutex_lock(&mutex);
        p.sum+=mysum;
    //Lascio il mutex
    pthread_mutex_unlock(&mutex);

    //Posso terminare il thread
    pthread_exit((void *)0);

}