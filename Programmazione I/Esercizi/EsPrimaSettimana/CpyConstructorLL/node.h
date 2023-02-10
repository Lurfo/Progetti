//Dichiarazione di un nodo generico usando i template!

#ifndef NODE_H
#define NODE_H
//Definizione del template per la classe, Type rappresenta il tipo di elemento che andiamo ad inserire nella lista!
template <typename Type> class LinkedList; //Importante andare a specificare la classe LinkedList in modo che può essere specificata come amica

template<typename Type>
class Node{

    private: 
        //Il tipo dell'elemento viene sostituito in fase di compilazione!
        Type element; //Andiamo a specificare il tipo di elemento che è contenuto all'interno della lista
        Node<Type>* next; //Andiamo a specificare il puntatore al prossimo elemento della lista!

    //Dichiarazione della classe amica 
    friend class LinkedList<Type>;




};



#endif