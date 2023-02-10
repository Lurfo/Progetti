//VADO A SPECIFICARE LE FUNZIONI DELLA CLASSE ITERATOR!
template <typename T>
CList<T>::Iterator::Iterator(Node<T>* passo){
    punt=passo; 
    //Sto inizializzando l'indirizzo di memoria puntato dal valore punt, a quello del nodo che ho inviato al costruttore!
}

//Operazione di deferenziazione!
template <typename T> 
T& CList<T>::Iterator::operator*() const{
    return punt->elemento;
}

template <typename T> 
bool CList<T>::Iterator::operator==(const Iterator& conf) const{
    return punt==conf.punt;
}

template <typename T> 
bool CList<T>::Iterator::operator!=(const Iterator& conf) const{
    return punt!=conf.punt; 
}

template <typename T>
typename CList<T>::Iterator& CList<T>::Iterator::operator++(){

    punt=punt->next;

    return *this;
}

template<typename T>
typename CList<T>::Iterator& CList<T>::Iterator::operator--(){
    Iterator salvo(*this); 

    while(punt->next!=salvo.punt){
        punt=punt->next;
    }

    return *this;
    
}

template <typename T> 
typename CList<T>::Iterator CList<T>::Iterator::operator++(int){
    Iterator salvo(punt);

    punt=punt->next;

    return salvo;
}

template <typename T>
typename CList<T>::Iterator CList<T>::Iterator::operator--(int){
    Iterator salvo(punt); 

    --*this;

    return salvo;
}

//Specifica delle funzioni della classe CList

//SPECIFICA DELLE FUNZIONI CHE RESTITUISCONO L'ITERATOR!
template <typename T>
typename CList<T>::Iterator CList<T>::begin() const{
    return Iterator(cursor->next);
}

template <typename T> 
typename CList<T>::Iterator CList<T>::end() const{
    return Iterator(cursor); 
}



//Specifica del costruttore
template <typename T>
CList<T>::CList(): cursor{nullptr}, grand{0}{} //Inizializzo il cursore al puntatore nullo!

//Specifica del distruttore
template <typename T>
CList<T>::~CList(){
    //Fino a che la lista non è vuota vado a rimuovere l'elemento che si trova dopo il costruttore!
    while(!empty()){remove();};
}


//Funione che controlla che la lista sia vuota
template <typename T>
bool CList<T>::empty() const{
    //Uso il confronto con il puntatore nullo!
    return cursor==nullptr;
}

//Specifica che restituisce il valore che si trova dopo il cursore
template <typename T>
const T& CList<T>::front() const{
    //Restituisco quindi il valore che si trova subito dopo il cursore!
    return cursor->next->elemento;
}

//Funzione che restituisce l'elemento puntato dal cursore!
template <typename T> 
const T& CList<T>::back() const{
    return cursor->elemento;
}

//Funzione che sposta il cursore!
template <typename T>
void CList<T>::advance(){
    cursor=cursor->next;
}

template <typename T>
void CList<T>::add(const T& e){
    //Definisco un nuovo puntatore ad un nodo per andare ad immagazzinare l'elemento!
    Node<T>* punt= new Node<T>;

    //Inserisco nel nuovo nodo l'elemento che ho inviato alla funzione
    punt->elemento=e;

    //Eseguo un controllo sul cursor che ho nella lista 
    if(cursor == nullptr){ //Se è il primo elemento della lista 

        punt->next=punt; //Allora faccio in modo che il prossimo elemento del nodo punti a se stesso!

        cursor=punt; //Salvo quindi tale valore nel cursor!
    }

    else{   //Se non è il primo elemento della lista!

        //Faccio in modo che il nuovo elemento punti al vecchio elemento successivo puntato dal cursor
        punt->next=cursor->next;

        //E che il cursor punti al nuovo elemento!
        cursor->next=punt;

    }

    ++grand;
    


}

//Specifica della funzione che rimuove un elemento dalla lista!
//Ovviamente va rimuovere l'utimo elemento della lista!
template <typename T>
void CList<T>::remove(){
    //Come prima cosa è importante verificare che la lista non sia nulla
    if(empty()){
        throw std::invalid_argument("La lista è già vuota!");
    }

    //Se non è vuota posso procedere con la rimoziobe dell'elemento che si trova dopo il cursor!
    else{
        //Salvo l'elemento puntato dal cursor!
        Node<T>* old=cursor->next;

        //Verifico che, se i due elementi sono uguali, allora vuol dire che bisogna andare a impostare il curost come elemento nullo
        if(old==cursor){
            cursor=nullptr; //In questo modo quado sono arrivato all'ultimo elemento posso andare a rimuovere anche quello dalla lista!
        }

        //Se non sono all'ultimo elemento, devo rimuovere quello che si trova subito dopo il cursor!
        else{
            //Faccio quindi in modo da eliminare il vecchio fronte!
            cursor->next=old->next;
        }

        //Elimino quindi il vecchio fronte
        delete old; 

        //Diminuisco la variabile che contiene la dimensione della lista!
        --grand;


        
    }
}

template <typename T>
std::string CList<T>::toString() const{
    ostringstream output; 
    Node<T>* element=cursor->next; //Parto sempre dal cursor!

    output<<"Cursor: "<<cursor->elemento<<" seguono: ";

    while(element!=cursor){
        output<<element->elemento<<((element->next!=cursor) ? ", ": " ");
        element=element->next;
    }

    return output.str();

}

//Specifica della funzione che esegue l'overload di []
template<typename T>
const T& CList<T>::operator[](const int numero){
    //Definisco un puntatore che punta al front

    Node<T>* element = cursor->next;

    if(numero<0 && numero>grand-1){
        throw std::invalid_argument("Guarda che la posizione inserita non è accessibile!");
    }

    else{
        
        for(int i=0; i<numero; i++){
            element=element->next;
        }

    }

    return element->elemento;

    
}