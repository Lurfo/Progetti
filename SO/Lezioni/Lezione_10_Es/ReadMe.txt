I THREAD


Inizialmente esistevano delle librerie fortemente eterogenee implemetate per la gestione dei thread, per questo motivo
si cercò di definire una interfaccia standard per la loro gestione, questo fu possibile grazie all'introduzione della
libreria PTHREAD, con lo standard  IEEE POSIX 1003.1c

In particolare, nella libreria, i thread sono definiti come un insieme di procedure implementati nel linguaggio c e sono 
composti da un file header "pthread.h" ed una libreria


L'uso dei thread, come già definito sugli appunti, è molto importante poichè permette di ottimizzare le prestazioni: 
i thread sono infatti anche chiamati come: "Processi leggeri" -> La creazione di un thread non è così dispediosa quanto quella
di un processo, proprio perchè non hanno bisogno della definizione di tutta la struttura che sta dietro ad un processo

In particolare, anche la comunicazione tra i thread è molto più efficiente rispetto a quella che avviene tra due processi
perchè non richiede dell'ausilio di strutture di comunicazione IPC


All'interno della libreria pthread, sono presenti delle API (Ossia delle apposite interfacce) con le queli è possibile andare
a gestire numerosi aspetti dei thread: 
    
    -GESTIONE: 
        La creazione, eliminazione,join tra i thread ecc...
    
    -GESTIRE I MUTEX:
        Crearli ed eliminarli, inizializzazione, e lock ed unclock su variabili di mutua esclusione quando ho a che fare
        con una seione critic
    
    -GESTIONE DELLE VARIABILI CONDITION: 
        Creazione ed eliminazione, wait e signal su delle condizioni che sono definite dal programmtore






LA CREAZIONE DI UN THREAD
Avviene tramite l'apposita funzione: 
     int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);

 -Viene creato un thread la cui esecuzione ha inizio a partire dalla funzione speficata dal puntatore di tipo void "start_routine"

 -L'attributo "attr" serve ad impostare degli attributi del thread stesso, in particolare, questo punta ad una precisa
  "pthread_attr_t"

 -All'interno di "thread", viene invece "conservato" l'identificatore del thread che è stato creato, in modo che esso possa 
  essere usato quando voglio chiamare delle funzioni apposite su quel thread

 -"arg" contiene una serie di argomenti che possono essere passati alla funzione, dopo aver opportunamente effettuato un
   casting a "void*"




TERMINAZIONE DI UN THREAD: 

