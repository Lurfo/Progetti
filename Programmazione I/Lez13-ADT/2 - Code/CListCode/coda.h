//Definizione della classe coda

//Devo includere la lista in modo da poterla utilizzare!
#include "Clist.h"

#ifndef CODA_H
#define CODA_H

template <typename T>
class Coda{ 

    private:
        //Vado ad inserire come elemento all'interno della classe la mia lista 
        List<T> buffer; 

    public: 

        //All'interno di public vado a definire tutte le funzioni che operano su tale lista 

        //Costruttore 
        Coda(); 

        //Distruttore non è necessarip poichè la lista circolare ha già il suo distruttore!
        //~Coda(); 

        //Funzione che restiuisce il front
        const T& front() const;

        //Funzione che aggiunge elemento in coda!
        void enqueue(const T&);

        //Funzione che rimuove un elemento dalla coda
        void dequeue();

        //Funzione che controlla se è vuota
        bool empty() const; 

        //Funzione che restituisce il numero di elementi!
        int size() const; 


};

#include "coda.cpp"


#endif