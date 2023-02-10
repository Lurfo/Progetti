//Definizione della classe base Account 
#include <string>

#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account{

    //Overload dell'operatore di stampa a video della classe
    friend std::ostream& operator<<(std::ostream&, const Account&);

    private: 
        //Impostiamo due variabili, un saldo e un credito!
        double balance; 

    public: 
        Account(double =0.0);

        //Funzioni che possono essere utili con la classe baseper poter gestire il bilancio ed effettuare operazioni base
        void setBalance(double);
        double getBalance() const;
        void withdrawBase(double);
        void depositBase(double);  




};


#endif