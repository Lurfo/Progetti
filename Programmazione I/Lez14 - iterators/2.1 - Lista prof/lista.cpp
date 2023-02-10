template <typename T> 
List<T>::Iterator::Iterator(Node<T>* el){
    v=el;
}

template <typename T>
T& List<T>::Iterator::operator*(){
    return v->elemento;
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++(){
    v=v->prox;
    return *this;
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator--(){
    v=v->prec;
    return *this;
}








template <typename T>
List<T>::List(){
    num=0; 
    head=new Node<T>; 
    trailer=new Node<T>; 

    head->prec=nullptr;
    trailer->prox=nullptr;

    head->prox=trailer;
    trailer->prec=head;
}

template <typename 





