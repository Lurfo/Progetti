//SPECIFICA DELLE FUNZIONI DELL'ITERATOR 
template <typename T> 
List<T>::Iterator::Iterator(Node<T>* elm){
    punt = elm; //Inizializzo il valore del puntatore contenuto nella classe iterator con quello che ho inviato al costruttore!
}

//Specifica della funzione di deferenziazione
template <typename T>
T& List<T>::Iterator::operator*(){
    return punt->elemento; //Devo inviare l'elemento che è contenuto all'interno del puntatore!
}

//Operazione di confronto con un altro iterator
template <typename T>
bool List<T>::Iterator::operator==(const Iterator& elm) const{
    return punt==elm.punt; //Devo confrontare il puntatore contenuto all'interno dell'iterator che ho con quello che gli ho inviato!
}

//Operazione di confronto dell'operazione diverso
template <typename T>
bool List<T>::Iterator::operator!=(const Iterator& elm) const{
    return punt!=elm.punt; //Come sopra vado a confrontare il puntatore che ho con quello che gli ho inviato per vedere se sono differenti!
    //Una funzione di questo tipo può essere molto utile quando devo scorrere gli elementi della ADT
}

//Operazione di avanzamento!
//NOTA: in questo caso, dobbiamo usare un differente tipo di chiarazione della funzione poichè essa ha come elemento di ritorno un iterator!
template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++(){
        //Avanzo il puntatore
        punt=punt->prox;

        //Poichè è l'operazione di pre incremento devo restituire come valore quello dell'oggetto che ho appena modificato!
        return *this;   
        //Uso quindi il puntatore this per restituire questo tipo di oggetto!

}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator--(){
   
    punt=punt->prec;

    return *this;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator--(int){
    Iterator nuovo(this->punt);
    punt=punt->prec;

    return nuovo;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int){
    Iterator nuovo=this->punt; 
    punt=punt->prox;
    return nuovo;
}
   

//DOPO AVER SPECIFICATO TUTTE LE FUNZIONI DELL'ITERATOR POSSO ANDARE A SPECIFICARE LE FUNZIONI DELLA CLASSE LISTA!

//Specifica del costruttore della lista 
template <typename T> 
List<T>::List():num{0}{
    //Vado ad inizializzare i puntatori head e trailer a puntarsi a vicenda!
    head= new Node<T>;
    trailer= new Node<T>; 

    head->prec=nullptr;
    trailer->prox=nullptr;


    //Essendo una DList devo inizializzarla in questo modo!
    head->prox=trailer;
    trailer->prec=head;
}

//Specifica del distruttore, uso sempre le due funzioni che ho dichiarato della classe!
template <typename T> 
List<T>::~List(){
    while(!empty()){
        eraseFront();
    }
}

//Specifica della funzione che restituisce il numero di elementi della lista!
template <typename T> 
int List<T>::size()const{
    return num;
}

template <typename T> 
bool List<T>::empty() const{
    return head->prox==trailer; 
    //Posso anche usare il numero di elementi della lista, ponendo
    //return num==0;
}

//ANIAMO A SPECIFICARE LE FUNZIONI CHE RESTITUISCONO L'ITERATOR!

//Specifica della funzione che restituisce la posizione de primo elemento della lista 
template <typename T> 
typename List<T>::Iterator List<T>::begin() const{
    //Ovviamente devo andare a restituire il valore dell'head della lista!
    //Siccome devo restituire un iterator, lo vado ad inizializzare!
    //Non devo andare ad inviare l'header, altirmenti non posso riesco a scorrere tutti gli elementi della lista!
    return Iterator(head->prox);   
}

//Vado a Specificare la funzione che restituisce la posizione dell'ultimo elemento della lista!
template <typename T> 
typename List<T>::Iterator List<T>::end() const{
    //Devo andare a restituire l'ultimo elemento
    //Vado a restituire, in questo caso, il trailer, poichè devo scorrere tutti gli elementi della lista, quindi è necessario che gli invio questo 
    //elemento altrimenti non riesco a scorrere tutti gli elementi!
    return Iterator(trailer);
    //Ad Esempio
    //for(Iterator p=list.begin(); p!=p.end(); p++)
    //Se non pongo end in questo modo e lo pongo come Iterator(trailer->prec) non posso visualizzare l'ultimo elemento della lista!
    //così come se non pongo la funzione begin al primo elemento ma all'header ho problemi nello scorrere la lista!
}

//FUNZIONI DI INSERIMENTO!
template <typename T> 
void List<T>::insertFront(const T& elm){
    //Vado ad usare una delle funzioni che ho definito!
    //Devo passargli un iterator, cominciando dall'inizio gli devo inviare il primo elemento della lista!
    Iterator p(head->prox);
    insert(p, elm);
}

template <typename T> 
void List<T>::insertBack(const T& elm){
    //Anche per questa funzione devo andare a utilizzare una delle funzioni che ho definito!
    //Siccome inserisco partendo dall'ultimo elemento devo inviare un iterator al trailer!
    Iterator p(trailer);
    insert(p, elm);
}

//Specifica della funzione di inserimenti di un elemento in una posizone mediante un iteratore!
template <typename T> 
void List<T>::insert(const Iterator& p, const T& elm){
    //Definisco un puntatore a nodo che utilizza quello dell'iteratore!
    Node<T>* nodo=p.punt; //Inizializzo il nuovo puntatore a nodo!
    Node<T>* nuovo= new Node<T>;

    //Salvo l'elemento nel nuovo nodo!
    nuovo->elemento=elm; 

    //Definisco il collegamento del nuovo nodo ai due
    nuovo->prox=nodo;
    nuovo->prec=nodo->prec;

    //Inserisco l'elemento nella lista!
    nodo->prec->prox=nuovo;
    nodo->prec=nuovo;
    
    num++;

}


//SPECIFICA DELLE FUNIONI DI ELIMINAZIONE DI UN ELEMENTO!
//Specifica di una funzione che elimina un elemento alla testa
template <typename T> 
void List<T>::eraseFront(){
    //Invio alla funzione che elimina un elemento il vero e proprio elemento da togliere che si trova in cima alla lista!
    erase(Iterator(head->prox));
}

template <typename T> 
void List<T>::eraseBack(){
    //Invio alla funzione l'ultimo elemento che è contenuto all'interno della lista!
    erase(Iterator(trailer->prec));
}

//SPECIFICA DELLA FUNZIONE CHE ELIMINA UN ELEMENTO!

template <typename T> 
void List<T>::erase(const Iterator& p){
    //Vad ad eliminare l'elemento che ho inviato!
    //Salvo il vecchio elemento!
    Node<T>* old = p.punt;
    
    //Ridefinisco i collegamenti del nodo precdente e di quello successivo!
    old->prec->prox=old->prox;
    old->prox->prec=old->prec;

    delete old; 

    num--;

}

template <typename T>
T& List<T>::getBack() const{
    return trailer->prec->elemento;
}

template <typename T>
T& List<T>::getFront() const{
    return head->prox->elemento;
}


 