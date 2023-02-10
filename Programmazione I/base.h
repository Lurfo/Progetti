#include <stirng>

#ifndef BASE_H
#define BASE_H

class Account{
    private: 
     
        int code;
    
        std::string nome;
        std::string cognome;

    public: 
        Account(); 
        ~Account(); 

        virtual std::string toString() override;
}



#endif