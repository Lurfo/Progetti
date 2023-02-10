#include <iostream>
#include "priorityQueue.h"

using std::cout;
using std::cin; 
using std::endl; 

int main(){
    PriorityQueue<int> pq; 
    int num;
    do{
        cout<<"Dimmi il numero che devo inserire!\n";
            cin>>num; 
        
        if(num!=0){
            pq.Enqueue(num);
        }
    }while(num!=0);

    cout<<"La dimensione del vettore è: "<<pq.size()<<"\n";

    int salvo=pq.size();

    for(int i=1; i<=salvo; i++){
        cout<<pq.Dequeue()<<((i!=salvo)? ", ":"\n");
    }

    if(pq.empty()){
        cout<<"Ho rimosso tutti gli elementi dalla coda con priorità!\n";
    }

}