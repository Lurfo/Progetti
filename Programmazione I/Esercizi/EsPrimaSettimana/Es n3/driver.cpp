#include "list.h"

#include <iostream>

using std::cout; 
using std::cin; 
using std::endl; 

int main(){
    CList<int> p; 
    int num; 

    do{
        cout<<"Inserisci elemento! 0 - Per terminare\n";
            cin>>num; 

        if(num!=0){
            p.add(num);
        }
    }while(num!=0);

    cout<<"Nella lista ci sono: "<<p.size()<<" elementi!\n";

    cout<<"Ti mostro gli elementi che sono contenuti nella lista! Usando la funzione apposita!\n";
    cout<<p.toString()<<"\n";

    cout<<"-----------------------------------\n";

    cout<<"Ti mostro gli elementi usando l'operator[]\n"; 

    for(int i=0; i<p.size(); i++){
        cout<<p[i]<<((i!=p.size()-1) ? ", ":"\n");
    }

    cout<<"---------------------------------\n";

    cout<<"Ti mostro gli elementi usando un iterator!\n";

    CList<int>::Iterator prv(p.begin());
    
    for(int i=0; i<p.size(); ++i, ++prv){
        cout<<*prv<<((i!=p.size()-1) ? ", ": "\n");
    }


    cout<<"------------------------------\n";
    
    cout<<"Parto dalla fine!\n"; 

    CList<int>::Iterator prv1(p.end());

    for(int i=0; i<p.size(); i++, --prv1){
        cout<<*prv1<<((i!=p.size()-1) ? ", ":"\n");
    }



    

}