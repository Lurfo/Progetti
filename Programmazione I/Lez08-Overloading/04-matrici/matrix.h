//Andiamo a definire una classe che serve per esprimere una matrice!
#include <iostream>

#ifndef MATRIX_H
#define MATRIX_H

class Matrix{

    friend std::ostream& operator<<(std::ostream&, const Matrix&);
    friend bool controllosomma(const Matrix&, const Matrix&);
    friend bool controlloprod(const Matrix&, const Matrix&);

    //Come dati privati andiamo ad inserire, il numero di righe, e il numero di colonne della matrice
    //Oltre che la matrice stessa!
    private: 
        int raw;
        int col;
        //Andiamo a definire la matrice come un puntatore a puntatori!
        //Stiamo cioè definendo la matrice come un insieme di array, uguali al numero di righe, che punta ad array che hanno dimensione uguale a quella 
        //delle colonne
        /*In altre parole essa si rappresenta: 
       (puntatore che rappresenta la prima riga) [a1]-->[...c...] (vettore che contiene gli elementi della riga 1)
                                                 [a2]-->[...c...]
                                                 [a3]-->[...c...]
        */
        double **mat;

    public: 
        //definisco il costruttore della matrice
        Matrix();//Default
        Matrix(double);//Un unico valore
        Matrix(int, int);
        Matrix(int, int,double**);//Passaggio di righe, colonne e insieme di elementi
        Matrix(const Matrix&);//Costruttore copia!

        //Anidamo, anche a definire il distruttore; 
        ~Matrix();

        //Definizione dell'operazione di riempimento!
        Matrix& riempimento(int);

        Matrix& modifica(int, int);

        //Dopo la definizione del costruttore, andiamo anche a definire l'operazioni di cui ho bisogno
        //Definiamo l'operazion =
        Matrix& operator=(const Matrix&);

        //Definizione dell'operazione +=
        Matrix& operator+=(const Matrix&);

        //Definizione dell'operatore -= (Simile alla somma)
        Matrix& operator-=(const Matrix&);

        //Definizione dell'operazione di prodotto tra due matrici!
        Matrix& operator *=(const Matrix&);

        
        
    





};


//Definizione dell'operaotre somma tra le due matrici
Matrix operator+(const Matrix&, const Matrix&);
//Definizione della sottrazione tra le due matrici!
Matrix operator-(const Matrix&, const Matrix&);
//Definizione dell'operazione prodotto tra due matrici
Matrix operator*(const Matrix&, const Matrix&);


















#endif