//Specifica delle funzioni dichiarate all'interno della classe 

template <typename T>
DList<T>::DList(): num{0}{
  
    //Devo andare a specificare il costruttore, facendo in modo che il trailer e l'head si puntino vicendevolmente!
    head=new Node<T>;
    trailer= new Node<T>; 

    //Ovviamente l'header non deve puntare a nulla che si trovi prima di lui!
    head->prev=nullptr;

    //Così come il trailer non deve puntare a nulla che si trovi prima dopo di lui!
    trailer->next=nullptr;

    head->next=trailer;
    trailer->prev=head;

}

template <typename T>
DList<T>::~DList(){
    //Per il distruttore usiamo sempre le funzioni che ho definito per la classe!
    while(!empty()){removeFront();}
}



//Specifica della funzione che aggiunge un elemento all'interno della lista in una specifica posizione!
template <typename T>
void DList<T>::add(Node<T>* nodo, const T& e){
    //Creo un nuovo nodo in cui inserire l'elemento!
    Node<T>* elm= new Node<T>; 

    //Salvo elemento!
    elm->elemento=e; 

    //Inizializzo i puntatori!
    //Sto aggiungendo il nodo alla sinistra del nodo che gli ho inviato!
    elm->next=nodo; 
    elm->prev=nodo->prev;

    nodo->prev->next=elm;
    nodo->prev=elm;

    ++num;
    
}



template <typename T>
void DList<T>::addFront(const T& e){
    //Sfrutto la funzione che ho definito per agiungere un elemento alla destra dell'header!
    //Dunque in cima alla lista!

    //Poichè la funzione aggiunge un elemento ALLA SINISTRA di un nodo, devo inviare l'elemento che si trova subito dopo l'header!
    add(head->next, e);

}

template <typename T>
void DList<T>::addBack( const T& e){
    //Uso sempre la funzione che ho definito per aggiungere un elemento!
    //Aggiungendo ALLA SINISTRA DEL NODO CHE INVIO, basta che mando il valore del trailer!
    add(trailer, e);
}

template <typename T>
const T& DList<T>::front() const{
    return head->next->elemento;
}

template <typename T>
const T& DList<T>::back() const{
    return trailer->prev->elemento;
}

template <typename T>
bool DList<T>::empty() const{
    return head->next==trailer;
}

template <typename T>
int DList<T>::size() const{
    return num;
}


//Specifica della funzione che rimuove un elemento dalla lista!
//ESSA TOGLIE DIRETTAMENTE IL NODO CHE VADO AD INVIARE, MODIFICANDO I PUNTATORI!
template <typename T>
void DList<T>::remove(Node<T>* nodo){
    
    //Come prima cosa andiamo a controllare che la lista non sia già vuota!
    if(empty()){
        throw std::invalid_argument("Guarda che la lista è vuota!");
    }

    else{  //Altrimenti procediamo con la rimozione del valore!
        Node<T>* old=nodo; 

        //Vado quindi a modificare gli indirizzi dei nodi che precedono e seguono il nodo da eliminare!
        old->prev->next=old->next;
        old->next->prev=old->prev;

        delete old; 
    
        
    }

    --num;

}

//Uso la funzione definta sopra per andare a eliminare gli elementi!
template <typename T>
void DList<T>::removeFront(){

    //Per rimuovere il primo elemento, devo effettivamente inviargli il primo elemento della lista!
    remove(head->next);
}

template <typename T>
void DList<T>::removeBack(){
    //Per rimuovere il 
    remove(trailer->prev);
}

