//Definizione della classe nodo che va inserita nella CList!

#ifndef CNODE_H
#define CNODE_H

template <typename T> class List;

template <typename T>
class Node{
    private: 
        T elemento; 

        Node<T>* next; 
    
    //Specifica della classe Lista come amica di questa in modo da poter andare a modificarne i valori che ho inserito!
    friend class List<T>;
};




#endif