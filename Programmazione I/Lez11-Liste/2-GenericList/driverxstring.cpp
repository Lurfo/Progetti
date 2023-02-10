//Vado a specificare un nuovo driver che utilizza la lista per inserire delle stringhe all'interno della lista!

#include "list.h"

#include <iostream>
#include <string>

using std::string;
using std::cout; 
using std::cin; 
using std::endl;

int main(){
    string elemento;

    LinkedList<string> lista;

    do{
        cout<<"Dimmi l'elemento da inserire all'interno della lista! [0 - Per terminare]\n";
        cin>>elemento;

        if(elemento!="0"){
            lista.addFront(elemento);
        }

    }while(elemento!="0");

    cout<<"Nella lista hai inserito: "<<lista.size()<<" elementi\n";

    cout<<"Ti mostro gli elementi della lista!\n";

    for(int i=0; i<lista.size(); i++){
        cout<<lista[i]<<((i!=lista.size()-1) ? ", " : " ");
    }

    cout<<endl;

    //Anche andando ad inserire altre tipologie di elementi all'interno della lista essa funziona allo stesso modo!
}