//Andiamo a vedere quelle che sono le strutture ADT che ho definito prima usando la STL!
#include <iostream>
#include <stack> //Questa implementazione dello stack utilizza una versione basata su vector!
#include <queue>
#include <deque>

using std::stack; 
using std::queue;
using std::deque;
using std::cout;
using std::cin; 
using std::endl;

int main(){
    //Bene o male l'uso di quelle ADT della stl è simile a quella che ho implementato precedentemente!
    stack<int> stac;
    queue<int> coda; 
    deque<int> dque;

    //Le adt che ho definito sopra hanno tutte le medesime funzioni che ho implementato anche all'interno delle mie strutture dati!
    int num; 

    do{
        cout<<"Inserimento nello stack - 0 per terminare\n"; 
            cin>>num;
        
        if(num!=0){
            stac.push(num);
        }
    }while(num!=0);


    do{
        cout<<"Inserimento elementi nella coda! 0 Per terminare\n";
            cin>>num; 
        
        if(num!=0){
            coda.push(num);
        }
    }while(num!=0);



    do{
        cout<<"Inserisci elementi nella deque - 0 Per terminare!\n";
            cin>>num;

        if(num!=0){
            dque.push_front(num);
        }    
    }while(num!=0);


    cout<<"Hai inserito tutti gli elementi all'interno delle funzioni!\n";

    cout<<"Dimensione dello stack: "<<stac.size()<<"\n";
    cout<<"Dimensione della coda: "<<coda.size()<<"\n";
    cout<<"Dimensione della deque: "<<dque.size()<<"\n";

    cout<<"Ti mostro tutti gli elementi che sono presenti all'interno delle ADT\n";

    cout<<"Elementi nello stack - Policy FILO\n";
    while(!stac.empty()){
        cout<<stac.top()<<((stac.size()!=1) ? ", " : " ");
        stac.pop();
    }

    cout<<endl;

    cout<<"Elementi nella coda - Policy FIFO\n";
    while(!coda.empty()){
        cout<<coda.front()<<((coda.size()!=1) ? ", " : " ");
        coda.pop();
    }

    cout<<endl;

    cout<<"Elementi che si trovano nella Deque - Usiamo una policy generica, in questa lista posso scorrere sia da sinistra che da destra\n";
    while(!dque.empty()){
        cout<<dque.front()<<((dque.size()!=1) ? ", " : " ");
        dque.pop_front();
    }

    cout<<endl;


}