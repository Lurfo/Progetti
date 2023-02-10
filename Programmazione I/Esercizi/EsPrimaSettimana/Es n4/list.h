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

    //Per svolgere l'esercizio numero 4, andare cioè a dividere quelli che sono gli elementi in posizione dispari da quelli in posizione pari
    //Vado a definire anche per la classe linked list, un iterator che mi permete di gestire al meglio gli elementi!
    public: 
        class Iterator{
                friend class LinkedList<Type>;
            private: 
                //Ho bisogno del mio puntatore! Ad un nodo!
                Node<Type>* punt; 

                Iterator(Node<Type>*); 
            
            public: 
                //Specifica della funzione di deferenziazione 
                Type& operator*() const; 
                
                bool operator==(const Iterator&) const; 
                bool operator!=(const Iterator&) const; 

                Iterator& operator++();
                Iterator& operator--(); 
                Iterator operator++(int); 
                Iterator operator--(int); 
        };

    public:
        //Definzione del costruttore 
        LinkedList();
        //Definizione del distruttore 
        ~LinkedList();

        //Definizione delle funzioni che sono necessarie alla classe!
        //Definizione della funzioni che restituiscono come elementi un iterator!
        Iterator begin() const;
        Iterator end() const;
        
        //Aggiungere un elemento!
        void addFront(Type&);

        //Elimino un elemento dalla testa della lista!
        void removeFront();

        //Funione che controlla se la lista sia vuota o meno!
        bool empty();

        //Prendo il primo elemento dalla lista 
        const Type& getFront();

        //Overload dell'operatore[]
        const Type& operator[](int);

        int size();



};

//A questo punto devo andare ad includere il file che contiene la specifica delle funzioni perchè, come detto nel file .cpp 
//Esso non può essere compilato indipendentemente dal client, poichè sono delle funzioni template che devono essere compilate indipendentemente dal
//driver, che gli deve passare il tipo di elemento!
#include "list.cpp"

#endif