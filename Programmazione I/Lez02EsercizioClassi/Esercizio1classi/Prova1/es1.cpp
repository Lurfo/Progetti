#include <iostream>
#include "es1.h" //Includo nel programma la classe
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(){
//Definizione dell'oggetto della classe Account
    Account prova;
    string nome; 
    int saldo{0};

    cout<<"Dimmi il nome della persona"<<endl; 
    getline(cin, nome);

    cout<<"Dimmi il suo saldo"<<endl;
    cin>>saldo;

//Imposto nella Classe name e balance

    prova.setName(nome);
    prova.setBalance(saldo);

//Prelevo dalla classe name e Balance
/*Nota, non ho bisogno di impostare argomenti 
nelle funzioni perchè non ne ho dichiarati nella 
classe, mi restituiscono solo un valore*/

    cout<<"Abbiamo: "<<prova.getName()<<endl;
    cout<<"Con un saldo di: "<<prova.getBalance()<<endl;

}