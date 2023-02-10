//Definzione della classe list, usando il template
#include "node.h" //Dobbiamo ovviamente inscludere quello che è il nodo che è stato definito prima!
//In modo che la classe linked list possa accedervi!

#include <iostream>

#ifndef LIST_H
#define LIST_H

template <typename Type>
class LinkedList{

    private: 
        Node<Type>* head; //Definizione della testa della lista, come puntatore ad un nodo!

        int size1; //Variabile che segna la lunghezza della lista

    public:
        //Definzione del costruttore 
        LinkedList();
        //Definizione del distruttore 
        ~LinkedList();

        //Vado a specificare il copy constructor della classe!
        //Essendo un copy constructor esso deve avere come argomento della funzione un'altra linkedList!
        LinkedList(const LinkedList<Type>&);
        
        //SPECIFICA DELL'OPERATORE =!
        LinkedList<Type>& operator=(const LinkedList<Type>&);

        //Definizione delle funzioni che sono necessarie alla classe!
        
        //Aggiungere un elemento!
        void addFront(const Type&);

        //Elimino un elemento dalla testa della lista!
        void removeFront();

        //Funione che controlla se la lista sia vuota o meno!
        bool empty() const;

        //Prendo il primo elemento dalla lista 
        const Type& getFront() const;

        //Overload dell'operatore[]
        //Lascio all'interno della lista anche la dichiarazione dell'operatore [], anche se non la utilizzeremo!
        const Type& operator[](int); 

        int size() const;



};

#include "list.cpp"

#endif