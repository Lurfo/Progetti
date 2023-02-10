//Andiamo a definire l'ultimo tipo di impiegato che va a definire un impiegato che guadagna sia un valore fisso che un valore corrispondente alle vedite 
//Poichè esso è un caso particolare della classe commission, allora la definiamo come una classe derivata dalla clase commission!
#include "commission.h"

#ifndef BASEECOMM_H
#define BASEECOMM_H

//Come affermato essa è una classe che deriva dalla classe commission!

class BaseEComm: public Commission{

    private: 
        double stipendio;

    public:
        //Definizione dei costruttori!
        BaseEComm();
        BaseEComm(const string&, const string&, const string&, double=0.0, double=0.0, double=0.0);

        //Definizione del distruttore!
        virtual ~BaseEComm()=default;

        double getStipendio();
        void setStipendio(double);

        

        //Riscrizione delle funzioni virtual!
        virtual double guadagni() override;
        virtual string toString() override;

        virtual double bonus() override;






};



#endif