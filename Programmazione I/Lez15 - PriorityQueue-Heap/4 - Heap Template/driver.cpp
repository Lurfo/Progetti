#include <iostream>
#include "heap.h"

using std::cout; 
using std::cin; 
using std::endl;

int main(){
    Heap<int> pro;
    
    int num;

    for(int i=1; i<=pro.sizeArr(); i++){
        cout<<"Dimmi elemento!\n";
            cin>>num;
        
        pro.insertHeap(num);

    }

    
    
    for(int i=1; i<=pro.sizeArr(); i++){
        cout<<pro.heapMaxEstract()<<((i!=pro.sizeArr()) ? ", " : "\n");
    }

}