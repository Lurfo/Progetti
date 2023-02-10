//Andiamo ad implementare quella che è la classe che descrive il funzionamento della Queue!

#ifndef CODE_H
#define CODE_H

template <typename T>
class Code{
  
    private: 
        //Definisco l'array che ti trova alla base della queue!
        T* arr; 

        //Elemeto che mantiene la dimensione degli elementi effettivamente contenuti all'interno della lista!
        int size1; 

        //Elemento che mantiene la grandezza totale dell'array!
        int tot;

        //Elementi che servono a mantenere la posizione della testa e della coda della lista!
        int head; 
        int tail; 

    public: 

        Code(int =10); 
        ~Code();

        const T& front() const;

        void enqueue(const T&);
        void dequeue();

        int size(){return size1;}

        bool empty() const;


};


#include "code.cpp"


#endif


