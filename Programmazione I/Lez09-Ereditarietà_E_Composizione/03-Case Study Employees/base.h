//Definizione della classe che ha uno stipendio fisso!

#include "employees.h"

using std::string;

#ifndef BASE_H
#define BASE_H

class Base: public Employees{

    private:
        double stipendio; 

    public: 
        Base();
        Base(const string&, const string&, const string&, double );

        //Definizione delle funzioni di prelievo e di inserimento dello stipendio!
        void setStipendio(double);
        double getStipendio();


        //Override delle funzioni virtual della classe base 
        virtual double guadagni() override;
        virtual string toString() override;

        virtual double bonus() override;




};





#endif