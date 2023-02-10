//Vado a definire un programma che utilizza l'heap!
#include "heap.h"
#include <iostream>

using std::cout; 
using std::cin; 
using std::endl; 

int main(){
    Heap prova; 
    int numero; 
    
    for(int i=1; i<prova.size(); i++){
        cout<<"Dimmi numero\n";
            cin>>numero; 
            prova.add(numero);
    }
    
    prova.vedo();

    prova.buildHeap(); 

    prova.vedo();

}