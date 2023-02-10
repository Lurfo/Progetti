//Specifica di un programma che va ad dividere una lista causale in due sottoliste a seconda degli elementi della posizione pari e quelli della posizione dispari!
#include "list.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using std::cout; 
using std::cin;
using std::endl; 


void vedo(List<int>&);



void divido(List<int>&, List<int>&, List<int>&);


int main(){
    List<int> primaria; 

    srand(static_cast<unsigned int>((time(0))));

    int num; 
    int rando; 

    cout<<"Dimmi il numero di elementi che deve avere la lista!\n"; 
        cin>>num; 

    cout<<"Dimmi i valori della lista che devo randomizzare!\n"; 
        cin>>rando; 

    for(int i=0; i<num; i++){
        primaria.insertFront((1+rand()%rando));
    }

    cout<<"Lista inizializzata, ti mostro la lista!\n"; 

        vedo(primaria);

    cout<<"Divido la lista in due sottoliste che contengono gli elementi nella posizione pari che quelli nella posizione dispari!\n"; 
    
    //Definisco le due liste in cui devo dividere la lista primaria

    List<int> pari; 
    List<int> dispari; 

    divido(primaria, pari, dispari);

    cout<<"Lista iniziale\n"; 
        vedo(primaria); 
    
    cout<<"Lista pari\n"; 
        vedo(pari); 

    cout<<"Lista dispari\n"; 
        vedo(dispari);

}


void vedo(List<int>& lista){

    for(int i=0; i<lista.size(); i++){
        cout<<lista[i]<<((i!=lista.size()-1) ? ", " : "\n");
    }

}

void divido( const List<int>& primaria, List<int>& pari, List<int>& dispari){
    //Definisco una variafile fantoccio che mi permette di identificare gli elementi che sono in posizione pari o dispari!

    //Mi salvo la massima grandezza della lista!
    int max=primaria.size();

    int i=1;

    for(List<int>::Iterator p=primaria.begin(); p!=primaria.end(); ++p, ++i){
     
        if(i%2==0){
            pari.insertBack((*p));
        }

        else{
            dispari.insertBack((*p));
        }

    }
    
}