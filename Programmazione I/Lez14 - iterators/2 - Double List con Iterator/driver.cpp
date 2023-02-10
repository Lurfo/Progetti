//Definisco un driver che mi fa utilizzare un iterator!
#include "list.h"
#include <iostream>

using std::cout; 
using std::cin; 
using std::endl;

int main(){
    //Dim;chiaro una nuova lista di numeri!
    List<int> nuova; 
    int numero;

    do{
        cout<<"Inserisci - 0 Per terminare\n";
            cin>>numero; 
        
        if(numero!=0){
            nuova.insertFront(numero);
        }

    }while(numero!=0);

    cout<<"Nella lista ci sono: "<<nuova.size()<<" elementi\n";
    cout<<"Uso gli iterator per farti vedere il primo elemento e l'ultimo della lista\n";

    List<int>::Iterator p(nuova.begin());
    List<int>::Iterator p1(nuova.end()); 

    --p1; //Devo decrementare il valore di p1, poichè la funzione end restituisce direttanente il trailer della lista!
    
    cout<<"Il front è: "<<*p<<"\n";
    cout<<"Il back è: "<<*p1<<"\n";

    cout<<"Usando gli iterator scorro tutta la lista, partendo dal front!\n";
    for(p; p!=nuova.end(); ++p){
        cout<<*p<<((p!=p1)? ", " : " " );
    }
    cout<<endl;

    
    //Devo fare in modo che il primo iterator punti esattamente all'head!
    List<int>::Iterator p2(nuova.begin());
    --p2;

    cout<<"Con gli iterator posso andare a scorrere la lista anche al contrario in modo molto semplice!\n";
  
    for(p1; p1!=p2; --p1){
        cout<<*p1<<((p1!=nuova.begin()) ? ", ":" ");
    }

    cout<<endl;

}