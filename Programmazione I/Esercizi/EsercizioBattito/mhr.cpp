#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void calcbatt(int a,int v[]){
    int au=a; 

    v[0]= 220-au;
    v[1]= 208-(0.7*au);
    v[2]= 207 -(0.7*au);
    v[3]=211-(0.64*au);

    return;

}

void calcolomaxmin(int* max, int* min, int v[]){
        int i=0;

        while(i!=4){
            if(i==0 || v[i]>*max){
                *max=v[i];
            }
           if(i==0 || v[i]<*min ){
               *min=v[i];
           }

           i++;
        }

        return;

}


int main(){
    int au, v[4];

    cout<<"Dimmi la tua età che ti spiego"<<endl;
        cin>>au;

    calcbatt(au,v);

    cout<<"Secondo uno studio, dovresti avere un MHR uguale a:"<<endl;

    int i=0;

    while(i!=4){

        cout<<v[i]<<", ";

        i++;
    }
    
    cout<<"questi valori"<<endl;

    int max, min;

    calcolomaxmin(&max, &min, v);

    cout<<"Dovresti avere un valore compreso tra: "<<max<<" e "<<min<<endl;


}