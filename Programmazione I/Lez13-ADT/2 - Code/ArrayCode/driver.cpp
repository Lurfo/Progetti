#include <iostream>
#include "code.h"

using std::cout;
using std::cin; 
using std::endl;

int main(){
    Code<int> pr; 
    int numero{0};
    try{
    do{
        cout<<"Inserisci un elemento all'interno della coda! [0 - Per Terminare]\n";
            cin>>numero;

        if(numero!=0){
            pr.enqueue(numero);
        }

    }while(numero!=0);

    }

    catch(std::invalid_argument e){
        std::cerr<<e.what()<<"\n";
    }

    cout<<"Ti faccio vedere il fronte della coda: \n";
    cout<<"Fronte: "<<pr.front()<<"\n";

    cout<<"Elimino il fronte che ti ho fatto vedere:\n";


    pr.dequeue();

    cout<<"Fronte: "<<pr.front()<<"\n"; 

    pr.enqueue(123432);

    while(!pr.empty()){
        pr.dequeue();
    }

    if(pr.empty()){
        cout<<"La lista ormai è vuota!\n";
    }




   
    
    

}