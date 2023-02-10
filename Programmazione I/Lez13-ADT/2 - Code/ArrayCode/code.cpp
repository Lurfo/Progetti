//Specifica delle funzioni della classe Queue!

//Specifica del costruttore della coda!
//Vado ad inizializzare tutti gli elementi della classe!
template <typename T>
Code<T>::Code(int grand): head{0}, tail{0}, size1{0}, tot{grand}, arr{new T[grand]}{}

//Specifica del distruttore della classe! 
//Deve eliminare la memoria che è stata riservata per l'array!
template <typename T>
Code<T>::~Code(){
    delete arr; 
}

//Funzione che restituisce l'elemento puntato da head!
template <typename T>
const T& Code<T>::front() const{
    return arr[head];
}


//Funzione che va ad inserire l'elemento nella posizione puntata dall'header!
template <typename T>
void Code<T>::enqueue(const T& elemento){
    
    //Verifico che la coda non sia ormai alla fine dell'array e che la lista non sia ormai completa 
    //NB: La condizione "head!=tail+1" è quella che definisce se la lista è ormai piena!
    //Ovviamente la prima condizione è quella che verifica che la coda non sia alla fine!
    if(tail!=tot-1 && head!=tail+1 ){
        arr[tail]=elemento; 
        tail++;
        size1++;
    }

    //Dobbiamo andare poi a verificare, che se il puntatore di coda si trova alla fine e l'header non si trova più nel punto iniziale, possiamo andare a spostare
    //il puntatore di coda all'inizio dell'array, in questo modo abbiamo un buffer circolare e possiamo andare a riempire nuovamente la coda fino a quando
    //essa non è piena!
    else if(tail==tot-1 && head!=0){
        arr[tail]=elemento;
        tail=0;
        size1++;
    }

    //Ovviamente se nessuna delle due condizioni di sopra non sono rispettate, allora lancio un'eccezione!
    else{
        throw std::invalid_argument("La lista è piena!");
    }


}



//Vado a specificare la funzione che ha il compito di andare ad elimnare l'elemento puntato dal puntatore di lista
//NB: il puntatore di lista, non elimina il valore che esso punta, ma viene spostasto e poi viene riscritto quando ci troviamo ad inserire 
//Un nuovo elemento!
template <typename T>
void Code<T>::dequeue(){

    //Dobbiamo verificare che la lista non sia vuota, in questo modo possiamo andare a spostare il puntatore!
    if(!empty()){
        //Spostando il puntatore all'elemento successivo, devo andare a decrementare la dimensione della coda!
        arr[head]=0;
        head++;
        size1--;
    }
    
    //Quando siamo arrivati alla fine della coda e devo eliminare l'ultimo elemento, lo sposto all'inizio!
    else if(head==tot-1){
        arr[head]=0;
        head=0;
        size1--;
    }

    else if(empty()){
        throw std::invalid_argument("Guarda che la coda è vuota!\n");
    }

    //Come ho visto sopra, per eliminare il velore contenuto in quella posizione lo sostituisco con uno 0!
}


//La funzione che controlla se la lista è vuota può verificare che la variabile della dimensione sia uguale a 0!
template <typename T>
bool Code<T>::empty() const{
    return size1==0;
}

