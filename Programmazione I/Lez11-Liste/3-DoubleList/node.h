//Modifico la classe che ho creato prima per andare a gestire le liste a doppio punatore!
#ifndef NODE_H
#define NODE_H

template <typename Type> class DLinkedList; 
template<typename Type>
class Node{

    private: 
        
        Type element; 
        Node<Type>* next; //Andiamo a specificare il puntatore al prossimo elemento della lista!
        Node<Type>* prev; //Rappresenta il puntatore all'elemento precedente della lista!

    //Dichiarazione della classe amica 
    friend class DLinkedList<Type>;




};



#endif