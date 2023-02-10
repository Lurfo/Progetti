//Definizione della classe DQUEUE
#include "list.h"

#ifndef DQUEUE_H
#define DQUEUE_H

template <typename T>
class Queue{
    private: 
        //Come viariabile privata devo ovviamente andare a definire la lista!
        DList<T> lista; 
    
    public: 
        Queue(); 

        //Il distruttore non è necessario basta quello della lista!

        void insertFront(const T&); 
        void insertBack(const T&);

        const T& front() const; 
        const T& back() const; 

        void removeFront(); 
        void removeBack(); 

        int size() const; 
        bool empty() const;

};

#include "dqueue.cpp"


#endif
