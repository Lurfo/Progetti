//Dichiaro una classe chiamata SavingsAccount che corrisponde ad un libretto di risparmio, per andare a calcolare a quanto ammonta il capitale in funzione 
//di un tasso di interesse
#include "account.h" 

#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

//Andiamo a definire un tale classe come una classe derivata della classe Accoutn iniziale!
class SavingsAccount: public Account{
    
    friend std::ostream& operator<<(std::ostream&, const SavingsAccount&);

    private: 
        double tassoInteresse;
        int anni;
        double capitale;

    public: 

        //Definizione del costruttore della classe 
        SavingsAccount(double =0.0, double =0.0, double =0.0);

        //Definizione delle funzioni che ci sono utili per definire questa classe
        void setInteresse(double);
        SavingsAccount& setAnni(double);
        double getInteresse();
        double totaleDopoGliAnni(int);




};



#endif