#include <iostream>
#include "list.h"
#include <array>

using std::cout; 
using std::cin; 
using std::endl; 

template <typename T>
void divide(LinkedList<T>&, LinkedList<T>&, LinkedList<T>&);

int main(){
    LinkedList<int> mast; 
    int num; 

    do{
        cout<<"Inserisci elemento - 0 Per terminare\n"; 
            cin>>num; 
        
        if(num!=0){
            mast.addFront(num);
        }
    }while(num!=0);

    cout<<"Nella lista ci sono: "<<mast.size()<<" elementi!\n";
    cout<<"Il primo elemento della lista è uguale a: "<<mast.getFront()<<endl;
    cout<<"------------------------\n";
    
    cout<<"Ti mostro gli elementi usando il ciclo for!\n";

    for(int i=0; i<mast.size(); i++){
        cout<<mast[i]<<((i!=mast.size()-1) ? ", ":"\n");
    }

    cout<<"---------------------------\n"; 

    cout<<"Ti mostro gli elementi usando un iterator!\n"; 

    LinkedList<int>::Iterator prova(mast.begin()); 
    int i{0};

    for(prova; prova!=mast.end(); ++prova){
        cout<<*prova<<((i!=mast.size()-1) ? ", ":"\n");
        i++;
    }

    cout<<"-----------------------------\n"; 

    cout<<"Separo gli elementi all'interno di due liste, una che contiene gli elementi in posizione pari e una quelli dispari!\n"; 
    LinkedList<int> pari; 
    LinkedList<int> disp; 

    //Passo la lista da dividere e le due liste dove dividerla!
    divide(mast, pari, disp);

    cout<<"Ti mostro le liste\n"; 

    LinkedList<int>::Iterator pa(pari.begin());
    LinkedList<int>::Iterator dis(disp.begin());
    LinkedList<int>::Iterator mas(mast.begin());

    cout<<"Elementi lista iniziale\n";
    i=0;
    for(mas; mas!=mast.end(); ++mas){
        cout<<*mas<<((i!=mast.size()-1) ? ", ":"\n");
        i++;

    }

    cout<<"Elementi lista pari\n"; 
    i=0;
    for(pa; pa!=pari.end(); ++pa){
        cout<<*pa<<((i!=pari.size()-1) ? ", ":"\n");
        i++;
    } 

    cout<<"Elementi lista disp\n"; 
    i=0; 
    for(dis; dis!=disp.end(); ++dis){
        cout<<*dis<<((i!=disp.size()-1) ? ", ":"\n");
        i++;
    }

}


//Specifica della funzione che divide!
template <typename T> 
void divide(LinkedList<T>& mast, LinkedList<T>& pari, LinkedList<T>& disp){
    
    typename LinkedList<T>::Iterator prov(mast.begin());

    /*for(int i=1; i<=mast.size(); ++i){
        if(i%2==0){
            pari.addFront(*prov);
        }

        else{
            disp.addFront(*prov);
        }

        ++prov;

    }*/

    //Voglio salvare gli elementi all'interno di un vettore!
    //In questo modo posso andarli ad inserire in ordine corretto all'interno della lista!
    T arr[mast.size()];

    for(int i=0; i<mast.size(); i++){
        arr[i] = *prov;
        ++prov;
    }

    //Dopo che gli elementi della lista iniziale sono stati inseriti all'interno di un array, scorrendolo all'incontrario posso andare a ripercorrere
    //tutti gli elementi, nel verso in cui sono stati inseriti inizialmente! Di conseguenza ho delle liste ordinate!

    for(int k=mast.size()-1; k>=0; k--){
        if((k+1)%2==0){
            pari.addFront(arr[k]);
        }

        else{
            disp.addFront(arr[k]);
        }
    }
    

}

