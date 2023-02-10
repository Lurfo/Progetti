//Andiamo a definire la classe che, invece, rappresenta la lista vera e propria!
#include "StringNode.h" //Dobbiamo includere anche la classe Node, poichè dobbiamo specificare funzioni che agiscono su quella!

#ifndef STRINGLIST_H
#define STRINGLIST_H

class StringList{

    //La classe che rappresenta la lista ha un solo elemento privato, MA CHE RISULTA ESSERE DI FONDAMENTALE IMPORTANZA!
    private:

        Node* header; //Come unico elemento ha un puntatore di tipo node! Questo elemento però risulta essere molto importante, in quanto
        //Rappresenta il primo elemento della lista, con in quale possiamo poi accedere a tutti gli altri elementi!
        //Nel caso in cui dovessimo perdere questo riferimento allora sarebbe impossibile andare a recuperare gli altri elementi!!!!

        //Aggiungo un elemento che segna la lunghezza della lista 
        int lung;
        

    public: 
        //Signature delle funzioni di classe 
        
        //Il costruttore 
        StringList();
        //Il distruttore
        ~StringList();

        //Specifica delle funzioni che vanno a compiere azioni sulla lista 
        void addFront(const string&); //Aggiunge un elemento in testa alla lista!

        void removeFront(); //Rimuove l'elemento dalla testa della lista!

        bool empty(); //Controlla che la lista sia vuota o meno
        const string& front() const; //Prende l'elemento alla testa della lista


        //Funzione che restituisce la lunghezza della lista 
        int size(){return lung;}

        //Definizine della funzione che va a riscrivere l'operatore per prelevare l'elemento i-esimo dalla lista!
        const string& operator[](int);


};



#endif