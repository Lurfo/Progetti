//Vado a specificare la classe che rappresenta l'albero binario di ricerca!
//Devo ovviamente includere la classe che contiene il nodo!

#include "node.h"
#ifndef BST_H
#define BST_H

template <typename T>
class BST{
    //Come accade nel caso delle liste l'unico elemento che posso adare a definire è un puntatore alla radice dell'albero!
    private:
        //Un po' come se fosse l'header di una lista! 
        Node<T>* root; 
        //Usando questo puntatore alla radice sono però in grado di andare a ripercorrere tutto l'albero!

    public:
        //Specifica del costruttore dell'abero!
        //Devo ovviamente inizializzare la radice ad un puntatore nullo!
        BST(Node<T>* r=nullptr): root{r}{}
        //Il distruttore usa una delle funzioni membro per andare a rilasciare la memoria occupata dalla radice!
       // ~BST(){release(root);}

        //Definisco la funzione che ha il compito di andare a restiure gli elementi presenti all'interno dell'albero in ordine!
        //Questa serve per scorre l'albero in ordine partendo da un nodo casuale!
        void inOrder(Node<T>*); 
        //Questa server per percorre l'abero partendo dalla radice!
        void inOrder(){inOrder(root);}

        //Definisco altre funzioni accessorie dell'albero!
        //Prelevo la radice dell'albero!
        Node<T>* getRoot(){return root;}
        
        //Ricerca di un elemento partendo da un elemento!
        Node<T>* search(T&);
        //Ricerca di un elemento partendo da un determinato nodo!
        Node<T>* search(Node<T>*, T&);
        
        //Ricerca del minimo partedo da un nodo!
        Node<T>* minimum(Node<T>*);
        //Ricerca del minimo partendo dalla radice!
        Node<T>* minimum(){return minimum(root);}

        //Ricerca del massimo partendo da un nodo!
        Node<T>* max(Node<T>*);
        //Ricerca del massimo partendo dalla radice!
        Node<T>* max(){return max(root);}

        //Vado a specificare le funzioni che restituiscono gli elementi predecessori  e successori rispetto ad un nodo!
        Node<T>* predecessor(Node<T>*); 
        Node<T>* successor(Node<T>*);

        //Specifica dell funzioni che vanno ad inserire un elemeneto all'interno della classe!
        Node<T>* insert(T&); //é un puntatore poichè restituisce NULL quando l'elemento è già presente!
        void release(Node<T>*);
    
};

#include "bst.cpp"

#endif
