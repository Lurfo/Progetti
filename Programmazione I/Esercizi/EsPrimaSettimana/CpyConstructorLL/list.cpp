
template<typename Type>
LinkedList<Type>::LinkedList():head{nullptr}, size1{0}{}


//Distruttore della lista che rimuove ogni elemento dalla lista
template<typename Type>
LinkedList<Type>::~LinkedList(){
    
    while(!empty()){
        removeFront();};
}

//Vado a definire l'implementazione del copy constructor!
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& copia):head{nullptr}, size1{0}{
    //Vado a selezionare un puntatore segnaposto che inizializzo al primo elemento della lista da copiare!
    Node<T>* segno=copia.head; 

    //Vado ad inserire poi gli elementi nella lista all'interno di un vettore, per poterli poi ordinare!
    T arr[copia.size()];

    int i=copia.size()-1;
    while(segno!=nullptr){
        arr[i]=segno->element;
        segno=segno->next; 
        i--;
    }

    //Vado a inserire gli elementi del vettore, ordinati in base all'inserimento che ho fatto nella prima lista, all'interno della nuova!
    for(int k=0; k<copia.size(); k++){
        addFront(arr[k]);
    }
   
}


//VADO A DEFINIRE LA FUNZIONE CHE DESCRIVE IL COMPORTAMENTE DELL'OPERATORE=
template <typename T> 
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& copia){
    //CONTROLLO 
    //Devo verificare se la classe che ho inviato è differente da quella con cui devo confrontarla!
    //Se infatti è uguale, posso rismarmiarimi di fare dei passaggi inutili!
    if(this==&copia){
        return *this;
    }

    else{
        //Vado ad eliminare tutti gli elementi che ci sono nella lista che devo sovrascrivere!
        while(!empty()){
            removeFront(); 
        }

        //Il processo che ho definito qui è molto simile a quello specificato nel costruttore copia! 
        //Scorro la lista da copiare e salvo gli elementi in un array! (Partendo dall'ultima posizione, in modo da considerare anche 
        //l'ordine con cui l'utente inserisce gli elementi all'interno della lista!)
        //Se faccio infatti solo il passaggio di inserimento degli elementi dalla lista di copia alla nuova lista, allora gli elementi
        //verrano salvati nell'ordine contrario!
        T arr[copia.size ()];
        Node<T>* segno=copia.head;

        for(int i=copia.size()-1; i>=0; i--){
            arr[i]=segno->element;
            segno=segno->next;
        }

        //Dall'array posso poi andare ad inserire gli elementi all'interno della lista che ho considerato!
        for(int i=0; i<copia.size(); i++){
            addFront(arr[i]);
        }

        //In questo modo ho cancellato tutti gli elementi che erano presenti prima all'interno della lista e li ho sostituiti con dei nuovi 
        //elemenenti!

    }

    return *this;
}

//Specifica della funzione che individua se la lista è vuota o meno
template<typename Type>
bool LinkedList<Type>::empty() const{
    return head==nullptr;
}

//Agginge un nuovo elemento alla lista
template<typename Type>
void LinkedList<Type>::addFront(const Type& elem){
  
   //Salvo il vecchio header
    Node<Type>* old=head; 

    //Creto un nuovo nodo, per aggiornarlo
    head=new Node<Type>;

    //Inserisco gli elementi!
    head->element=elem;

    //Salvo nel puntatore next il vecchio header che ho considerato!
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
const Type& LinkedList<Type>::getFront() const{
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
int LinkedList<Type>::size() const{
    return size1;

}