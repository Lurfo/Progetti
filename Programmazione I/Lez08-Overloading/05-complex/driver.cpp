//Secifica del driver per mostrare le caratteristiche della classe 
#include "complex.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main(){
    //Definizione di un numero complesso usado il costruttore di default che abbiamo
    Complex c1{3,5};
    
    cout<<"Il valore del complesso è uguale a: "<<c1<<"\n";

    Complex c2{2,6};

    cout<<"Ho un secondo complesso: "<<c2<<"\n";

    cout<<"Faccio la somma dei due numeri\n";

    c2+=c1;

    cout<<"c2+=c1, ottengo: "<<c2<<"\n";

    //Uso del costruttore di copia 

    Complex c3{c1};

    cout<<"Mostro il valore di c3: "<<c3<<"\n";
    cout<<"Mostro il valore di c1: "<<c1<<"\n";

    cout<<"Faccio il prodotto tra i due complessi\n";

    Complex c4;

    c4=c3*c1;

    cout<<"Il valore di c4 è: "<<c4<<"\n";





}