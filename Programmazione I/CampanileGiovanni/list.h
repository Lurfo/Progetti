#include "node.h"
#include <stdexcept>

#ifndef LIST_H
#define LIST_H

template <typename T>
class List{
    public:
        //Definizione della classe degli iterator, come detto inizialmente essa deve essere una classe associata e quindi deve essere definita all'interno
        //della classe "di partenza!"
        class Iterator{
            private:
                //L'iterator dunque contiene come membri dati, il puntatore al noto della lista
                Node<T>* punt; 
                //In particolare andiamo anche ad inserire il costruttore dell'iterator come membro privato in modo che solo la classe List
                //Può andare a identificare un iterator!
                Iterator(Node<T>*); //Ovviamente l'iterator ha come argomento un puntatore al nodo per andare ad inizializzare il proprio puntatore

                //NOTA BENE: Ovviamente l'iterator, non viene definito "automaticamente" dalla lista, ma devo sempre 
                //specificare un oggetto di tipo iterator all'interno del driver per poter utilizzare un oggetto di questa classe!
                //Ovviamente, il costruttore è utile proprio perchè, quando ho definito l'oggetto di tipo iterator, devo andarlo ad inizializzare 
                //con l'indirizzo di un nodo della lista per poter effettuare tutte le operazioni di cui ho bisogno!
                //Motivo per cui ho bisogno di un costruttore anche per questa classe!
                //(Il funzionamento di questo iterator è molto simile a quello analizzato in 1 con i vettori!)
            
            public: 

                //Ovviamente, come specificato, ho che la classe iterator che ho definito, contiene anche delle funzioni da poter utilizzare sugli
                //oggetti di tipo iterator! 
                //Ognuna di queste funzioni ha un compito molto importante, ed inoltre, ho che possono essere molto utili nell'utilizzo degli 
                //oggetti iterator!

                //NOTA: Quelle sotto sono le "funzini base" che contiene la classe Iterator, ovviamente posso andare ad aggiungerne anche altre
                //in base alle esigenze di cui ho bisogno!

                T& operator*(); //Operatore di deferenziazione, restituisce l'elemento puntato dall'iterator!
                bool operator==(const Iterator&) const; //Operatore di confronto, controllo che due iterator siano uguali!
                bool operator!=(const Iterator&) const; //Operatore di contronto, controllo se due iterator sono differenti!
    
                Iterator& operator++(); //Operatore che fa avanzare l'iterator al prossimo elemento!
                Iterator& operator--(); //Operatore che fa arretrare l'iterator all'elemento precedente!
                Iterator operator--(int);
                Iterator operator++(int);

                //Dobbiamo poi andare a dichiarare la classe List come friend, in modo che essa possa modificare gli elementi presenti all'interno
                //di tale classe!
                friend class List<T>;

        };
        
        

    private: 
        //Sto sempre definendo una DLinkedList, quindi ho sempre bisogno della coda e della testa!
        Node<T>* head; 
        Node<T>* trailer; 
        int num; 

    public:

        //Dopo aver definito la classe Iterator posso andare a definire tutte le funzioni della lista!
        //Anche quelle che utilizzano gli iterator come elemento!
        //Utilizzare un iterator in alcune funzioni è molto utile!


        List(); //Costruttore!
        ~List(); //Distruttore

        int size() const; //Numero di elementi presenti nella lista!
        bool empty() const; //Controlla se la lista è vuota!

        //Come detto inizialmente ci possono essere delle funzioni che restituiscono l'iterator come valore!, esse possono essere molto utili per 
        //andare a scorrere la lista!
        Iterator begin() const; //Restituisce la posizione del primo elemento presente nella lista!
        Iterator end() const; //Restituisce la posizione dell'ultimo elemento presente nella lista!

        //Funzioni di inserimento del valore nella lista!
        void insertFront(const T&); 
        void insertBack(const T&); 

        //Funzione di inserimento vera e propria su cui si basano le altre!
        void insert(const Iterator&, const T&); //Vediamo che la funione di inserimento si basa sull'iterator per conoscere la posizione dove inserire
        //l'elemento!

        //Vado a definire le funzioni di eliminazione di un elemento dalla lista!
        void eraseFront(); //Elimino il primo elemento!
        void eraseBack();   //Elimino il secondo elemento!

        //Funzione di eliminazione di un elemento sulla quale si basano poi anche le altre!
        void erase(const Iterator&);

        T& getFront() const; 
        T& getBack() const;
        

};

#include "list.cpp"



#endif