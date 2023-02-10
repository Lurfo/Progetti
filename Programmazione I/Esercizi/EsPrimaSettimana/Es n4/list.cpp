//SPECIFICA DELLE FUNZIONI DELLA CLASSE ITERATOR!
template <typename T>
LinkedList<T>::Iterator::Iterator(Node<T>* elm){
    punt=elm;
}

template <typename T>
T& LinkedList<T>::Iterator::operator*() const{
    return punt->element;
}

template <typename T> 
bool LinkedList<T>::Iterator::operator==(const Iterator& elm) const{
    return punt==elm.punt;
}

template <typename T>
bool LinkedList<T>::Iterator::operator!=(const Iterator& elm) const{
    return punt!=elm.punt;
}

template <typename T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++(){
    punt=punt->next;

    return *this;
}

template <typename T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator--(){
    Iterator salvo(punt); 
    punt=head;

    while(punt->next!=salvo.punt){
        punt=punt->next;
    }
    return *this;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int){
    Iterator salvo(punt); 
    punt=punt->next;
    return salvo;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator--(int){
    Iterator salvo(punt); 

    punt=head;

    while(punt->next!=salvo.punt){
        punt=punt->next;
    }

    return salvo;
}


//SPECIFICA DELLE FUNZIONI DELLA CLASSE!

template<typename Type>
LinkedList<Type>::LinkedList():head{nullptr}, size1{0}{}


//Distruttore della lista che rimuove ogni elemento dalla lista
template<typename Type>
LinkedList<Type>::~LinkedList(){
    while(!empty()){removeFront();};
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::begin() const{
    return Iterator(head);
}

//NOTA: La funzione che restituisce la posizione finale della lista, restituisce un puntatore nullo, infatti l'ultimo elemento della
//lista è un puntatore nullo!
template <typename T> 
typename LinkedList<T>::Iterator LinkedList<T>::end() const{
    return Iterator(nullptr);
}



//Specifica della funzione che individua se la lista è vuota o meno
template<typename Type>
bool LinkedList<Type>::empty(){
    return head==nullptr;
}

//Agginge un nuovo elemento alla lista
template<typename Type>
void LinkedList<Type>::addFront(Type& elem){
   
   //Salvo il vecchio header
    Node<Type>* old=head; 

    //Creto un nuovo nodo, per aggiornarlo
    head=new Node<Type>;

    //Inserisco gli elementi!
    head->element=elem;

    //Salvo nel puntatore next il vecchio headerche ho considerato!
    head->next=old;

    ++size1;

}

template<typename Type>
void LinkedList<Type>::removeFront(){
    
    //Salvo il vecchio header
    Node<Type>* old=head;

    //Inserisco nell'header il puntatore all'elemento successivo
    head=old->next;

    //Rimuovo il primo elemento che ho salvato!
    delete old;

    --size1;

}

//Funzione che restituisce il primo elemento della lista!
template<typename Type>
const Type& LinkedList<Type>::getFront(){
    //Controllo se la lita è vuota
    if(!empty()){
    //Restituisco l'elemento che ho richiesto
    return head->element;

    }
    //Se la lista è vuota, lancio l'eccezione!
    else{

        throw std::invalid_argument("La lista è vuota!");

    }
}

//Overload dell'operatore [] per accedere agli operandi!
template<typename Type>
const Type& LinkedList<Type>::operator[](int i){

    //Definisco due puntatori che occorrono per scorrere la lista
    Node<Type>* elemento{head};
    Node<Type>* vecchio=head;

    

    if(empty()){
        throw std::invalid_argument("Guarda che la lista è vuota!");
    }

    else{

    //Ciclo necessario per trovare l'elemento!
        for(int k=size1-1; k>i; k--){

            //Mi sposto tra i vari nodi, fino a quando non ho trovato l'elemento dalla posizione richiesta 
            //Uso i 2 puntatori che ho definito sopra!
            elemento=vecchio->next;
            vecchio=elemento;
                
            
        }

        //Restituisco l'elemento che ho trovato!
        return elemento->element;

    }
            
            
        

    //Per la funzione di ricerca, devo necessariamente pertire dalla testa della lista a causa del fatto che l'unico elemento che 
    //è direttamente accessibile della lista è quello che si trova sopra tutti gli altri, quindi il fronte della lista!
    //Si deve necessariamente scorrere al contrario!

}





template <typename Type>
int LinkedList<Type>::size(){
    return size1;
}