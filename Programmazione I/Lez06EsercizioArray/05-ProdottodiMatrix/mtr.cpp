#include <iostream>
#include <array>

#include <ctime>
#include <cstdlib>



using std::cout;
using std::cin;
using std::endl;
using std::array;

int i=1;

template<typename sost>
void riemp(sost& matrc){

   srand(i);
       i++;


    for(auto& raws: matrc ){
        for(auto& col: raws){
            col=1+rand()%10;
        }
    }

    return;
}

template<typename sost>
void vedo(sost& matrc ){
    for(auto& raws: matrc){
        for(auto& col: raws){
            cout<<col<<"; ";
        }
        cout<<endl;
    }

    return;
}

void prodo(array<array<int, 3>, 4>& a, array<array<int, 4>, 3>& b,  array<array<int, 4>, 4>& p ){
    int r=0;
    int c=0;
    int d=0;

    for(int i=0; i<4; i++){
        
         int d=0;

        for(int k=0; k<4; k++){
           
            int c=0;
            int sommavett=0;

            while(c<3){
                sommavett+=a[r][c]*b[c][d];
                c++;
            }

            p[i][k]=sommavett;

            d++;
            
        }

        r++;
        

    }

    return;

}

    


int main(){

    array<array<int, 3>, 4> a;
    array<array<int, 4>, 3> b;

    cout<<"Vado a riempire le due matrici!\n";

        riemp(a);

    cout<<"Riempio la seconda!\n";

    riemp(b);

   cout<<"Ti faccio vedere i valori delle due matrici!\n";
   
    cout<<"Matrice A:\n ";
    vedo(a);

    cout<<"Matrice B:\n";
    vedo(b);

    cout<<"Effettuo il prodotto tra le matrci!!!\n";

    array<array<int, 4>, 4> c;

    cout<<"Riempio c\n";
     
    riemp(c);

    cout<<"Mostro c:\n";

    vedo(c);

    prodo(a, b, c);

    cout<<"Il risultato finale è: \n";
    vedo(c);

    
}