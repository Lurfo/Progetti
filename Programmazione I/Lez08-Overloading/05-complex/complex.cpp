//Specifica delle funzioni della classe complex
#include "complex.h"
#include <iostream>
#include <sstream>
#include <string>

Complex::Complex(double r, double c){
    //Nel caso del costruttore andiamo a sfruttare la funzione di inserimento dei valori che abbiamo definito
    setValues(r,c);
}

Complex::Complex(const Complex& copio):
real{copio.real}, imm{copio.imm}{}

Complex::~Complex(){
    std::cout<<"Elimino il numero: "<<toString()<<"\n";
}

void Complex::setValues(double r, double c){

    real=r;
    imm=c;
}

std::string Complex::toString() const{

    std::ostringstream output;

    output<<real<<"+"<<imm<<"i";

    return output.str();

}

std::ostream& operator<<(std::ostream& output, const Complex& num){

    output<<num.toString();

    return output;
}

Complex& Complex::operator=(const Complex& sec){

    real=sec.real;
    imm=sec.imm;

    return *this;

}

Complex& Complex::operator+=(const Complex& sec){
    real+=sec.real;
    imm+=sec.imm;

    return *this;
}

Complex& Complex::operator-=(const Complex& sec){

    real-=sec.real;
    imm-=sec.imm;

    return *this;

}

Complex& Complex::operator*=(const Complex& sec){
    double tengo;
    tengo=real;
    real=(real*sec.real-imm*sec.imm);
    imm=(tengo*sec.imm+imm*sec.real);

    return *this;
}

Complex operator+(const Complex& uno, const Complex& due){

    Complex tengo{uno};

    tengo+=due;

    return tengo;

}

Complex operator-(const Complex& uno, const Complex& due){
    Complex tengo{uno};

    tengo-=due;

    return tengo;
}

Complex operator*(const Complex& uno, const Complex& due){
    Complex tengo{uno};

    std::cout<<"Valore della variabile temp: "<<tengo<<"\n";

    tengo*=due;

    return tengo;
}