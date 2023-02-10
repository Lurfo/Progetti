//Definizione della classe palestra!
#include <list>
#include <fstream>
#include "cliente.h"

#ifndef PALESTRA_H
#define PALESTRA_H

class Palestra{

    //Definisco una funzione che ha il compito di salvare gli elementi su di un file!
    //Ovviamente un file binario!
    friend void salvataggio(std::fstream&, Palestra&);
    friend void caricamento(std::fstream&, Palestra&);
    friend void vediClienti(Palestra&);
    friend void modifica(Palestra&);

    private: 


        std::string name;

        std::list<cliente> client; 
    
    public: 

        Palestra( const std::string& =" "); 
        ~Palestra(); 

        void setName(const std::string&); 
        std::string getName() const; 

        void aggiungiElemento(const cliente&);

        int size(){
            return client.size();
        }

        bool trovato(int);

};



#endif