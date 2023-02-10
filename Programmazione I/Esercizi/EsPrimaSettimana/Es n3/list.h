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
        //Vado a scrivere la classe dell'iterator per la circular list!
        class Iterator{
           
            friend class CList<T>;

            private: 
                //Definisco un puntatore ad un nodo!
                Node<T>* punt; 

                //Definisco il costruttore della classe!
                Iterator(Node<T>*); 
                //Ha come argomento un riferimento al nodo!

            public: 
                //Definiscione della funzione di deferenziazione!
                T& operator*() const;

                //Definizione di alcune funzioni di comparazione!
                bool operator==(const Iterator&) const; 
                bool operator!=(const Iterator&) const;  

                //Defizione di alcune funioni di avanzamento dell'iterator!
                Iterator& operator++(); 
                Iterator& operator--(); 
                Iterator operator++(int);
                Iterator operator--(int);  

        };

    public: 
        //Specifica del costruttore
        CList();
    
        //Specifica del costruttore
        ~CList();

        //Funzioni che occorrono alla lista!

        //All'interno della classe vado a definire le due funzioni che restituiscono come valori quello dell'iterator!
        //Restituisco Il valore del nodo iniziale della lista!
        Iterator begin() const; 
        //Restituisco il valore del nodo finale della lista!
        Iterator end() const;

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