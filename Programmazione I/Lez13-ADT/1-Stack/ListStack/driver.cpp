//Utilizzo dello stack basato sulle linked list!
#include "listStack.h"
#include <iostream>

using std::cin; 
using std::cout; 
using std::endl;

int main(){
    cout<<"Utilizzo dello stack basato su liste!\n";
    
    Stack<int> st;
    int numero;

    cout<<"La dimensione dello stack ora è uguale a: "<<st.size()<<"\n";

    do{
        cout<<"Inserisci un elemento da mettere nello stack [0 - Per Terminare]\n";
        cin>>numero; 
        
        if(numero!=0){
            st.push(numero);
            cout<<"La dimensione dello stack è: "<<st.size()<<"\n";
        }

    }while (numero!=0);

    cout<<"La testa dello stack è: "<<st.top()<<"\n";

    cout<<"Elimino un elemento\n";
    st.pop(); 

    cout<<"La dimensione è: "<<st.size()<<"\n";
    cout<<"La testa dello stack ora è uguale a: "<<st.top()<<"\n";
    
    





}