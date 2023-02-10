#include <iostream>
#include <queue>

using std::cout; 
using std::cin; 
using std::endl; 
using std::priority_queue; 

int main(){
    priority_queue<int> elm; 
    int num;
    do{
        cout<<"Dimmi - 0 Termino\n"; 
            cin>>num; 

        if(num!=0){
            elm.push(num);
        }
    }while(num!=0);

    while(!elm.empty()){
        cout<<elm.top()<<" ";
        elm.pop();
    }

    cout<<endl;
    
}