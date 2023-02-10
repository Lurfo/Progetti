#include <iostream>
#include "rettangolo.h"

using std::cout;
using std::endl;
using std::cin;

//Questa è la funzione friend che abbiamo definito nela classe del rettangolo, così facendo possiamo vedere tutti i dati che sono contenuti in essa
const void vedo(Rett&);



int main(){

    //Come definito nel costruttore della classe rettangolo, dobbiamo andare a considerare i 4 punti che compongono i vertici del rettangolo!
    Point p1(6,4);
    Point p2(18,4);
    Point p3(6,20);
    Point p4(18,20);
    Rett prova(p1, p2, p3, p4);


    //
    cout<<"Ti mostro i punti del rettangolo:\n";
    cout<<"Valore altezza: "<<prova.altezza()<<"\n";
    cout<<"Valore della larghezza: "<<prova.larg()<<"\n";
    cout<<"Valore dell'area: "<<prova.area()<<" m^2"<<endl;
    cout<<"valore del perimetro: "<<prova.perimetro()<<" m"<<endl;
    vedo(prova);
    prova.disegno();
}

const void vedo(Rett& prova){
    cout<<"Ti mostro tutti i valori del rettangolo\n";

    cout<<"Carattere di riempimento: "<<prova.fill;
    cout<<"\nCarattere del perimetro: "<<prova.peri;
    cout<<"\nTi mostro i punti!\n";

    cout<<"p1: "<<prova.p1.getPointX()<<", "<<prova.p1.getPointY()<<"\n";
    cout<<"p2: "<<prova.p2.getPointX()<<", "<<prova.p2.getPointY()<<"\n";
    cout<<"p3: "<<prova.p3.getPointX()<<", "<<prova.p3.getPointY()<<"\n";
    cout<<"p4: "<<prova.p4.getPointX()<<", "<<prova.p4.getPointY()<<"\n";
}