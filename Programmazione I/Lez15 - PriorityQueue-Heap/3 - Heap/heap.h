//BISOGNA TENERE A MENTE UNA COSA MOLTO IMPORTANTE!
//Un heap è un albero in cui ogni elemento contenuto in un nodo è sempre maggiore di tutti i suoi figli! (controlla slide 24!)


#include <array>


using std::array;


#ifndef HEAP_H
#define HEAP_H
//Per definire la nostra struttura dati Heap, vado a creare una classe che permette di evere determinate funzioni che gestiscono tutti i dati privati!
class Heap{
    private: 

        //Dichiaro un puntatore ad intero che va ad inizializzare un array, per andare ad inserire, gli elementi!
        int* elm;
        //Va a ricordare il numero di elementi che vado ad inserire, essendo che questa struttura si basa su un array allora resta sempre fissa 
        //non deve cioè essere modificata!
        int numeri;
        //Questo valore è quello che va a ricordarsi in che posizione devo aggiungere l'elemento all'interno dell'array ogni volta che chiamo la funzione
        //add!
        int posiz;

        //Funzione heapfy è quella che va a controllare che un nodo soddisfi la proprietà di HEAP!
        //Ho un elemento dell'array a[i]; 
        //Posso definire i suoi due figli, uno di destra e uno di sinistra, tramite le funzioni left e right, che sono definite sotto
        //(In particolare ho che, usando gli indici degli array posso andare a trovare facilmente le posizioni dei 2 figli!)
        //Tuttavia potrebbe essere che l'elemento a[i], può essere maggiore dei suoi figli!
        //Dunque la funzione Heapfy va a spostare in basso questo elemento (sostituendolo con il velore di uno dei 2 figli!), fino a quando la proprietà
        //heap non viene soddisfatta!
        //In particolare ho che la funzione heapfy, non è quella che crea l'heap, si impegna solo a traformare l'array nell'heap!
        //Per tale motivo viene definta come funzione privata, poichè deve essere poi utilizzata da una seconda funzione "build heap" che va a 
        //creare il nostro heap!
        //Da sola non può essere utilizzata in quanto va a considerare che alcuni dei sottoalberi, siano già degli heap!
        //dunque, va ad unire questi due heap, andando dunque ad unirli!
        //In particolare, sfrutta una definizione iterativa!
        void heapfy(int);
        int left(int); 
        int right(int);

    public:

        //Costruttore della classe
        //NOTA BENE: Ogni volta che andiamo a specificare la dimensione dell'array, dobbiamo sempre aggiungere uno alla dimensione di cui ho bisogno!
        //Proprio perchè devo andare ad inserire gli elementi all'interno dell'heap partendo dalla posizione 1, andando quindi a escludere la posizione 0!
        //Posizione che non viene ovviamente toccata!
        Heap(int =11);
        //Distruttore della classe! 
        ~Heap(); 

        //Funzione che ha il compito di andare ad inserire gli elementi all'interno dell'array!
        //Inizializzando quindi tutti gli elemnenti all'interno della struttura!
        void add(const int); 
        
        //ATTENZIONE! 
            //NELLA CLASSE HEAP, NON COMPARE LA FUNZIONE BUILDHEAP, MA ABBIAMO UNA FUNZIONE CHE, QUANDO ANDIAMO AD INSERIRE GLI ELEMENTI
            //FA QUESTO PROVESSO IN AUTOMATICO! MA LA FUNZIONE HEAPFY SERVE PER ESSERE UTILIZZATA IN TANTI ALTRI PROCESSI!
        //Bisogna andare a specificare una funzione che va a "trasformare" un array in un heap!
        //Tale funzione ha proprio il compito di andare a creare un heap, sfruttando la funzione heapfy che ho definito come variabile privata 
        //Tale funzione va quindi a richiamare la funzione heapfy, in modo che venga inizializzato il nostro array in un heap!
        void buildHeap(); 
        //Non ha degli elementi come argomento di funzione poichè essa va ad agire direttamente sugli elementi del vettore!
        
        //Funzione che va a restituire la dimensione della struttura!
        int size() const;

        //Funzione che mostra a video gli elementi della struttura!
        void vedo() const;
};

#endif