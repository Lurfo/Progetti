#include <iostream>

#include <ctime>
#include <cstdlib>

using std::cout;
using std::cin; 
using std::endl;

int main(){
    int array[10];
    srand(static_cast<unsigned int>(time(0)));


    cout<<"inserisci i numeri\n";

    for(int i=0; i<10; i++){
        array[i]=1+rand()%1000;
    }

    cout<<"Hai inserito i numeri:\n";

    for(int i=0; i<10; i++){
        cout<<array[i]<<"; ";
    }

    cout<<endl;

    cout<<"Sistemo in ordine crescente"<<endl;

    for(int j=0; j<10; j++){
        int key=array[j];
        int i=j;

        while(i>0 && array[i-1]>key){
            array[i]=array[i-1];
            i--;
        }
        array[i]=key;
    }


    cout<<"Hai inserito i numeri:\n";

    for(int i=0; i<10; i++){
        cout<<array[i]<<"; ";
    }

    cout<<endl;
}