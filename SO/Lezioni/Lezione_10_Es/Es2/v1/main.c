#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

#define DIM_VETT 5

//Specifica della struttura che mi occorre per "condividere i dati tra i thread!"
//In particolare la definisco come una struct globale, poichè i thread condividono tra di loro tutti i dati che sono presenti 
//nell'area globale
typedef struct{
    
    //Definisco i due vettori
    int* a; 

    int* b;

    //Definisco poi la variabile  in cui andare ad inserire il risultato
    int sum;

} dati;


dati p;

//Devo inizializzare anche la variabile che mi occorre come mutex!
//Anche qui la specifico come variabile globale, in modo che possa essere visualizzata da tutti
pthread_mutex_t mutex;

//Mi definisco la signature della start function dei thread
void* ProdottoScalare(void* arg);


int main(){

    srand(time(NULL));

    //Mi definisco un array che contiene l'id dei thread
    //In particolare devo creare un numero di thread pari al numero di locazioni dei due vottori, poichè ogni thread lavora
    //sulla locazione di un vettore!
    pthread_t idThr[DIM_VETT];

    //Effettuo l'allocazione dinamica dei vettori che mi occorrono
    p.a=(int*) malloc(DIM_VETT*sizeof(int));

    p.b=(int*) malloc(DIM_VETT*sizeof(int));

    //Inizializzo le variabili contenute nella memoria!
    p.sum=0;


    //Inizializzo i due vettori con i valori che mi interessano!
    for(int i=0; i<DIM_VETT; i++){
        p.a[i] = rand() % 10 +i;
        p.b[i] = rand() %20 + (i+1);
    }

    //Ho inizializzato i vettori, mi definisco l'attributo che specifica che i thread che vado a creare debbano essere joinable
        //Devo creare la variabile
        pthread_attr_t attr; 

        //Inizializzo l'attributo
        pthread_attr_init(&attr); 

        //Lo imposto come joinable
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

        //In questo modo ho specificato che l'attributo indica che il thread è joinable!

    //Vado ad inizializzare la variabile che occorre usare com mutex!
    //Ovviamente posso andare a sfruttare l'apposita funzione di inizializzazione
    pthread_mutex_init(&mutex, NULL);

    //Mi definisco una variabile che per "tenere" lo stato del thread dopo a sua terminazione!
    int stato;
    
    //Posso andare a creare i thread
    for(int i=0; i<DIM_VETT; i++){

        //Posso dunque andare a creare i thread!
        //In particolare, condivito ai thread, come argomento, la loro posizione!
        stato=pthread_create(&idThr[i], &attr, ProdottoScalare, (void*) i);

        if(stato){
            printf("Il thread, è terminato con stato: %d\n", stato); 
                exit(1);
        }

    }


    //Il thread principale deve andare ad attendere i suoi figli!
    for(int i=0; i<DIM_VETT; i++){
       
        pthread_join(idThr[i], (void*) &stato);

        printf("Terminato il thread: %ld, con stato: %d\n", idThr[i], (int) stato);

    }

    //Il thread principale mostra il risultato

    printf("Ti mostro i due vettori:\n"); 

    printf("a: "); 

    for(int i=0; i<DIM_VETT; i++){
        printf("%d;", p.a[i]);
    }

    printf("\n");

    printf("b: "); 

    for(int i=0; i<DIM_VETT; i++){
        printf("%d;", p.b[i]);
    }

    printf("\n");

    printf("Il loro prodotto scalare è: %d\n", p.sum);


    //Alla fine, devo andare a liberare la memoria e andare ad eliminare il mutex e la variabile che ho usato come attributo
    pthread_attr_destroy(&attr); 

    pthread_mutex_destroy(&mutex); 

    free(p.a); 
    free(p.b);

    //Devo far terminare il thread principale, sempre tramite la funzione pthread_exit
    pthread_exit(0);

}



void* ProdottoScalare(void* arg){


    //L'argomento della funzione è pari alla posizione che il deve andare a considerare nel vettore!
    int pos = (int) arg; 


    int myprod=0; 

    //Posso dunque adare a fare la somma dei due vettori
    myprod= p.a[pos]*p.b[pos];
    
    //Per andare a modificare la variabile condivisa, vado a considerare il mutex 
    pthread_mutex_lock(&mutex); 
    p.sum+=myprod;
    pthread_mutex_unlock(&mutex); 

    pthread_exit(0);

}
