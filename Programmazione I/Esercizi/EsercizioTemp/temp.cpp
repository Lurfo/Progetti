#include <iostream>

using std::cout;
using std::cin;
using std::endl;

float calcf(float a){
    float v=a;
    float t;

    t=(v*9/5)+32;

    return t;


}

float calcc(float a){
    float v=a;
    float t;

    t=(v-32)*5/9;

    return t;
}

int main(){
    float v, t;
    char s;

    cout<<"Dimmi il valore della temperatura: ";
        cin>>v;
    cout<<"Ora dimmi la scala (c=Celsius o f=Fahrenheit): ";
        cin>>s;

    if(s=='c'){

         t=calcf(v);

        cout<<"La termperatura in Fahrenheit è uguale a: "<<t<<endl;
    }

    else if(s=='f'){
        t=calcc(v);

        cout<<"La temperatura in Celsius è uguale a:"<<t<<endl;
    }



}