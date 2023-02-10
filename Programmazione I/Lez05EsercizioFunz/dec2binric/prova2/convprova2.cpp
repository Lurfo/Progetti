#include <iostream>
#include <array>

using std::cout; 
using std::cin;
using std::endl;

int conversion(int);

int main(){
    int num;

    cout<<"Dimmi il numero da convertire\n";
    cin>>num;

    cout<<"Il numero convertito è uguale a: "<<conversion(num)<<". "<<endl; 
}

int conversion(int num){
    
    if(num==0){
        return 0;
        
    }

    else{
        return(num%2+10*conversion(num/2));
    }



}