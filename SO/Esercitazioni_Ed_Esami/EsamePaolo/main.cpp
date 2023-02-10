#include <iostream>
#include <fstream>
#include "header.h"

using std::cout;
using std::cin; 
using std::endl; 
using std::ifstream; 
using std::ios;




int main(){

    int r,c;

    int **matrix;

    ifstream file;

    file.open("dati31.txt", ios::in);

    if(!file){
        cout<<"ERRORE FILE NON APERTO\n"<<endl;
        exit(1);
    }

    file>>r>>c;

    cout<<"Righe: "<<r<<" Colonne: "<<c<<endl;

    matrix = new int *[r]; 

    for(int i=0; i<r; i++){
        matrix[i]= new int[c];
    }

    //Inizializzo la matrice
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            matrix[i][j]=0;
        }
    }


    //Vedo matrice inizializzata
   vedoMatrice(matrix, r, c);


    //ingresso della matrice
    recuperoValori(file, matrix, r, c);


    //Vedo i valori della matrice
    vedoMatrice(matrix, r, c);



    verificaContenuto(matrix, r, c);


    int scelta, val;

    cout<<"Converto una riga a tua scelta in un numero decimale, dimmi il valore della riga: \n";
        cin>>scelta;


    
    val = conversioneBinarioDec(matrix, scelta, c);

    cout<<"Valore convertito: "<<val<<endl;


    int vettore[r];

    sommaTotale(matrix, r, c, vettore);

    cout<<"Mostro il vettore convertito\n";
    
    for(int i=0; i<r; i++){
        cout<<vettore[i]<<", ";
    }

        cout<<endl;


    file.close();


}