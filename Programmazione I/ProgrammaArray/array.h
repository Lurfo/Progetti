#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>

class Array 
{
    friend std:: ofstream& operator<< (std:: ostream&,const Array&);
    friend std:: istream& operator>> (std:: istream&, Array&);
   
    public:

        //definiamo il costruttore di default per la massima dimensione di integers2 che non abbiamo inizializzatp 
        explicit Array (int=10);
        // definiamo il costruttore copia per quando facciamo l uguaglianza tra in due array 
        Array (const Array&);
        //definiamo il distruttore
        ~ Array ();
        // definiamo il costruttore non default( il tipo size_t è per gli indici )
        size_t getSize()const;
        // defimiamo gli overload 

            // assegnazione 
            const Array& operator = (const Array&);

            //suguaglianza
            bool operator == (const Array&) const;
            //disuguaglianza
            bool operator != (const Array& right) const{
                return ! (*this==right);}
            // []
            int& operator [] (int);
            // per mostrare valore in una posizione
            int operator [] (int) const;
    private:
    size_t size;
    int *ptr; 
};
#endif
