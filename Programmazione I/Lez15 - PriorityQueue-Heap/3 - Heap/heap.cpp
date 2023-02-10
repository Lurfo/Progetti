#include "heap.h"
#include <stdexcept>
#include <iostream>

//Specifica del costruttore della struttura dati!
Heap::Heap(int eleme): numeri{eleme}, posiz{1}, elm{new int[eleme]}{
   //Per comodità inizializzo tutti gli elementi dell'array a 0!
    for(int i=0; i<eleme; i++){
        elm[i]=0;
    }

}

//Distruttore della classe, elimino la memoria allorata per il dispositivo!
Heap::~Heap(){
    delete elm;
}


//Specifica della funzione che aggiunge un elemento all'interno dell'array!
void Heap::add(const int num){
  
    if(posiz==size()){
        throw std::invalid_argument("Guarda che ormai è pieno!");
    }

    else{
        //Vado ad aggiungere un elemento all'interno dell'array! Andando ad incrementare la posizione di riferimento ogni volta e controllando che 
        //l'arry non sia ormai pieno!
        elm[posiz++]=num;
    }

}

//LEFT E RIGHT restituiscono la posizione del figlio di destra e quello di sinistra!
int Heap::left(int pos){
    return 2*pos;
}

int Heap::right(int pos){
    return 2*pos+1;
}


//Specifica della funzione che va a generare l'array!
void Heap::buildHeap(){
    //In particolare si ha una cosa molto importante, cioè vale a dire che SI PARTE DIRETTAMENTE DALLA POSIZIONE N/2 (In quanto è inutile partire
    //direttamente dalle foglie) poichè il nodo che si trova alla posizione n/2 è L'ULTIMO NODO CHE POTREBBE AVERE DEI FIGLI!
    //Facilmente si può infatti andare a vedere che tutti gli elementi che si trovano alle poszioni maggiori di n/2 è impossibile che abbiano dei figli!
    //ESSI INFATTI SARANNO SICURAMENTE DEI FIGLI DEGLI ELEMENTI CHE SONO COMPRESI TRA 1 ED N/2!
    int grand; 

    grand=size()/2;

    //Partendo dunque da questa posizione n/2, posso scorrere a retroso gli elementi e andare a utilizzare la funzione heapfy!
    //Inoltre, il partire dagli elementi che si trovano alle ultime posizioni, mi permette, proseguendo nella funzione buildheap, 
    //che invocando gli elementi sulle posizioni che si trovano più in alto, nei livelli sottostanti ho già degli heap, come richiede la funzione 
    //heapfy! 
    //(Ovviamente questo perchè le ultime posizioni che hanno dei nodi figli, i suoi figli sono ovviamente già dei sottoalberi! Con uno schema è molto
    //più semplice andare ad individuare questo legame!)
    for(int i=grand; i>=1; i--){
        //Come argomento della posizione heapfy devo andare ad inviare la posizione dell'elemento!
        heapfy(i); //Vado a richiamare la funzione che organizza l'heap!
    }

    
}

void Heap::heapfy(int pos){
    //Definisco i figli del nodo che ho inviato!
    //Ovviamente la definizione dei figli serve per trovare il confronto!
    int l=left(pos);
    int r=right(pos);

    //Mi salvo la posizione dell'elemento che sarà il più grande, perchè serve per andare a scambiare le posizioni degli elementi!
    int maggiore{0};

    //IL PROCESSO DI SEGUITO SERVE PER ANDARE A TROVARE IL MASSIMO TRA I 3 ELEMENTI (Il nodo padre e i 2 figli!)
    //(Devo comunque sempre controllare che il figlio di destra e quello di sinistra esistono, usado la prima condizione dell'if!)

    //Controllo se il figlio di sinistra sia maggiore dell'elemento padre
    if(l<=size() and elm[l]>elm[pos]){
        //se si mi salvo la sua posizione!
        maggiore=l;

    }

    else{
        //altrimenti mi salvo la posizione del padre!
        maggiore=pos;
    }

    //DOPO AVER CONTROLLATO IL LATO DI SINISTRA CONTROLLO QUELLO DI DESTRA!

    //controllo sempre che il valore di destra sia maggiore di quello che ho come nodo padre!
    if(r<=size() and elm[r]>elm[maggiore]){
        //Se si mi salvo il valore della posizione del figlio di destra
        maggiore=r; 
    }
    
    //A questo punto, se il valore maggiore corrisponde ad uno dei due figli, devo andare a scambiare uno dei figli con il padre!
    if(maggiore!=pos){       
        int mantengo=elm[pos]; 

        elm[pos]=elm[maggiore]; 

        elm[maggiore]=mantengo;

        //Dopo aver scambiato il valore del figlio con quello del padre, devo però andare a verificare che il sottoalbero di sinistra o destra
        //(in base a quale figlio è maggiore dell'altro!!!), abbia ancora la proprietà di heap, se non possiede questa proprietà allora la funzione 
        //procede a "sistemare" il sottoalbero in modo che esso continui ad avere la proprità di heap!
        heapfy(maggiore);
        //In quest caso vediamo quindi il motivo per cui la funzione heapfy è definita come ricorsiva, a mano a mano che vado più avanti, se
        //trovo un valore minore, devo andare a richiamare la funzione heapfy su ogni elemento che si troa in basso per vedere se continua a rispettare 
        //la proprità di heap!
    }

    

}

int Heap::size() const{
    return numeri;
}


void Heap::vedo() const{
    for(int i=1; i<numeri; i++){
        std::cout<<elm[i]<<((i!=numeri-1) ? ", " : " ");
    }
    
    std::cout<<std::endl;
}













 