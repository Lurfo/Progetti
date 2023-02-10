/* Come definito anche precedentemente una delle modalità più semplice per andare a definire uno stack, altro non è che usare un array!
In particolare bisogna quindi considerare, un array, contenente un certo numero di elementi e un oggetto che va a memorizzare l'elemento che si trova 
sulla sommità dell'array! Che va ovviamente modificato ogni volta!*/

//Specifica della classe, andando ovviamente ad usare un template in modo da renderla molto più efficiente!
#include <iostream>
#include <stdexcept>

#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

template <typename T>
class Stack{
    private: 
      
        T* arr; //Array su cui si basa lo stack!
        int capacity; //Essendo un array dobbiamo andare a specificare anche la quantità di elementi che esso può contenere!
        int primo; //Posizione dell'elemento che si trova al top dello stack!

    public: 
        //Costruttore 
        Stack(int =10); //Usiamo un argomento di default per la capatità!

        //Distruttore
        ~Stack(); //Distruttore!

        //Numero di elementi che sono contenuti!
        int size(){return primo+1;} //Per vedere qunti l'effettivo numeri di elementi all'interno dello stack uso la posizione dell'elemento al top!

        //Ho bisogon di definire la funzione che va a prelevare l'elementi che si trova al di sopra dello stack!
        const T& front() const; 

        //Funzione pop ->toglie l'elemento dalla cima
        void pop();
        
        //Funione push ->toglie l'elemento dalla testa 
        void push(const T&);

        //Funzione che controlla che la lista non sia vuota!
        bool empty() const;


};  

//Vado ad includere qui la specifica della lista poichè generata tramite template!
#include "arrayStack.cpp"

#endif

