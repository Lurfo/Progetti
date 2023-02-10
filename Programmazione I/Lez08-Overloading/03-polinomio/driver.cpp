#include "poli.h"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

std::ostream& operator<<(std::ostream&, const Pol&);


int main(){

    double coefs[5]{1,2,3,4,5};


    Pol p1(coefs, 5);
    
    cout<<"Ti faccio vedere il polinomio: \n";
    cout<<p1<<"\n";

    cout<<"-------------------------------"<<endl;

    //Vediamo il funzionamento del costruttore copia, dichiarando una nuova variabile ed inizializzandola con il polinomio che abbiamo definito sopra

    cout<<"Genero una nuova variabile che inizializzo con p1!\n";

    Pol p2{p1};

    cout<<"Dunque  ho che  p2: "<<p2<<"\n";

    cout<<"-------------------------------"<<endl; 

    //Funzionamento dell'operatore di assegnazion =

    cout<<"Genero un nuovo polinomio\n";

    double num[6]{1,6,7,8,9,2};

    Pol p3(num, 6);

    cout<<"Il polinomio che ho definito: "<<p3<<"\n";

    cout<<"Ora pongo che p2=p3\n";

    p2=p3;
    
    cout<<"Il valore modificato di p2 è uguale a: "<<p2<<"\n";

    //Con l'operatore uguale abbiamo quindi assegnato a p2 il valore di p3, ottenendo due polinomi completamente uguali!

    cout<<"-------------------------------"<<endl;

    //Procedo adando ad usare l'operatore += per sommare ad uno dei polinomi che ho definito un altro

    cout<<"Effettuo l'operazione p2+=p1\n";

    cout<<"Valore iniziali di p2: "<<p2<<"\n";
    cout<<"Valore di p1: "<<p1<<"\n";

    p2+=p1;

    cout<<"Il valore di p1 è quindi uguale a: "<<p2<<"\n";

    cout<<"--------------------------------"<<endl;

    double c1[]{0,1,1};
    double c2[]{0,1,1};

    Pol provo1(c1,3);
    Pol provo2{c2,3};

    cout<<provo1<<endl;
    cout<<provo2<<endl;

    provo2*=provo1;

    cout<<"Dopo moltiplicazione: \n";
    cout<<provo1<<endl;
    cout<<provo2<<endl;
    




}

std::ostream& operator<<(std::ostream& ouput, const Pol& p){
    
    for(int i=p.size-1; i>0; i--){
        ouput<<p.coefs[i]<<"x^"<<i<<"+";
    }

    ouput<<p.coefs[0];

    return ouput;
}