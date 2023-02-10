//Specifica delle funzioni della classe base abstract employees.h
#include "employees.h"
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using std::cin;

Employees::Employees(): name{" "}, cognome{" "}, SSN{" "}{
} 

Employees::Employees(const string& n, const string& c, const string& ssn){
    setName(n);
    setCognome(c);
    setSSN(ssn);
}

void Employees::setName(const string& n){
    name=n;
}

void Employees::setCognome(const string& c){
    cognome=c;
}

void Employees::setSSN(const string& ssn){
    SSN=ssn;
}

string Employees::getName(){
    return name;
}

string Employees::getCognome(){
    return cognome;
}

string Employees::getSSN(){
    return SSN;
}

//Andiamo poi a specificare la seconda funzione virtual, che ha il compito di restituire tutti gli elementi all'interno di una stringa 

string Employees::toString(){
    //In questo modo la funzione formatta tutto all'interno di un unica stringa!
    return "Nome: "+getName()+"\nCognome: "+getCognome()+"\nSSN: "+getSSN()+"\n";
}