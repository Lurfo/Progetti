#include "base.h"

#ifndef DERIVED_H
#define DERIVED_H

class Derived : public Base{
    private: 
        int saldo; 
        int conto; 

    public: 
        Derived(); 
        ~Derived(); 

        std::string toStirng();
}


#endif