//Specifica delle funzioni che fanno parte della lista a doppio puntatore

//Il costruttore deve essere implementato in modo che la testa e la coda puntano l'un l'altro!
template<typename Type>
DLinkedList<Type>::DLinkedList():size1{0}{

    head= new Node<Type>;   //Creo quindi i due nodi principali!
    trailer = new Node<Type>;

    head->next=trailer; //Il valore successivo dell'header deve puntare al triler
    head->prev=nullptr; //Quello precedente, a puntatore nullo! (Prima dell'header non ho elementi)

    trailer->prev=head; //Il valore precedente del trailer lo devo far puntare all'header
    trailer->next=nullptr; //Il valore successivo del trailer è nullo, non ci sono elementi dopo questo!

}


//Distruttore della lista che rimuove ogni elemento dalla lista
template<typename Type>
DLinkedList<Type>::~DLinkedList(){
    while(!empty()){
        removeFront();};

    delete head;    //Quando poi ho rimosso tutti gli elementi devo andare ad eliminare i puntatori che ho creato!
    delete trailer;
}

//Devo cambiare questa funzione, se la lista è vuota, essa deve puntare al trailer!
template<typename Type>
bool DLinkedList<Type>::empty(){
    return head->next==trailer;
}

//Specifica della funzione che aggiunge un  elemento tra due nodi!!
template <typename Type>
void DLinkedList<Type>::add(Node<Type>* v, Type& ele){
    //Definizione di un nuovo puntatore ad un nodo
    Node<Type>* nuovo= new Node<Type>;

    //Vado ad inserire l'elemento all'interno del nodo 
    nuovo->element=ele;

    //Ora bisogna andare a linkare l'oggetto all'interno della lista 
    nuovo->next=v;
    nuovo->prev=v->prev;

    v->prev->next=nuovo;  //Aggiornameto del puntatore dell'elemento che precede il nuovo elemento!
    v->prev=nuovo;       //Aggiornamento del punatore che punta all'elemento precedente!

    ++size1;
    
    
}


template<typename Type>
void DLinkedList<Type>::addFront(Type& elem){
  
  //Nella funzione che aggiunge l'elemento all'inizio della lista posso usare la funzione che ho definito prima 
  add(head->next, elem);

}

template<typename Type>
void DLinkedList<Type>::addBack(Type& elem){
//Allo stesso modo facciamo per la funzione che aggiunge alla fine!
    add(trailer, elem);
}

template<typename Type>
void DLinkedList<Type>::insertOrder(Type& elem){

    Node<Type>* salvo=trailer->prev;

        while(salvo!=head){

            if(elem<salvo->element){
                break;
            }

            salvo=salvo->prev;

        }

        add(salvo->next, elem);

    
}

template <typename  Type>
void DLinkedList<Type>::remove(Node<Type>* punt ){
    if(empty()){
        throw std::invalid_argument("La lista è vuota");
    }

    //Vado a modificare i puntatori dei nodi in modo da eliminare l'elemento!
    Node<Type>* primo=punt->prev;
    Node<Type>* sec=punt->next;

    primo->next=sec;
    sec->prev=primo;

    delete punt;

    --size1;
    
}

template<typename Type>
void DLinkedList<Type>::removeFront(){
    
    remove(head->next);

}

template<typename Type>
void DLinkedList<Type>::removeBack(){
    remove(trailer->prev);

}


template<typename Type>
const Type& DLinkedList<Type>::getFront(){
    if(!empty()){
   
    return head->next->element;

    }
    //Se la lista è vuota, lancio l'eccezione!
    else{

        throw std::invalid_argument("La lista è vuota!");

    }
}

//Definisco la funzione che serve per prelevare l'elemento dalla fine della lista 
template <typename Type>
const Type& DLinkedList<Type>::getBack(){
    if(!empty())
        return trailer->prev->element;

    else 
        throw std::invalid_argument("La lista è vuota!");
}

//Overload dell'operatore [] per accedere agli operandi!
template<typename Type>
const Type& DLinkedList<Type>::operator[](int i){

    //Ora che ho una lista che posso scorrere dall'inizio alla fine, posso andare a sfruttare le caratteristiche per partire dall'ultimo elemento
    //e visualizzarli tutti

    Node<Type>* elemento={nullptr};
    Node<Type>* segno={trailer};

    for(int k=0; k<=i; k++){
        elemento=segno->prev;
        segno=elemento;
    }

    return segno->element;

}





template <typename Type>
int DLinkedList<Type>::size(){
    return size1;
}