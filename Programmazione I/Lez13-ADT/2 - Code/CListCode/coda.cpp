//Specifica di tutte le funzioni della classe coda!

//costruttore, fa semplicemente inizializzare la mia lista circolare!
template <typename T>
Coda<T>::Coda(): buffer{}{}

//Restituisco il front della coda 
template <typename T>
const T& Coda<T>::front() const{
    return buffer.front();
}

//Specifica della funzioe che aggiunge un elemento alla coda!
template <typename T>
void Coda<T>::enqueue(const T& e){
    //Per aggiungere un elemento alla lista utilizzo la funzione che ho già definito della lista!
    buffer.add(e);

    //Tuttavia non posso concludere così, devo andare a spostare il cursor in modo che, l'elemento che inserisco per primo, sarà sempre l'elemento front
    //della lista, e che tutti gli elementi che lo seguono sono in ordine di posizionamento!
    buffer.advance();
}

//Funzione che rimuove un elemento dalla lista
template <typename T>
void Coda<T>::dequeue(){
    //Non devo fare altro che eliminare il front dalla lista 
    buffer.remove(); 
}

template <typename T>
bool Coda<T>::empty() const{
    //Ovviamente se la coda è vuota, anche la lista è vuota 
    return buffer.empty();
}

//Funzione che restituisce l'empiezza della coda 
//Visto che l'ampiezza della coda dipende dagli elementi che sono contenuti nella lista, allora posso udare quella funzione!
template <typename T>
int Coda<T>::size() const{
    return buffer.size();
}
