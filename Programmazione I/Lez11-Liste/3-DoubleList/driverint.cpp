//Specifico un driver che riempie la lista di interi
#include "list.h"

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main(){

   /* DLinkedList<int> lista;
    int elemento;

    cout<<"Aggiungo un elementi all'inizio della lista\n";

    do{
        cout<<"Dimmi il numero da inserire, in modo che vado a preparare gli elementi della lista [0 - Per terminare]\n";
            cin>>elemento;

        if(elemento!=0){
            lista.addFront(elemento);
        }


    }while(elemento!=0);

    cout<<"Nella lista ci sono: "<<lista.size()<<" elementi\n";

    cout<<"--------------------------\n";

    for(int i=0; i<lista.size(); i++){
        cout<<lista[i]<<((i!=lista.size()-1) ? ", ":" ");
    }

    cout<<endl;

    cout<<"---------------------------\n";

    cout<<"Aggiungo elemento alla coda della lista!\n";

    do{
        cout<<"Dimmi il numero da inserire, in modo che vado a preparare gli elementi della lista [0 - Per terminare]\n";
            cin>>elemento;

        if(elemento!=0){
            lista.addBack(elemento);
        }
    }while(elemento!=0);

    cout<<"La lista ora contiene: "<<lista.size()<<" elementi\n";

    cout<<"Ora ti mostro la lista\n";

    for(int i=0; i<lista.size(); i++){
        cout<<lista[i]<<((i!=lista.size()-1) ? ", ":" ");
    }

    cout<<endl;

    cout<<"--------------------\n";

    cout<<"Vado a rimuovere un elemento dalla testa\n";
    lista.removeFront();

    cout<<"Rimuovo un elemento dal fondo\n";
    lista.removeBack();

    cout<<"La lista contiene: "<<lista.size()<<" elementi\n";

    cout<<"Ti mostro gli elementi\n";

    for(int i=0; i<lista.size(); i++){
        cout<<lista[i]<<((i!=lista.size()-1) ? ", ":" ");
    }

    cout<<endl;*/

    cout<<"--------------------------------------\n";

    DLinkedList<int> listaord;
    int elemento;

    cout<<"Ti mostro la lista ordinata\n";

    do{
        cout<<"Dimmi il numero da inserire, in modo che vado a preparare gli elementi della lista [0 - Per terminare]\n";
            cin>>elemento;

        if(elemento!=0){
            listaord.insertOrder(elemento);
        }
    }while(elemento!=0);

    cout<<"Mostro gli elementi\n";

    for(int i=0; i<listaord.size(); i++){
        cout<<listaord[i]<<((i!=listaord.size()-1) ? ", ":" ");
    }

    cout<<endl;
    

}