//Andiamo a definire una funzione che ha il compito di mostrare quali sono le caratteristiche di tutte le classi che abbiamo definito 
//Ovviamente, dobbiamo includere tutte le classi per poterle utilizzare 
#include "account.h"
#include "SavingsAccout.h"
#include "CheckingAccount.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main(){
    cout<<"Ti mostro quali sono le caratteristiche della classe base e di quelle derivate\n";

    //Cominciamo partendo con la classe base
    Account base; 
    cout<<"Ho che il contenuto del conto è di: "<<base<<"€\n";

    //Andiamo ad usare alcune delle funzioni
    base.depositBase(10000);
    cout<<"Dopo aver depositato ho un saldo di: "<<base<<"€\n";

    base.withdrawBase(100);
    cout<<"Ho prelevato e ora il saldo è di: "<<base<<"€\n";

    cout<<"-----------------------------------------------\n";

    //Passiamo a definire la classe CheckingAccount che contiene delle specifiche aggiuntive!

    CheckingAccount derivo1{1000, 1.50};

    cout<<derivo1<<"\n";

    //Prelievo
    derivo1.withdraw(50);
    //Deposito
    derivo1.deposit(1200);

    cout<<derivo1<<"\n";

    cout<<"------------------------------------------------\n";

    //Passiamo a definire l'ultima classe derivata 

    SavingsAccount conse{10000, 3};

    cout<<conse<<"\n";

    conse.setAnni(20).totaleDopoGliAnni(20);
    

    cout<<conse<<"\n";

}