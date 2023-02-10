//Andiamo a definire il driver che ha come scopo quello di mostrare le "capacità" delle classi definite!
//Ovviamente dobbiamo includere ogni singola classe per poterla sfruttare!
#include "employees.h"
#include "base.h"
#include "baseecomm.h"
#include "commission.h"

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::vector;
using std::cin; 
using std::endl;

void puntatore(Employees*);
void riferimento(Employees&);

int main(){
    //Definizione dei singoli membri di tutte le classi che abbiamo!
    //Employees s; //Non commentare questo campo genera errore, poichè, come sappiamo, essendo employees una abstract non possiamo instanziarla!

    Base primo{"Giovanni", "Pinotto", "1.12321", 1800.90};
    Commission sec{"Mario", "Rossi", "123kckdk13", 12342, 0.6};
    BaseEComm ter{"Mimmo", "Mario", "majfj2j34j4", 12431, 0.9, 1000};


    //Andiamo quindi a specificare quali sono le caratteristiche delle varie classi usando il late binding per definire farci stampare a video tutte
    //le informazioni di cui abbiamo bisogno!
    cout<<"Ti mostro il dipendente base: \n";
    cout<<primo.toString()<<"\n";

    cout<<"------------------------------------------------\n";

    cout<<"Ti mostro il dipendente su commissioni!\n";
    cout<<sec.toString()<<"\n";
   
   cout<<"--------------------------------------------------\n";

    cout<<"Ti mostro il dipendente base+commissioni\n";
    cout<<ter.toString()<<"\n";
    cout<<ter.guadagni()<<"\n";
    
    cout<<"--------------------------------------------------\n";


    //Da questo punto in poi andiamo a sfruttare quello che è il late binding
    //Inizialmente andiamo a definire un vettore di puntatori alla classe base!
    vector<Employees*> ptr;

    //Inseriamo all'interno del vettore quelli che sono i valori degli indirizzi di ogni oggetto che noi abbiamo definito!
    ptr.push_back(&primo);
    ptr.push_back(&sec);
    ptr.push_back(&ter);

    //A questo punto possiamo vedere come funziona il late binding tramite puntatore!

    cout<<"Late binding con riferimento tramite puntatore alla classe base\n";

    for(Employees* i: ptr){
        puntatore(i);
    }

    cout<<"Late Binding con passaggio per riferimento della classe base!\n";

    for(Employees* i:ptr){
        riferimento(*i);
    }

}

//Specifica della funzione che prende in ingresso gli oggetti per puntatore!
void puntatore(Employees* punto){
    cout<<punto->toString()<<"\n";
    cout<<"-------------------------------------------------\n";
}

void riferimento(Employees& riferisco){
    cout<<riferisco.toString()<<"\n";
    cout<<"--------------------------------------------------\n";
}