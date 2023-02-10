//Definizione della classe list 
#include "node.h"
#include <stdexcept>

#ifndef LIST_H
#define LIST_H

template <typename T>
class DList{
    private:
        Node<T>* head; 
        Node<T>* trailer; 
        int num;

        //Specifica della funzione che aggiunge un elemento, in modo da non doverla ripetere più volte!
        void add(Node<T>*, const T&);
        void remove(Node<T>*);

    public: 

        DList(); 
        ~DList();

        void addFront(const T&);
        void addBack(const T&);

        const T& front() const; 
        const T& back() const; 

        bool empty() const; 
        int size() const;


        void removeFront(); 
        void removeBack();
};

#include "list.cpp"


#endif