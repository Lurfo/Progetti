//Specifico un programm in grado di andare a leggere i valori che sono contenuti all'interno del file in binario
#include"accounts.h"
#include <iostream>
#include <fstream>

using std::fstream;
using std::cin;
using std::cout;
using std::endl;
using std::ios;

void mostro(Account&);

int main(){
    fstream filelettura{"client.dat", ios::in | ios::binary};

    if(!filelettura){
        std::cerr<<"Non posso andare ad aprire il file\n";
        exit(EXIT_FAILURE);
    }

    Account elemento; 
        filelettura.read(reinterpret_cast<char*>(&elemento), sizeof(Account));

    while(filelettura){
        


        if(elemento.getNum()!=0){
            mostro(elemento);
        }

        filelettura.read(reinterpret_cast<char*>(&elemento), sizeof(Account));

    }

}

void mostro(Account& elemento){
    cout<<"L'account di: \n";
    cout<<"Numero: "<<elemento.getNum()<<"\n";
    cout<<"Nome: "<<elemento.getName()<<"\n";
}