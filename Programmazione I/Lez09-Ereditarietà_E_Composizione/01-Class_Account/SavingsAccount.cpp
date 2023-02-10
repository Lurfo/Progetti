//Andiamo a specificare quelle che sono tutte le funzioni della classe SavingsAccount 
#include "SavingsAccout.h"
#include <sstream>
#include <cmath>
#include <sstream>

//Specifica del costruttore
//Per impostare il valore del conto chiamiamo sempre il costruttore di default
SavingsAccount::SavingsAccount(double inBal, double rate, double anni):
Account(inBal), capitale{0.0}{
    setInteresse(rate);
    setAnni(anni);
}

SavingsAccount& SavingsAccount::setAnni(double y){

    if(y>=0){
        anni=y;
    }

    else 
        throw std::invalid_argument("Guarda che l'anno che hai inserito non va bene");

    
    return *this;


}

void SavingsAccount::setInteresse(double i){
    //Imaginando che il valore che l'utente inserisce all'interno della classe sia della forma a%, lo andiamo a definire in decimali
    tassoInteresse=i/100; //In questo modo andiamo a considerare solo il valore decimale
}


double SavingsAccount::getInteresse(){
    return tassoInteresse;
}

//Andiamo a esprimere la funzione che ha il compito di calcolare a quanto ammonta poi il capitale dopo un certo numero di anni 
double SavingsAccount::totaleDopoGliAnni(int y){

    //Per ottere il valore del capitale dopo un certo numero di anni andiamo ad usare l'algoritmo predefinito
    //ATTENTO, dobbiamo usare la funzione getBalance della classe per ottenere il valore del bilancio, questo perchè le funzioni della classe derivata
    //Non possono accedere direttamente alle variabili membro della classe iniziale!
    capitale=getBalance()*pow(1+tassoInteresse, y);
    
    return capitale;


}

std::ostream& operator<<(std::ostream& out, const SavingsAccount& d){
    std::ostringstream output;
    
    output<<"Inizialmente avevi un bilancio di: "<<d.getBalance()<<"\nHai un tasso di interesse: "<<d.tassoInteresse*100
        <<"%. Dopo "<<d.anni<<" anni, otterrai un capitale pari a: "<<d.capitale;

    out<<output.str();

    return out;
}
