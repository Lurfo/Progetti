//Definizione della classe clienti
#include "data.h"
#include <string>

#ifndef CLIENTE_H
#define CLIENTE_H

class cliente{

    friend class palestra;

    private: 

    //Quello che andiamo ad usare come codice!
    int codice;

    Data scadenza;

    char nome[15]; 
    char cognome[15]; 

    public: 

        cliente(int =0, const std::string& =" ", const std::string& =" "); 

        ~cliente();

        void setCode(int); 
        int getCode() const; 

        void setName(const std::string&);
        std::string getName() const;

        void setSecond(const std::string&); 
        std::string getSecond() const; 

        void setData(int, int, int);
        std::string getData();

        cliente& operator=(const cliente&);



};



#endif