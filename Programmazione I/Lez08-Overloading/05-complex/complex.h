//Definizione della classe che specifica i numeri complessi
#include<string>

#ifndef COMPLEX_H
#define COMPLEX_H

class Complex{

    //Specifica dell'operaotre di stampa a schermo
    friend std::ostream& operator<<(std::ostream&, const Complex&);

    private: 
        double real;
        double imm;

    public:

        //Definizione del costuttore
        Complex(double =0.0, double =0.0);
        Complex(const Complex&);

        //Definizione del distruttore
        ~Complex();

        //Definizione della funzione per impostare i valori del numero complesso
        void setValues(double, double);

        //Definizione della funzione che ha il compito di definire il numero all'interno di una stringa
        std::string toString() const;

        //Definizione delle varie operazione tra i numeri complessi 
        Complex& operator=(const Complex&);
        Complex& operator+=(const Complex&);
        Complex& operator-=(const Complex&);
        Complex& operator*=(const Complex&);
        
};


Complex operator+(const Complex&, const Complex&);
Complex operator-(const Complex&, const Complex&);
Complex operator*(const Complex&, const Complex&);


#endif