#include <iostream>
using std::cout;
using std::endl;

int main(){
    
    //Per descrivere il primo triandolo;
    for(int i{1}; i<=10; ++i){
      
        for(int j=1; j<=i; ++j){
            cout<<"*";
        }
      
        cout<<"\n";
    }

    cout<<"\n";

    //Per descrivere il secondo triangolo
    for(int i=10; i>0; i--){
       
        for(int j=i; j>0; j--){
            cout<<"*";
        }

        cout<<"\n";
    }

    cout<<"\n";

    //Per descrivere il terzo triangolo
    for(int i=1; i<=10; i++){
        for(int k=1; k<i; k++){
            cout<<" ";
        }
        for(int j=10; j>i; j--){
            cout<<"*";
        }

        cout<<"\n";
    }

    cout<<"\n";

    //Per descrivere il quarto triangolo
    for(int i=1; i<=10; i++){
        for(int k=10; k>i; k--){
            cout<<" ";
        }
        for(int j=1; j<=i; j++){
            cout<<"*";
        }
        
        cout<<"\n";
    }


}