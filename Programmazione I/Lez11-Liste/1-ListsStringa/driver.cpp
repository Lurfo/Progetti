//Verifica delle capacità della lista 

#include <iostream>
#include "StringList.h"

using std::cout;
using std::cin; 
using std::endl;

int main(){
    StringList lista; 

    if(lista.empty()){
        cout<<"La lista è ancora vuota!\n"; //controlla che la lista sia vuota!
    }

    //Aggiungo un elemento!
    lista.addFront("Semaforo");
    lista.addFront("Macchina");
    lista.addFront("Sempre");
    lista.addFront("sono");
    lista.addFront("bello");
    lista.addFront("Tokyo");
    lista.addFront("Aereo");

    cout<<"Il primo elemento è: "<<lista.front()<<"\n";
    cout<<"La lunghezza della lista è: "<<lista.size()<<"\n";

    //Eliminazione di un elemento alla testa!

    lista.removeFront();

    cout<<"Il nuovo fronte è: "<<lista.front()<<"\n";
    cout<<"Ora la lunghezza della lista è: "<<lista.size()<<"\n";

    cout<<"Ti mostro gli elementi che ci sono nella lista usando l'operatore []\n";

    for(int i=0; i<lista.size(); i++){
        cout<<"Elemento "<<i+1<<": "<<lista[i]<<((i==lista.size()-1) ? " ": ", ");
    }

    cout<<endl;

}