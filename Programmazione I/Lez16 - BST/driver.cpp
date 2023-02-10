#include "bst.h"
#include <iostream>

using std::cout; 
using std::cin; 
using std::endl; 

int main(){
    BST<int> prov; 
    int num; 

    do{
        cout<<"Dimmi il numero da inserire\n";
            cin>>num; 

        if(num!=0){
            prov.insert(num);
        }
    }while(num!=0);

    cout<<"Ti mostro gli elementi nell'albero usando la fuzione inOrder!\n";

    prov.inOrder();
    cout<<"\n";
}