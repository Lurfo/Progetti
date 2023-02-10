#include <iostream>

using std::cout;
using std::endl;

int main(){    
    for(int i=1; i<=50000; i++){
      
        for(int j=1; j<=i; j++){
          
            for(int k=j; k<=i; k++){
               
                int latsqr{k*k+j*j};
                int iposqr{i*i};

                if(latsqr==iposqr){
                    cout<<"Terna: "<<j<<", "<<k<<", "<<i<<";";
                    cout<<endl;

                }
            }
        }
    }
}
