//Specifica delle funzioni della classe!

//Costruttore!
template <typename T>
List<T>::List(): cursor{nullptr}, elementi{0}{}

//Distruttore
template <typename T>
List<T>::~List(){

    //Sfruttiamo sempre delle funzioni che abbiamo specificato per rimuovere ogni elemento dalla classe!
    while(!empty()){remove();}
}

template <typename T>
bool List<T>::empty() const{
    return cursor == nullptr;
}

template <typename T>
const T& List<T>::back() const{
    return cursor->elemento;
}

template <typename T>
const T& List<T>::front() const{
    return cursor->next->elemento;
}

template <typename T>
void List<T>::add(const T& e){
    //Creo un nuovo nodo!
    Node<T>* n= new Node<T>;

    //Inserisco elemento nel nuovo nodo!
    n->elemento=e;

    //Controllo se è il primo elemento che inserisco nella lista!
    if(empty()){
        //Faccio in modo che il nuovo nodo punti a se stesso
        n->next=n;

        //Pungo il cursore uguale al nuovo nodo!
        cursor=n;
    }

    else{
        //Faccio in modo che il nuovo nodo punti al front
        n->next=cursor->next;

        //Cambio quindi il front con il nuovo elemento!
        cursor->next=n;
    }

    ++elementi;


}

//Funzione che elimina un elemento!
template <typename T>
void List<T>::remove(){

    //Inizializzo la variabile al valore che si trova subito dopo il cursor!
    Node<T>* old = cursor->next;    

    //Controllo che la lista non sia già vuota
    if(empty()){
        std::cerr<<"Guarda che la lista ormai è già vuota!\n";
    }

    //Se siamo arrivati al cursor sostituisco con un nullptr in modo da andare ad eliminare l'elemento contenuto nel cursor
    else if(old==cursor){
        cursor=nullptr;
    }


    else{
        cursor->next=old->next;
    }

   
    delete old;

    --elementi;

}

//Avanzamento del cursor
//NB: Tale funzione risulta essere molto importante nell'implementazione della Coda in quanto è quella che tiene conto del primo elemento inserito!
template <typename T>
void List<T>::advance(){
    cursor=cursor->next;
}

//Restituisco il numero di elementi contenuti!
template <typename T>
int List<T>::size() const{
    return elementi;
}