#include <iostream>
#include "matrix.h"
#include <ctime>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;



int main(){

    //Definisco un doppio puntatore a double, per inizializzare il costruttore 3 che si trova sotto
    double **punto;
   
    punto=new double*[5];
   
    for(int i=0; i<5; i++){
        punto[i]=new double[7];
    }

    srand(static_cast<unsigned int>(time(0)));

    for(int i=0; i<5; i++){
        for(int j=0; j<7; j++){
            punto[i][j]=1+rand()%20;
        }
    }


    cout<<"Ti mostro cosa può fare la classe matrice!\n";

    cout<<"Uso dei vari costruttori!\n";

    //Definizione di una nuova matrice 
    Matrix m1; //Uso il costruttore di default 
    Matrix m2(3,6);//Uso del costruttore con colonne e righe
    Matrix m3(5,7, punto);//Uso del costruttore che fa uso del doppio costruttore!

    cout<<"Matrice con il costruttore di default: \n"<<m1<<"\n";
    cout<<"Matrice con il costruttore con colonne e righe: \n"<<m2;
    cout<<"Matrice con il costruttore 'completo':\n"<<m3;

    //Andiamo a vedere il funzionamento del costruttore di copia!
    Matrix m4{m3};
    cout<<"Ho usato il costruttore copia per inizializzare una matrice m4, con i valori di m3\n";
    cout<<"Il valore di m4 è:\n"<<m4;

    cout<<"-----------------------------------"<<endl;

    cout<<"Uso della funzione di modifica e di riempimento!\n";
    cout<<"Vado a modficare i valori di m3:\n"<<m3;

    m3.modifica(4,3).riempimento(30);

    cout<<"Il valore di m3, modificato e riempito è uguale a:\n"<<m3;

    cout<<"-----------------------------------"<<endl;

    //Uso delle varie operazioni!

    m1.modifica(4,3).riempimento(10);
    cout<<"Valori di m1:\n"<<m1;

    m2.modifica(4,3).riempimento(20);
    cout<<"Valori di m2:\n"<<m2;

    cout<<"Pongo m2+=m1\n";

    m2+=m1;

    cout<<"Il valore di m2 è ora:\n"<<m2;

    cout<<"//////////////////////////////////"<<endl;

    m3.modifica(4,3).riempimento(30);
    cout<<"Valori di m3:\n"<<m3;

    cout<<"Pongo  m3-=m1\n";

    m3-=m1;

    cout<<"Il valore di m3 è:\n"<<m3;

    cout<<"/////////////////////////////////"<<endl;

    cout<<"Definisco una nuova matrice m5\n";
    cout<<"Mostro m2:\n"<<m2;
    cout<<"Mostro m3:\n"<<m3;

    Matrix m5;

    m5=m2+m3;

    cout<<"Vedo che m5=m3+m2:\n"<<m5;

    cout<<"/////////////////////////////////"<<endl;

    cout<<"Sovrascrivo il valore di m4\n";
    cout<<"Mostro m2:\n"<<m2;
    cout<<"Mostro m3:\n"<<m3;

    m4=m3-m2;

    cout<<"Vedo che ora m4=m3-m2:\n"<<m4;

    cout<<"--------------------------------"<<endl;

    //Utilizzo del prodotto tra le matrici!

    cout<<"Modifico i valori di m1 e m2 per andare a svolgere il prodotto tra le matrici\n";

    m1.modifica(3,5).riempimento(30);
    m2.modifica(5,2).riempimento(30);

    cout<<"Ti mostro m1:\n"<<m1;
    cout<<"Ti mostro m2:\n"<<m2;

    m3=m1*m2;

    cout<<"Vedo che m3=m1*m2\n"<<m3;

    cout<<"Modifica del valore di m2\n";

    m2*=m3;

    cout<<"Il valore di m2 ora è:\n"<<m2;

}