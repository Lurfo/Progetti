//Per andare a definire gli elementi di un BST devo andare a definire un nodo un po' più complesso, contenete non solo gli elementi che deve memorizzare
//ma anche un puntatore agli altri elementi!

//Ovviamente definisco la classe nodo come un template!
#include <iostream>


#ifndef NODE_H
#define NODE_H
template <typename T> class BST; 

template <typename T>
class Node{
    //Definizione defli elementi privati!
    private: 
        T elm; 
        Node<T>* parent;
        Node<T>* left; 
        Node<T>* right; 
    
    //Devo andare a definire anche una "zona" pubblica, in cui vado a definire il costruttore del nodo!
    public:

        //In questo modo avado ad inizializzare tutti gli elementi del nodo!
        Node(T& e, Node<T>* p=nullptr, Node<T>* l=nullptr, Node<T>* r=nullptr): elm{e}, parent{p}, left{l}, right{r}{}

    //RICORDA
    //Devo sempre andare a dichiarare la classe BST come classe amica di questa, in modo da poterne gestire anche gli elementi privati!
    friend class BST<T>;

};



#endif