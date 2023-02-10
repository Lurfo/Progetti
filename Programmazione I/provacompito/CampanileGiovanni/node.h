//Definizione del nodo della Lista che usa gli iterator!

#ifndef NODE_H
#define NODE_H

template <typename T> class List;

template <typename T>
class Node{

    private: 
        T elemento; 
        Node<T>* prox; 
        Node<T>* prec; 
    
    friend class List<T>;
};

#endif