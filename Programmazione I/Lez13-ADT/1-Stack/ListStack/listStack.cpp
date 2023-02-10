//Specifica delle varie funzioni dello stack!

//Il costruttore ha solo il compito di andare ad inizializzare la lista!
template <typename T>
Stack<T>::Stack(): l(){}

template <typename T>
void Stack<T>::push(const T& e){
    l.addFront(e); //Uso le funzioni della lista per andare a definire le funzioni che compongono lo stack!
}

template <typename T>
void Stack<T>::pop(){

    if(empty()){
        throw std::runtime_error("Guarda che lo Stack è vuoto!");
    }

    l.removeFront(); //Ovviamente anche la funzione di pop uso lo stesso stratagemma!
}

template <typename T>
const T& Stack<T>::top() const{

    if(empty()){
        throw std::runtime_error("Guarda che lo stack è vuoto!");
    }

    return l.getFront(); //Usiamo la funzione della lista per prelevare l'elemento che si trova in cima!

}

template <typename T>
int Stack<T>::size() const{
    return l.size();
}

template <typename T>
bool Stack<T>::empty() const{
    return l.empty();
}


