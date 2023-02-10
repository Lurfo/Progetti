#include <iostream>
#include "data.h"

using std::cout;
using std::cin; 
using std::endl;

int main(){

    //Andiamo ad usare l'operatore new per definire un puntatore alla classe data
    Data* provo{new Data{}};

    cout<<"il puntatore contine l'elemento che ha indirizzo: "<<provo<<"\n";
    cout<<"il puntaotre si trova all'indirizzo: "<<&provo<<"\n";
    cout<<"Ti mostro la data puntata dal puntatore: "<<provo->getData()<<"\n";

    cout<<"Elimino il puntatore usando il comando delete\n";

    //Andiamo dunque ad eliminare l'elemento che è contenuto all'interno della zona di memoria puntata dal puntatore!
    delete provo;

    cout<<"Dal messaggio vediamo proprio che viene chiamato in causa il distruttore per eliminare l'elemento che punta il puntatore!\n";
    




}