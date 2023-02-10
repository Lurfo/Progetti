#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main(){
    cout<<"Ti mostro la sequenza di fibonacci\n";
   
    int i{0};
    int fib[100];

     while(true){
        
         if(i==0){
            
            fib[0]=1;
            cout<<fib[0]<<" ";
         }

         else if(i==1){
             fib[1]=1;
            cout<<fib[i]<<" ";
         }

         else{
            fib[i]=fib[i-1]+fib[i-2];
            cout<<fib[i]<<" ";
         }

        i++;

}
    cout<<endl;

}