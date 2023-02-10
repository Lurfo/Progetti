#include <iostream>
#include "list.h"
#include "dqueue.h"



using std::cin; 
using std::cout; 
using std::endl; 

int main(){
    //Prova fatte per verificare il funzionamento della lista!
    /*int num; 

    DList<int> prova;

    do{
        cout<<"Dimmi 0 Fermo\n"; 
            cin>>num; 

        if(num!=0){
            prova.addFront(num);
        }
    }while(num!=0);

    cout<<"Dimensione: "<<prova.size()<<"\n"; 
    cout<<"fronte: "<<prova.front()<<"\n";

    cout<<"Elimino il fronte: \n";

    prova.removeFront(); 

    cout<<"Dimensione: "<<prova.size()<<"\n"; 
    cout<<"fronte: "<<prova.front()<<"\n";*/

    //----------------------------------------------------------------------------------

    Queue<int> coda; 
    int numero;

    coda.empty();


    do{
        cout<<"Inserisci elementi all'interno della coda!\n";
            cin>>numero;

        if(numero!=0){
            coda.insertFront(numero);
            cout<<"Sono stati inseriti: "<<coda.size()<<" elementi\n";
        }

    }while(numero!=0);

    cout<<"Nella coda ci sono in totale: "<<coda.size()<<" elementi\n";
    cout<<"Il primo elemento da estrarre è : "<<coda.front()<<"\n";
    cout<<"L'ultimo elemento da estrarre è: "<<coda.back()<<"\n";

    cout<<"Rimuovo il primo e l'ultimo elemento!\n";
    coda.removeFront(); 
    coda.removeBack(); 

    cout<<"Nella coda ci sono in totale: "<<coda.size()<<" elementi\n";
    cout<<"Il primo elemento da estrarre è : "<<coda.front()<<"\n";
    cout<<"L'ultimo elemento da estrarre è: "<<coda.back()<<"\n";
    
    cout<<"Posso però anche inserire degli elementi alla posizione dell'ultimo elemento da estrarre!\n";

    coda.insertBack(12);
    coda.insertBack(23);

    cout<<"Infatti ora ho che l'ultimo elemento è: "<<coda.back()<<"\n";


}