Può avvenire in 3 modalità differenti: 
    
    -Conclude la sua start_routine, dunque termina la sua esecuzione;

    -Viene chiamata la funzione pthread_exit(), che fa terminare il thread (come avveniva con exit per i processi); 

    -Può anche essere cancellato da altri thread, tramite la funzione pthread_cancel

    -Può anche terminare se il processo a cui appartiene termina con una exit() oppure il thread pricipale 
    (Quello a cui è affidato l'esecuzione del main ed è quello che viene creato sempre all'inizio dell'esecuzione) 
    effettua una return dal main()
    NOTA: Queste due cause di terminazione, fanno in modo che tutti i thread collegati a quel processo vengano terminati

La funzione pthread_exit(void *status) è quella che viene utilizzata per la terminazione esplicita di un thread (proprio come avveniva
con i proceissi quando usavo una exit), per questa ragione è buona norma usarla in tutti i thread per evitare degli errori
Essa prende in input un valore, status, che indica lo stato con cui il thread termina!

NOTA: Se viene usata nel thread principale, gli altri thread continueranno ad eseguire!



GUARDA ESEMPIO ES1 
(Specialmente il MAKEFILE)
In particolare, quello che è fondamentale quando utilizzo la libreria pthread è inserire all'interno del comando
di compilazione il flag "-pthread" questo perchè la libreria pthread è una libreria dinamica, che quindi viene linkata
a runtime!
Se non vado ad aggiungere questo flag, non posso usare la libreria!


PASSAGGIO DEI PARAMETRI
In particolar modo, tramite la funzione pthread_create, è possibile passare solo un parametro, per questo motivo
qando ho intenzione di passa due o più parametri, devo necessariamente andare a definire una struct, nella quale andare
a racchiudere i dati (allocandola tramite la funzione malloc, ottenendo così un puntatore alla struct) 
e passandola poi al thread tramite casting a void.
NOTA: Per poter usare la struct, il thread, deve andare ad effettuare il casting inverso, passando da (void*) a (struct*)!


JOIN 
Essa è un modo per poter andare a sincronizzare tra loro più thread!
Si effettua tramite la funzione
    
    int pthread_join(pthread_t threadId, void **retval);

Tale funzione fa in modo che il processo chiamante venga bloccato fino a che il pthread con l'id pari a "threadId" non 
termina la sua esecuzione
Inoltre, tramite questa chiamata, è possibile anche conoscere lo stato di terminazione del thread, tramite la variabile
"retval"
Un po' come la funzione wait!  

Attenzione: Per fare in modo che un thread, possa essere joinato, bisogna andare a specificare lo specifico attributo 
            quando il thread viene creato, andando ad impostare il valore apposito!

            Bisogna dunque:

                -Instanziare la variabile che funge da attributo; 

                -Inizializzarla mediante la funzione pthread_init(pthread_attr_t* att);

                -Usare la funzione  "int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);", che occorre
                 per andare a specificare che quell'attriuto inidica che il thread può essere joinable!
                 (Bisogna usare come identificatore in "detachstate" -> PTHREAD_CREATE_JOINABLE)
                
                -Infine si deve usare il riferimento all'attributo che ho definito, quando vado a creare il thread, in modo
                 che esso venga creato come detached!
                 (Bisogna cioè, specificarlo all'interno della funzione pthread_create())


CREAZIONE E DISTRUZIONE DI MUTEX

Nel caso in cui dovesse essere necessario, la libreria pthread, implementa anche delle funzioni che servono per andare
ad utilizzare dei semafori mutex, in modo da controllare la competizione tra i thread, quando lavorano su una variabile 
condivisa:

    -int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
        Questa funzione permette di inizializzare un mutex, che viene impostato già nello stato di sbloccato.
        (Dunque il primo thread che arriva, subito riesce ad entrare!)
      
        Come parametri di questa funzione si hanno: 
            -mutex, che è una variabile sulla quale la funzione di inizializzazione inserisce l'id del mutex che è stato creato

            -attr, serve per andare ad impostare gli attributi del mutex!

    -int pthread_mutex_destroy(pthread_mutex_t *mutex);
        Questa, invece viene semplicemente usata quando devo andare a deallocare un mutex!
        (Dove la variabile mutex, specifica l'id del mutex che voglio eliminare)

Per poter andare a sfruttare un mutex, i thread usano delle funzioni di signal and wait, come nel caso dei processi, ma queste
sono direttamente implementate nella libreria pthread
NOTA: Tutte le funzioni, hanno in ingresso l'id del mutex che voglio andare ad eliminare!

    -pthread_mutex_lock(pthread_mutex_t* mutex);
        Esattamente come la wait, viene utilizzata per acquisire l'accesso al mutex e quindi cominciare la sezione critica
        in particolare, se il mutex è già bloccato, allora il thread si blocca in attesa che venga liberato!

    -pthread_mutex_trylock(pthread_mutex_t *mutex);
        Questa è una funzione simile alla lock, solo che: NON È BLOCCANTE, se il mutex è già occupato, allora il thread
        non si blocca in attesa che venga liberato, ma restituisce un errore che ha come codice "EBUSY"

    -pthread_mutex_unlock(pthread_mutex_t *mutex);
        Questa invece serve per andare a liberare un mutex (uscendo dalla sezione critica) e sbloccare uno dei processi
        che si trova in attesa!


GUARDARE ESEMPIO ES2
(Prodotto scalare)
Nel quale si ha un esempio di come inizializzare i mutex per poterli sfruttare e anche come ottnere un attibuto
per specificare se un thread può essere joinable o meno!



CONDITION VARIABLES
In particolare, nella libreria pthread, si ha che la cooperazione può avvenire mediante delle Condition Variables, basandosi
sempre su una condizione!,

In particolare, le Condition Variabiles, possono essere usate assieme ai Mutex, definiti precedentemente
in questo modo, si possono andare a realizzare dei Monitor, tramite l'uso di due elementi definiti dalla libreria

-Creazione e Distruzione delle Variabili condition:
Le funzioni che vengono sfruttate sono molto simili a quelle che ho anche definito nel caso del mutex e dell'attr:

    -int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
        Dove ho che: 

            -cond, rappresenta l'identificare della variabile che ho creato, di tipo pthread_cond_t;
            la funzione infatti andrà ad inserire l'id nel riferimento che gli ho inviato

            -attr, rappresenta invece degli attributi da utilizzare per la varcond

        Questa funzione permette di creare la variabile condition, che viene impostata come "sbloccata", come con il mutex, 
        il primo che arrive, non si deve necessariamente mettere in attesa sulla condizione!

    -int pthread_cond_destroy(pthread_cond_t *cond);
        Tale funzione, serve per distruggere la CV specificata dall'ID cond


-La libreria Monitor, mette anche a disposizione delle funzioni di wait e di signal sulla CV: 

    -int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
        La funzione serve per effettuare una wait sulla CV, infatti essa ha in ingresso: 

            -Il riferimento alla CV; 

            -Il riferimento al mutex, che viene rilasciato automaticamente al momento della chiamata della funzione

    -int pthread_cond_signal(pthread_cond_t *cond);
        La funzione, serve per effettuare una signal sulla CV, in particolare, essa non ha in ingresso il mutex
        perchè viene già utilizzat come ingresso al monitor!


MONITOR CON I PTHREAD
Come anticipato, è possibile "realizzare" un monitor con la libreria pthread, sfruttando una combinazione di CV + Mutex!
Di fatto dunque, le funzioni che sfrutto per il monitor sono equivalenti a: 

    -enter_monitor() ---> pthread_mutex_lock(); 

    -wait_cond() ---> pthread_cond_wait(); 
        Questa blocca il chiamante sulla condizione e rilascia il mutex (cioè il thread esce dal monitor, come avviene
        di fatto quando ho a che fare con un monitor signal and continue!)

    -signal_cond() --->pthread_cond_signal(); 
        Quando è ricevuta la segnalazione sulla condizione, allora il thread viene sbloccato e il mutex viene nuovamente 
        "bloccato" per regolare l'ingresso al monitor!

    -leave_monitor() ---> pthread_mutex_unlock();

Posso quindi notare che le funzioni di ingresso al monitor e di uscita dal monitor, coincidono con le funzioni di lock 
ed unlock sul monitor!

In particolare, la tipologia di monitor che viene implemetata è un moniotr signal and continue, infatti: 

    -Il thread che effettua la segnalazione, continua la sua esecuzione, sempre all'interno del monitor

    -Il thread che effettua la wait sulla condizione, rimane in attesa fino a che il mutex non è rilasciato e dunque, deve
    rientrare nel monitor

    -In particolare siccome deve rientrare nuovamente nel monitor, allora è possibile che la sua condizione venga invalidata
    quindi è bene che il thread, controlli nuovamente la sua condizione! 
    (come nel caso dei processi, USO IL WHILE e non l'if!)

GUARDARE ESEMPI ES3, ES4 
Sull'uso del monitor, per implementare due problemi di tipo "Produttore/Consumatore", "Lettore/Scrittore"