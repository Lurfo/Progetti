#include <iostream>
#include "list.h"

using std::cout; 
using std::cin; 
using std::endl;

int main(){
    LinkedList<int> mast;  
    int num;

    do{
        cout<<"Dimmi numero da inserire - 0 Termino\n";
            cin>>num; 

        if(num!=0){
            mast.addFront(num);
        }
    }while(num!=0);

    cout<<"Nella lista ci sono gli elementi\n";
    for(int i=0; i<mast.size(); i++){
        cout<<mast[i]<<((i!=mast.size()-1) ? ", ":"\n");
    }

    cout<<"-------------------------------------\n";
    cout<<"Uso il copy constructor!\n";

    LinkedList<int> slv{mast};

    cout<<"Com' è prevedbile la nuova lista avrà gli stessi elementi di quella vecchia!\n";

    for(int i=0; i<slv.size(); i++){
        cout<<slv[i]<<((i!=slv.size()-1) ? ", ":"\n");
    }

    cout<<"-------------------------------------\n";
    cout<<"Prova dell'operatore =\n";

    //Definisco una nuova lista 

    LinkedList<int> prova;

    int elm; 

    do{
        cout<<"Dimmi elemento che devo inserire!\n";
            cin>>elm; 
        
        if(elm!=0){
            prova.addFront(elm);
        }

    }while(elm!=0);

    cout<<"Ti mostro gli elementi della lista\n";

    for(int i=0; i<prova.size(); i++){
        cout<<prova[i]<<((i!=prova.size()-1) ? ", ":"\n");
    }

    cout<<"Ora pongo la nuova lista uguale ad una vecchia lista!\n"; 

    prova=mast; 

    cout<<"Ti mostro gli elementi!\n";

    for(int i=0; i<prova.size(); i++){
        cout<<prova[i]<<((i!=prova.size()-1) ? ", ":"\n");
    }




}