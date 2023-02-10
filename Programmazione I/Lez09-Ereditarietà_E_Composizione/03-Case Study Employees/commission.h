//Classeche rappresenta l'impegato che guadagna su commisione in base alle vendite!
#include "employees.h"

using std::string;

#ifndef COMMISSION_H
#define COMMISSION_H


class Commission : public Employees{

    private: 
    
    double vendite;
    double commissioni;

    public: 

        //Costruttore della classe
        Commission();
        Commission(const string&, const string&, const string&, double= 0.0, double =0.0);

        //Andiamo, ovviamente, anche a definire il distruttore per questo elemento!
        virtual ~Commission()=default;

        void setVendite(double);
        double getVendite();

        void setCommission(double);
        double getCommission();

        //Specifica delle funzioni virtual
        //Così facendo segnaliamo il fatto che su tali funzioni è stato eseguito un override
        virtual double guadagni() override;
        virtual string toString() override;
        
        //Override della funzione per il bonus
        virtual double bonus() override;



};

#endif