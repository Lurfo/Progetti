#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int fibonacci(int);

int main(){
    int pos;
    cout<<"Ti posso dire un qualsiasi numero della sequenza di fibonacci, basta solo dirmi la posizione\n";
    cin>>pos;

   cout<<"Alla posizione che mi hai detto, corrisponde il numero: "<<fibonacci(pos)<<endl;

}

int fibonacci(int n){
    if(n==0 or n==1)
        return n;

    else {
        int n_uno=1, n_due=0, tmp;
       
        for(int i=2;i<=n; i++ ){
            tmp=n_uno;
            n_uno+=n_due;
            n_due=tmp;

        }

        return n_uno;

    }

}
