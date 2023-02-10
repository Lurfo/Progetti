//Andiamo quindi a specificare le funzioni che abbiamo messo all'interno della classe
#include <iostream>
#include <stdexcept>

#include "point.h"



//Specifichiamo quindi il costruttore per la nostra classe!
Point::Point(double x, double y){
    setPointX(x);
    setPointY(y);
}

Point::~Point(){
    std::cout<<"ci penso io a distruggere tutto\n";
}

void Point::setPointX(double x){
    
    //Usiamo le eccezzioni per verificare che il valore che abbiamo inserito è compreso nell'intervallo che vogliamo
    if(x<=0 && x>=25){
        throw std::invalid_argument("I valori devono essere compresi tra 0 e 20");
    }

    else{
        //Usiamo il puntatore this per specificare che la variabile x è quella che appartiene alla classe
        this->x=x;
    }


}

//La funzione setPointY è simile alla stessa funzione che abbiamo definito prima!
void Point::setPointY(double y){

    if(y<=0 && y>=25){
        throw std::invalid_argument("I valori che hai inserito non sono corretti, devono essere compresi tra 0 e 20!");
    }

    else{
        this->y=y;
    }

}

//Andiamo poi a specificare le funzioni che hanno il compito di prelevare i dati dei punti della classe!
double Point::getPointX() const{
    return x;
}

double Point::getPointY() const{
    return y;
}

//Dunque abbiamo concluso con la specifica delle funzioni della classe!