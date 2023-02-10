//Specifico una funzione che ha la possibilità di andare a usare le funzioni per gestire un file!
#include "accounts.h"
#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::fstream;
using std::ios;
using std::cin; 
using std::cout;
using std::endl; 

void inserisco(fstream&, int);
void salvataggio(fstream&);

int main(){
    int numero;
    //Apro il file che mi serve per salvare i dati!
    fstream salvo{"client.dat", ios::in | ios::out | ios::binary};

    if(!salvo){
        std::cerr<<"Non posso aprire il file"<<endl;
        exit(EXIT_FAILURE);
    }

    //Vado ad inserire gli elementi all'interno del file binario usando la funzione!
    cout<<"Dimmi il numero che voglio inserire\n";
    cin>>numero;
    
    while(numero>0 && numero<=100){
        inserisco(salvo, numero);
        cout<<"Dimmi il numero!";
        cin>>numero;
    }

    cout<<"Ho inserito tutti gli elementi che mi avevi chiesto!\n";
    cout<<"Li salvo\n";

   
    salvataggio(salvo);
   

}

void inserisco(fstream& binario, int numercont){

    string nome, cognome;
    double saldo;
    
    cout<<"Dimmi il nome, il cognome e il bilancio\n";
    cin>>nome;
    cin>>cognome; 
    cin>>saldo; 

    //Inizializzo la classe con i dati che ho scelto!
    Account elemento{numercont, nome, cognome, saldo}; 

    binario.seekp((elemento.getNum()-1)*sizeof(Account));
    binario.write(reinterpret_cast<char*>(&elemento), sizeof(Account));

}

void salvataggio(fstream& binario){
    std::ofstream elementosal{"salvo.txt", ios::out};

    Account salvo;
    
    //Serve per riportare il puntatore all'inizio poichè è stato spostato dalla funzione che ha il compito di andare ad inserire il valore all'interno del
    //del file binario!
    binario.seekg(0);
    binario.read(reinterpret_cast<char*>(&salvo), sizeof(Account));

    while(binario){
        if(salvo.getNum()!=0){
            elementosal<<salvo.getNum()<<" "<<salvo.getName()<<" "<<salvo.getLast()<<" "<<salvo.getBal()<<endl;
        }

        binario.read(reinterpret_cast<char*>(&salvo), sizeof(Account));
    }

}

