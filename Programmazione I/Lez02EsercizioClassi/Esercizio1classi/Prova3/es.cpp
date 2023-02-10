#include <iostream>
#include "es.h"
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

 Account primo;

void aggiungi(){
    int denaro{0};
    
    cout<<"Quanto denaro vuoi depositare?\n";
    cin>>denaro;

    primo.addBalance(denaro);

}

void togli(){
    int denaro{0};

    cout<<"Quanrto denaro dobbiamo prelevare?\n";
    cin>>denaro;

    primo.subBalance(denaro);

}


int main(){
    int saldo{0};
    string nome; 
    char risp;
    string risp1;

    cout<<"Inserire il nome:\n";
    getline(cin,nome);

    cout<<"Inserire il bilancio\n";
    cin>>saldo;

    cout<<"Registro i dati nella banca dati\n";

        primo.setName(nome);
         primo.setBalance(saldo);

    cout<<"Vuoi effetturare altro operazioni?\n [y/n]\n";
    cin>>risp;

    if(risp=='y'){

            while(risp1!="stop"){
                cout<<"Cosa vuoi fare?\n[aggiungi/togli]\n";
                cin>>risp1;
                
                if(risp1=="aggiungi")
                    aggiungi();

                else if (risp1=="togli")
                    togli();


            cout<<"Puoi dirmi stop per fermarmi!\n";

            }
            

        }

    cout<<"Abbiamo l'account di: "<<primo.getName()<<"\n";
    cout<<"Con un saldo di: "<<primo.getBalance()<<"\n";
    

}