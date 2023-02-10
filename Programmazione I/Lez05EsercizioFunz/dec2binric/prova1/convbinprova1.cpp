#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void conversion (int num);

int main(){
    int num{0};
    cout<<"Dimmi il numero che vuoi convertire in binario\n";
    cin>>num;


    conversion(num);
    
    cout<<endl;

}

void conversion(int num){
    if(num==0){
        cout<<"0";
        return;
    }

    else{
        conversion(num/2);
        cout<<num%2;
    } 

}