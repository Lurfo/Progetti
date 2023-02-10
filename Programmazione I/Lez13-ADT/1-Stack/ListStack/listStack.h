//Specifica del conteiner basatu su delle liste!
#include "list.h" //Devo ovviamente includere la classe lista in modo da poterla usare!

#ifndef LISTSTACK_H
#define LISTSTACK_H

//Definisco lo stack usando dei template!
template <typename T>
class Stack{
    private: 
        LinkedList<T> l; //Vado a definre all'interno dei membri dell stack solo una lista che sarà la base del nostro stack!

        //La lista che abbiamo definito conosce anche la sua dimensione, quind possiamo anch non includere un elemento che rappresenta le dimensioni
        //dello stack, ma usare quello definito nella classe LinkedList!

    public: 

        //Specifica delle funzioni
        Stack(); 

        //Non è necessario implementare un distruttore poichè la lista che usiamo ne ha già uno!

        //Definizione delle funzioni utili! 
        void push(const T&); 
        void pop(); 

        const T& top() const; 
        
        int size() const; 

        bool empty() const; 


        

};

#include "listStack.cpp"



#endif