//Specifica di tutte le funzioni membro della classe 
#include<iostream>
#include <string>
#include "matrix.h"
#include <ctime>
#include <cstdlib>
#include <exception>



//Nel caso in cui non venga specificato differentemente, allora si ha che il valore della matrice che andiamo ad inserire è uno zero
Matrix::Matrix():
raw{1}, col{1}, mat{new double* [raw]}{
    mat[0]=new double[col];
    mat[0][0]=0;
}

//Definizione del costruttore che contiene solo il numero di righe e di colonne
//Passando solo righe e colonne andiamo a definire un costruttore che inizializza la matrice a zero!
Matrix::Matrix(int r, int c): 
raw{r}, col{c}, mat{new double*[raw]}{
  
    for(int i=0; i<raw; i++){
        mat[i]=new double[col];

    }

    for(int i=0; i<raw; i++){
        for(int j=0; j<col; j++){
            mat[i][j]=0;
        }
    }
}

Matrix::Matrix(int r, int c, double**valors):
raw{r}, col{c}, mat{new double* [raw]}{
    for(int i=0; i<raw; i++){
        mat[i]=new double[col];
    }

    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            mat[i][j]=valors[i][j];
        }
    }
}

//Definizione del costruttore di copia!
Matrix::Matrix(const Matrix& sec): 
raw{sec.raw}, col{sec.col}, mat{new double*[raw]}{
    
    for(int i=0; i<raw; i++){
        mat[i]=new double[col];
    }

    for(int i=0; i<raw; i++){
        for(int j=0; j<col; j++){
            mat[i][j]=sec.mat[i][j];
        }
    }

    

}

//Con il distruttore, dobbiamo anch eliminare ogni elemento che è contenuto negli array riga, quindi per fare ciò andiamo 
//a utilizzare un ciclo for
Matrix::~Matrix(){
    std::cout<<"Eliminazione della matrice\n";

    for(int i=0; i<raw; i++){
        delete[] mat[i];
    }

    delete[] mat;
    
}

//Specifica della funzione di riempimento!
Matrix& Matrix::riempimento(int numero){
    std::cout<<"Riempio la matrice con numeri casuali da 1 a "<<numero<<"\n";
    std::cout<<"Nuove righe: "<<raw<<"\n";
    std::cout<<"colonne: "<<col<<"\n";

    srand(static_cast<unsigned int>(time(0)));

    for(int i=0; i<raw; i++){
        for(int j=0; j<col; j++){
            mat[i][j]=1+rand()%numero;
        }
    }

    return *this;
}

Matrix& Matrix::modifica(int r, int c){

    for(int i=0; i<raw; i++){
      
       delete[] mat[i];
    
    }

    delete[] mat;

    raw=r;
    col=c;

    mat= new double*[raw];

    for(int i=0; i<raw; i++){
        mat[i]=new double[col];
    }
    
    return *this;

}


Matrix& Matrix::operator=(const Matrix& sec){
   //Per l'operazione di copia dobbiamo prima andare ad eliminare gli elementi che sono contenuti all'interno della matrice!
   for(int i=0; i<raw; i++) 
        delete[] mat[i];

    delete[] mat;

    //Andiamo quindi a sovrascrivere tutti i dati che sono contenuti nella prima all'interno della seconda
    raw=sec.raw;
    col=sec.col;

    mat=new double* [raw];

    for(int i=0; i<raw; i++){
        mat[i]= new double[col];
    }

    //Andiamo quindi ad inserire all'interno della matrice tutta gli elementi della seconda matrice!
    for(int i=0; i<raw; i++){
        for(int j=0; j<col; j++){
            mat[i][j]=sec.mat[i][j];
        }
    }

    return *this;

}

Matrix& Matrix::operator+=(const Matrix& conf){

    //Andiamo a controllare se il numero di colonne e di righe di tutte e due le matrici è uguale, altirmenti la somma non può essere effettuata
    if(controllosomma(*this, conf)){
        for(int i=0; i<raw; i++){
            for(int j=0; j<col; j++){
                mat[i][j]+=conf.mat[i][j];
            }
        }
    }

    else 
        throw std::invalid_argument("Guarda che così non va, perchè le due matrici non hanno righe e colonne uguali");

    return *this;

}

Matrix& Matrix::operator-=(const Matrix& conf){
    

    if(controllosomma(*this, conf)){
        for(int i=0; i<raw; i++){
            for(int j=0; j<col; j++){
                mat[i][j]-=conf.mat[i][j];
            }
        }
    }

    else
        throw std::invalid_argument("Guarda che così non va, perchè le due matrici non hanno righe e colonne uguali");

    return *this;

}

Matrix& Matrix::operator*=(const Matrix& prd){

   if(controlloprod(*this, prd)){

       Matrix mantengo(raw, prd.col);

        for(int i=0; i<raw; i++){

            for(int j=0; j<prd.col; j++){

                int c=0;
                int r=0;
                int somma=0;

                while(c<col && r<prd.raw){
                    somma+=mat[i][c]*prd.mat[r][j];
                    c++;
                    r++;
                }

                mantengo.mat[i][j]=somma;                

            }
        }

        *this=mantengo;

        return *this;
    
     }

    else 
        throw std::invalid_argument("Guarda che così il prodotto non si fa!"); 

  
}


std::ostream& operator<<(std::ostream& out, const Matrix& mat){
    
    for(int i=0; i<mat.raw; i++){
        for(int j=0; j<mat.col; j++){
            out<<mat.mat[i][j]<<", ";
        }

        out<<"\n";
    }

    return out;

}

bool controllosomma(const Matrix& prima, const Matrix& seconda){
    if(prima.raw==seconda.raw && prima.col==seconda.col){
        return true;
    }

    else 
        return false;
}

bool controlloprod(const Matrix& prima, const Matrix& seconda){
    if(prima.col==seconda.raw){
        return true;
    }

    else 
        return false;
}

//Nell'operazione di somma andiamo a sfruttare l'operatore che già abbiamo definito!
Matrix operator+(const Matrix& uno, const Matrix& due){

    Matrix tengo{uno};

    tengo+=due;

    return tengo;
}

//Anche nell'operazione di sottrazione andiamo a sfruttare l'operazione che abbiamo definito prima!
Matrix operator-(const Matrix& uno, const Matrix& due){

    Matrix tengo{uno};

    tengo-=due;

    return tengo;
}

//Specifica dell'operatore prodotto!
Matrix operator*(const Matrix& primo, const Matrix& secondo){

    Matrix nuovo{primo};

    nuovo*=secondo;

    return nuovo;
}

