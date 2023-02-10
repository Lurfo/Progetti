//Specifica del programma che va a definire il funzionamento della lista generica con interi!
#include "list.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main(){

    int elemento;
   
    //Il modo in cui andiamo a definire la nostra lista ora è leggermiente differente, dobbiamo andare a specificare il tipo di elemento che usiamo!
    //La specifica quindi diventa molto simile a quella dei vettori, che essendo anch'essi una classe generica
    //Poichè possiamo inserire al loro interno un qualsiasi tipo di elemento, si dichiarano in modo molto simile!
    LinkedList<int> lista;


    do{
        cout<<"Inserisci elemento all'interno della lista [0 - Per terminare]\n";
            cin>>elemento;
        if(elemento!=0){
            lista.addFront(elemento);
        }
    }while(elemento!=0);


    

    cout<<"All'interno della lista ci sono: "<<lista.size()<<" elementi!\n";

    cout<<"Ti mostro quelli che sono gli elementi della lista!\n";

    for(int i=0; i<lista.size(); i++){
        cout<<lista[i]<<((i!=lista.size()-1) ? ", " : " ");
    }

    cout<<endl;

    cout<<"------------------\n";

    cout<<"Vado ad elimare il primo elemento della lista\n";

    lista.removeFront();

    cout<<"La nuova lista è uguale a: \n";

    for(int i=0; i<lista.size(); i++){
        cout<<lista[i]<<((i!=lista.size()-1) ? ", " : " ");
    }

    cout<<endl;

    cout<<"---------------------\n";

    cout<<"Posso però andare sempre ad aggiungere molti altri elementi!\n";

    do{
        cout<<"Inserisci elemento all'interno della lista [0 - Per terminare]\n";
            cin>>elemento;
        if(elemento!=0){
            lista.addFront(elemento);
        }
    }while(elemento!=0);

    cout<<"La nuov lista è uguale a:\n";

    for(int i=0; i<lista.size(); i++){
        cout<<lista[i]<<((i!=lista.size()-1) ? ", " : " ");
    }

    cout<<endl;

    cout<<"Essa ha dimensione uguale a: "<<lista.size()<<"\n";

}