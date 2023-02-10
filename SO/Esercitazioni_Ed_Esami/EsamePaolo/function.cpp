#include "header.h"
#include <iostream>


void recuperoValori(std::ifstream& file, int **matrice, int r, int c){
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            file>>matrice[i][j];
        }
    }
}
void vedoMatrice(int **matrice, int r, int c){

    std::cout<<"-----------------------------------------------------------"<<std::endl;

    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            std::cout<<matrice[i][j]<<" ";
        }
        
        std::cout<<std::endl;
    }

    std::cout<<"-------------------------------------------------------"<<std::endl;
}
void verificaContenuto(int **matrice, int r, int c){

    bool diverso;

    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            
            if(matrice[i][j]!=0  && matrice[i][j]!=1){
                diverso = true;
                break;
            }

        }
    }

    if(diverso){
        std::cout<<"La matrice contiene un numero diverso da 1 o 0\n"<<std::endl;
    }

    else{
        std::cout<<"La matrice contiene solo 0 o 1"<<std::endl;
    }

}


int conversioneBinarioDec(int **matrice, int r, int c){
  

    int num=0;

    int val = 7;

    for(int i=0; i<c; i++){
        num += matrice[r][i]*potenzaDue(val);
        val--;
    }

    return num;



}

int potenzaDue(int exp){

    int val=1;

    if(exp==0){
        return 1;
    }

    if(exp==1){
        return 2;
    }

    else{

        for(int  i=1; i<=exp; i++){
            val = 2*val;
        }
    }


    return val;

}


void sommaTotale(int **matrice, int r, int c, int *vettore){
    
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            vettore[i]=conversioneBinarioDec(matrice, i, c);
        }
    }

}