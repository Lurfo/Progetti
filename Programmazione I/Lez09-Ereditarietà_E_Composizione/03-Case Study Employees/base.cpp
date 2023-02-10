//Specifica delle funzioni dell'operario che riceve uno stipendio base!
#include "base.h"
#include <stdexcept>
#include <sstream>

Base::Base(): Employees(), stipendio{0.0}{}

Base::Base(const string& n, const string& c,  const string& ssn, double stip): Employees(n,c,ssn){
    setStipendio(stip);
}

void Base::setStipendio(double s){
    if(s>=0){
        stipendio=s;
    }

    else 
        throw std::invalid_argument("Guarda che così non va eh\n");
}

double Base::getStipendio(){
    return stipendio;
}

//Override delle funzioni virtual!
double Base::guadagni(){
    return stipendio+bonus();
}

double Base::bonus(){
    return 0.0;
}

string Base::toString(){
    std::ostringstream output;

    output<<Employees::toString()<<"Stipendio: "<<getStipendio()<<"€ \n"<<"Bonus: "<<bonus()<<"€\n";

    return output.str();

}