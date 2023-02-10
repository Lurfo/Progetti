//Vado a dichiarare tutte le funzioni che ho definito nella classe dqueue!

template <typename T>
Queue<T>::Queue(): lista{}{}

template <typename T>
void Queue<T>::insertFront(const T& elem){
    lista.addFront(elem);
}

template <typename T>
void Queue<T>::insertBack(const T& elem){
    lista.addBack(elem);
}

template <typename T>
const T& Queue<T>::front()const{
    return lista.front();
}

template <typename T>
const T& Queue<T>::back() const{
    return lista.back();
}

template <typename T>
void Queue<T>::removeBack(){
    if(!empty())
        lista.removeBack();
    
    else
        throw std::invalid_argument("La lista è vuota!");
}

template <typename T>
void Queue<T>::removeFront(){
    if(!empty())
        lista.removeFront();

    else
        throw std::invalid_argument("La lista è vuota!");
}

template <typename T>
int Queue<T>::size() const{
    if(empty())
        std::cout<<"Non ci sono ancora elementi in coda\n";

    else{
        return lista.size();
    }
}

template <typename T>
bool Queue<T>::empty() const{
    return lista.empty();
}