//Definizione della classe lista!
#include "node.h"
#include <sstream>

using std::ostringstream;

#ifndef LIST_H
#define LIST_H

template <typename T>
class CList{
    //Elmenti privati della lista!
    private:
      
        //Elemento che deinisce il cursore della lista, che ci permette di scorrere tutta la lista! 
        Node<T>* cursor; 
        
        //Specifico un elemento che tiene conto della dimensione della lista!
        int grand;

    public: 
        //Specifica del costruttore
        CList();
    
        //Specifica del costruttore
        ~CList();

        //Funzioni che occorrono alla lista!

        bool empty() const; //Controllo che la lista non sia vuota

        const T& front() const; //Elemento che segue il cursore 
        const T& back() const; //Elementi puntato dal cursore!

        void advance(); //Sposto del cursore!

        void add(const T&); //Funzione per aggiungere un elemento!
    
        void remove(); //Rimuovo l'elemento che si trova dopo il cursore!

        int size(){return grand;}

        //Definisco una funzione di stampa che serve per mostrare tutta la lista!
        std::string toString() const;

        //Definzione dell'overload dell'operatore []
        const T& operator[](const int);

};

#include "list.cpp"


#endif