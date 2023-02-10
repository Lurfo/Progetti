#include <iostream>
#include <string>
#include "veicoloc.h"

using std::cout;
using std::cin;
using std::string;
using std::endl;

int main(){
    Vehicle veicolo{"Harley", "Diesel",-2015 ,"Arancio","120 Cavalli"};
    
    string modello, fuelType, color, cavalli;
    int yearMan{0};
    char risp;

    cout<<"Ho i dati di questo veicolo salvati"<<endl;
    veicolo.displayVehicle();

    cout<<"Vuoi modificare i dati?[y/n]\n";
    cin>>risp; 

    while(risp=='y'){
        cin.ignore(100,'\n');

        cout<<"Inserisci il modello del veicolo: ";
            getline(cin, modello);

        
        cout<<"Inserisci il tipo di carburante: ";
            getline(cin, fuelType);


        cout<<"Inserisce il colore: ";
            getline(cin, color);

        cout<<"Inserisci i cavalli del motore: ";
            getline(cin, cavalli);


        cout<<"Inserisci l'anno di produzione: ";
            cin>>yearMan;

            while (cin.fail()){
                cin.clear();
                cin.ignore(100, '\n');
                cout<<"L'anno che hai inserito non è valido!"<<endl;
                cin>>yearMan;
            }
            

        cout<<"-----------------------------------\n";
        cout<<"Salvo tutti dati che mi hai inserito\n";
        veicolo.setMake(modello);
        veicolo.setFuel(fuelType);
        veicolo.setColor(color);
        veicolo.setEngine(cavalli);
        veicolo.setYear(yearMan);
        cout<<"-----------------------------------\n";

        cout<<"Vuoi rivedere i dati inseriti?[y/n]\n ";
        cin>>risp;

        if(risp=='y'){
            cout<<"Ti faccio rivedere i dati inseriti\n";
            veicolo.displayVehicle();
        }

        cout<<"Vuoi modificare i dati?[y/n]\n";
        cin>>risp;
    }

}