//Vado a riscrivere la lista di cui ho bisogno per la coda 


#include "CNode.h"
#include <iostream>
#include <stdexcept>

#ifndef CLIST_H
#define CLIST_H

template <typename T>
class List{
    private: 
        //Specifica del cursore della lista!
        Node<T>* cursor; 

        //Per tenere il  numero degli elementi che inserisco al suo interno!
        int elementi; 

    public: 
        //Costruttore
        List(); 

        //Distruttore
        ~List(); 

        //Funzione che controlla se la lista è vuota 
        bool empty() const; 

        //Funzione che restituisce il back 
        //NB: Il Back verrà utilizzato come indicatore per il tail! Ovviamente qui andranno aggiunti gli elementi!
        const T& back() const;

        //Funzione che restituisce il front
        //Sarà quella che poi rappresenta l'head della funzione!
        const T& front() const; 

        //Funzione che aggiunge un elemento!
        void add(const T&); 

        //Funzione che rimuove l'elemento dal front!
        void remove();

        //Funzione che fa avanzare il cursor
        void advance();

        //Funzione che restituisce la grandezza
        int size() const;


    
};

#include "Clist.cpp"


#endif