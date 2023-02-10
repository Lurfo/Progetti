//Aggiorno la classe in modo da poter definire una lista a doppio puntatore!
#include "node.h" 


#include <iostream>

#ifndef LIST_H
#define LIST_H

template <typename Type>
class DLinkedList{

    private: 
        Node<Type>* head; //Definizione della testa della lista, come puntatore ad un nodo!
        Node<Type>* trailer; //Dobbiamo aggiungere il secondo puntatore che rappresenta la coda della lista!

        int size1; //Variabile che segna la lunghezza della lista

    public:
        //Definzione del costruttore 
        DLinkedList();
        //Definizione del distruttore 
        ~DLinkedList();

      
        void addFront(Type&);

        //Possiamo aggiungere la funzione che inserisce un elemento in coda alla lista 
        void addBack(Type&);

        
        void removeFront();

        //Ho una funzione che può rimuovere anche elementi dalla coda!
        void removeBack();

        //Funione che controlla se la lista sia vuota o meno!
        bool empty();

        
        const Type& getFront();

        //Posso impostare la funzione che va a prelevare l'ultimo elemento della lista!
        const Type& getBack();

        //Overload dell'operatore[]
        const Type& operator[](int);

        void insertOrder(Type&); //Definisco la funzione che va a inserire in ordine gli elementi all'interno della lista

        int size();


    protected: 
        //Definisco una funzione protected che ha lo scopo di andare ad aggiungere un elemento all'interno della lista 
        //Le definiamo protected in modo che solo le funzioni membro possono accedervi e utilizzarle!
        void add(Node<Type>*, Type& );
        void remove(Node<Type>*);

};


#include "list.cpp"

#endif