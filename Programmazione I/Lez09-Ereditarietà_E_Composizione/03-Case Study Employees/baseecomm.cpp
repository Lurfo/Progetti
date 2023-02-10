//Specifica delle funzioni della classe baseecomm
#include "baseecomm.h"
#include <stdexcept>
#include <sstream>
//Ovviamente dobbiamo sempre andare a sfruttare quello che è il costruttore della classe base per impostare tutti idati!
BaseEComm::BaseEComm(): Commission(), stipendio{0.0}{}

//Come vediamo al costruttore della classe da cui questa deriva dobbiamo inviare tutte le informazioni per andarle ad inserire all'interno dei relativi 
//dati membri!
BaseEComm::BaseEComm(const string& n, const string& c, const string& ssn, double v, double c1, double stip): Commission(n, c, ssn, v, c1){
    setStipendio(stip);
}

//Specifica delle funzioni che abbiamo visto precedentemente!

void BaseEComm::setStipendio(double s){
    if(s>=0){
        stipendio=s;
    }

    else 
        throw std::invalid_argument("Guarda che il valore dei soldi non è corretto!");
}

double BaseEComm::getStipendio(){
    return stipendio;
}

//Andiamo ad eseguire l'override delle funzioni definite come virtual!
double BaseEComm::guadagni(){
    return getStipendio()+bonus()+Commission::guadagni();
}

double BaseEComm::bonus(){
    return stipendio+stipendio*0.1;
}

string BaseEComm::toString(){
    std::ostringstream output;

    output<<Commission::toString()<<"Stipendio Base: "<<getStipendio()<<" €\n"<<"Guadagno totale: "<<BaseEComm::guadagni()<<"€\n";

    return output.str();
}