//Specifica delle funzioni della classe commission.h
#include <stdexcept>
#include "commission.h"
#include <sstream>

using std::string;

//Definizione del costruttore
//Come si vede, quando andiamo a definire il costruttore per questa classe, adiamo anche a richiamare il costruttore della classe base!
Commission::Commission(): Employees(), vendite{0.0}, commissioni{0.0}{}

Commission::Commission(const string& n, const string& c, const string& ssn, double v, double comm): 
//Anche quando abbiamo degli element specificati dobbiamo sempre chiamare il costruttore della classe base per poter andare ad inserire nome, cognome e ssn
Employees(n,c,ssn){
    setVendite(v);
    setCommission(comm);
}


void Commission::setVendite(double v){
    if(v>=0.0){
        vendite=v;
    }

    else 
        throw std::invalid_argument("Guarda che quello che hai inserito non è un valore corretto!");

}

double Commission::getVendite(){
    return vendite;
}

void Commission::setCommission(double c){
    if(c>=0.0){
        commissioni=c;
    }

    else 
        throw std::invalid_argument("Guarda che il valore non è corretto!");
}

double Commission::getCommission(){
    return commissioni;
}

//Andiamo a specificare le funioni che sono state definite come virtual!

double Commission::guadagni(){
    return getCommission()*getVendite()+Commission::bonus();
}

//Specifica della funzione del bonus
double Commission::bonus(){
    return 0.0;
}

string Commission::toString(){
    //Anche all'interno di questa funzione andiamo ad usare quella che è la funzione toString che troviamo nella classe  base
    std::ostringstream ouput;

    ouput<<"Impiegato:\n"<<Employees::toString()<<"Commissioni: "<<getCommission()<<"\n"<<"Vendite: "<<getVendite()
        <<"\n"<<"Guadagno dalle vendite: "<<Commission::guadagni()<<"€\n"<<"Bonus: "<<bonus()<<"€\n";

    return ouput.str();



}
