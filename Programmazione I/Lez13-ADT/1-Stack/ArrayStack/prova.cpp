//Vado a specificare un driver che ha il compito di andare a utilizzare lo stack basato su array che ho definito!
#include <iostream>

#include "arrayStack.h"

using std::cout; 
using std::cin; 
using std::endl;

int main(){
    //Dichiarazione dello stack
    Stack<int> st; 

    cout<<"Dimensione dello stack: "<<st.size()<<endl; 

    cout<<"Inserisco degli elementi!\n";

    st.push(12);
    st.push(245);
    st.push(9);
    st.push(3);

    cout<<"La dimensione ora è: "<<st.size()<<endl;
    cout<<"Il primo elemento dello stack è: "<<st.front()<<endl; 

    cout<<"Effettuo un pop\n";
    st.pop(); 
    cout<<"Il primo elemento dello stack ora è: "<<st.front()<<endl; 

    cout<<"Elimino tutti gli elementi dallo stack\n";

    st.pop();
    st.pop();
    st.pop();

    cout<<"La dimensione ora è: "<<st.size()<<endl;

    cout<<"Provo ad effettuare un nuovo pop\n";
    try{
    st.pop();
    }
    catch(std::runtime_error e){
        std::cerr<<e.what()<<endl;
    }

    cout<<"Ormai tutti gli elementi dello stack erano già fuori, quindi si genera un errore!\n";

    


}
