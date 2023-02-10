#include <iostream>
#include <fstream>
#include "accounts.h"

using std::fstream;
using std::ios;
using std::cout;
using std::endl;
using std::cin; 

void mostro(Account&);


int main(){
    fstream scrivoInBin("client.dat",  ios::in | ios::out | ios:: binary);

    if(!scrivoInBin){
        std::cerr<<"Non posso aprire il file"<<endl;
        exit(EXIT_FAILURE);
    }

    

    int numeroAccount;
    string nome, cognome;
    double saldo; 

    do{
    std::cout<<"Dimmmi il numero di conto(da 1 a 100!)\n";
    cin>>numeroAccount;

    while(numeroAccount<0 && numeroAccount >100){
        cout<<"I valori che hai inserito non sono corretti\n";
        cin>>numeroAccount;
    }

    if(numeroAccount!=0){
    cout<<"Inserisci Nome, Cognome, Saldo\n";
    cin>>nome;
    cin>>cognome;
    cin>>saldo;

    //Definisco un oggetto di tipo acocunt instanziato con i valori che ci occorrono!
    Account elemento{numeroAccount, nome, cognome, saldo};
    //Vado ad inserire l'elemento che ho definito all'interno del file!

    scrivoInBin.seekp((elemento.getNum()-1)*sizeof(Account));
    scrivoInBin.write(reinterpret_cast<const char*>(&elemento), sizeof(Account));
    }

    }while(numeroAccount!=0);

    //visto che il file che ho definito è sia in lettura che in scrittura vado a mostrare a video gli elementi 
    //Sposto il puntatore all'inizio!

    scrivoInBin.seekg(0);


    while(scrivoInBin){
        Account elementomostro; 
        scrivoInBin.read(reinterpret_cast<char*>(&elementomostro), sizeof(Account));
        if(elementomostro.getNum()!=0){
            mostro(elementomostro);
        }
    }

   

}

void mostro(Account& element){
    cout<<"Numero: "<<element.getNum()<<"\n";
    cout<<"Nome:"<<element.getName()<<"\n";
}

