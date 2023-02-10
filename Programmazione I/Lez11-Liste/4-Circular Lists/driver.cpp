#include <iostream>
#include <string>

#include "list.h"

using std::cout; 
using std::cin;
using std::endl;

int main(){
    CList<int> prova; 
    int numero;



    do{
        cout<<"Inserisci elementi all'interno della lista! [0 - Per Terminare]\n";
        cin>>numero;

        if(numero!=0){
            prova.add(numero);
        }
    
    }while(numero!=0);

    cout<<"La dimensione della stringa è: "<<prova.size()<<endl;

    cout<<"Nella lista ci sono gli elementi: \n";

    cout<<prova.toString()<<"\n";

    cout<<"Posso andare anche a spostare il cursore della lista!\n";

    prova.advance();

    cout<<"La lista ora ha come cursore:\n";
    cout<<prova.toString()<<"\n";

    cout<<"----------------------------------\n";

    cout<<"Posso andare ad eliminare l'elemento successivo al cursore della lista!\n";

    cout<<"Ti mostro prima la lista!\n";
    cout<<prova.toString()<<endl;
    
    cout<<"Il front: "<<prova.front()<<"\n";
    cout<<"Il back: "<<prova.back()<<"\n";

    cout<<"Elimino l'elemento\n";
    prova.remove();

    cout<<"La lista ha come dimensione: "<<prova.size()<<endl;

    cout<<"Ti mostro la lista con l'elemeto rimosso\n";
    cout<<prova.toString()<<endl;

    cout<<"Il front: "<<prova.front()<<"\n";
    cout<<"Il back: "<<prova.back()<<"\n";

    cout<<"Il front è stato elimanto!\n";

    cout<<"Come visto sopra il front è: "<<prova[0]<<"\n";
    cout<<"Mente il cursor è uguale a: "<<prova[prova.size()-1]<<"\n";



}