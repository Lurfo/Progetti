#include <iostream>
#include "es1,2.h"
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(){
    //Do all'oggetto di cui ho bisogno un valore inizializzato
    Account prova{"Giordano Bruno", 12345};

    cout<<"Abbiamo un account di: "<<prova.getName();

    cout<<"\nCon un saldo di: "<<prova.getBalance()<<endl;
}