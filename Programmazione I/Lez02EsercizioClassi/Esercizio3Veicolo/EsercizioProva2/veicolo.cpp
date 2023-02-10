#include <iostream>
#include <string>
#include "veicoloc.h"

using std::cout;
using std::cin;
using std::string;
using std::endl;

void validafunz(char* risp){
    while(*risp!='y' and *risp!='n'){
        cout<<"Hai inserito una rispota non valida!\n";
        cout<<"Inseriscine una corretta![y/n]"<<endl;
        cin>>*risp;
    }

    return;

}

int main(){
    Vehicle veicolo{"Harley", "Diesel",-2015 ,"Arancio","120 Cavalli"};
    char risp;

    cout<<"Ho i dati di questo veicolo salvati"<<endl;
    veicolo.displayVehicle();

    cout<<"Vuoi modificare i dati?[y/n]\n";
    cin>>risp; 

    validafunz(&risp);

    while(risp=='y'){
        cin.ignore(100,'\n');

        veicolo.setAllStats();

        cout<<"Vuoi rivedere i dati inseriti?[y/n]\n ";
        cin>>risp;

        validafunz(&risp);

        if(risp=='y'){
            cout<<"Ti faccio rivedere i dati inseriti\n";
            veicolo.displayVehicle();
        }

        cout<<"Vuoi modificare i dati?[y/n]\n";
        cin>>risp;

        validafunz(&risp);
    }

}