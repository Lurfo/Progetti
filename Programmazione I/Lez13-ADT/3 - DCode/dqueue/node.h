//Specifica del nodo della lista a doppio puntatore 

#ifndef NODE_H
#define NODE_H

//Definizione della classe DList, di cui ho bisogno per definirla come classe amica di node per poter gestire gli elementi che essa contiene!

template <typename T> class DList;

template <typename T>
class Node{
    
    private: 
       
        Node<T>* next; 
        Node<T>* prev; 

        T elemento;

    friend class DList<T>;


};





#endif