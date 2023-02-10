//Vado a specificare tutte le funzioni dello stack usando sempre dei template!

//Il costruttore mi deve impostare la capacità dello stack, l'array di elementi che mi sevono e il numero di elementi inizializzato a zero!
template <typename T>
Stack<T>::Stack(int cap): capacity{cap}, arr{new T[cap]}, primo{-1}{} 
//Front è posizionato a -1 in modo che quando effettuo il primo push esso diventa 0, indicando che 0 è la posizione del primo elemento!

//Specifica del distruttore che deve andare ad eliminare l'array che ho definito!
template<typename T>
Stack<T>::~Stack(){
    delete[] arr; //In questo modo andiamo ad eliminare tutti gli elementi che sono contenuti all0interno dell'array!
}

//Specifica della funzione di inseimento!
template <typename T>
void Stack<T>::push(const T& e){
    //Bisogna inserire l'elemento all'interno dello stack

    //Controllo che il numero di elementi non sia ormai raggiunto!
    if(size()==capacity){
        throw std::runtime_error("Ormai lo stack è pieno!");
    }

    //Se il numero di elementi non è uguale alla capacità dello stack, allora posso inserire l'elemento all'interno dell'array!
    else{
        //Uso il pre incremento in modo che il valore del vada ad incrementare a mano a mano che andiamo ad inserire elementi all'interno dello stack!
        arr[++primo]=e;
    }
}

//Specifica della funzione pop, essa non fa altro che andare ad spostare l'indice del front!
//Alla fine è impossibile andare ad elimare un elemento all'interno dell array!
template <typename T>
void Stack<T>::pop(){

    //Controlliamo piuttosto che l'array non sia già vuoto
    if(empty()){
        throw std::runtime_error("Lo Stack è ormai vuoto!");
    }

    else{
        --primo; //Se lo stack non è vuoto vado ad decrementare il valore dello stack!
    }

}


//Specifica della funzione che restituisce il valore che si trova in cima allo stack!
template <typename T> 
const T& Stack<T>::front() const{
    //Uso il valore del front per restituire il valore che si trova in cima allo stack

    if(empty()){
        throw std::runtime_error("Impossibile, lo stack è vuoto!");
    }
    
    else
        return arr[primo];
}

//specifica della funzione che ha il compito di controllare che la lista non sia vuota!
template<typename T>
bool Stack<T>::empty() const{
    return primo==-1;   //Sappiamo che se la lista è vuota il front dello stack è uguale a -1, quindi posso usarlo come valore sentinella per controllare
                        //che lo stack sia vuoto!


}

