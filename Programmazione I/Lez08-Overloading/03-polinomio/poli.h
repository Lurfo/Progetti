#include <iostream>
#include <string>


#ifndef POLI_H
#define POLI_H

class Pol{

    //Definisco la funzione che ha il compito di prelevare la stringa del polinomio!
    //ATTENZIONE, per sovrascrivere l'operatore
    friend std::ostream& operator<<(std::ostream&, const Pol&);

    //Abbiamo due soli membri privati
    private:
        //Serve per definire il grado del polinomio
        int size;
        //Vettore usato per definire un array che contiene i coefficienti del polinomio
        double *coefs;

    public:
       
        //Troviamo 3 tipi di costruttori:
        //Costruttore di defaul, quanto andiamo non si specificano elementi        
        Pol();
        //Quando gli inviamo solo un interno! 
        explicit Pol(double);
        //Quando gli inviamo sia il numero di interi che i coefficienti
        Pol(double coeffic[], int numero);
        //NOTA: Esiste anche la possibilità di metterli tutti assieme all'interno del medesimo costruttore
        //ma tuttavia sarebbe molto più complesso da gestire! 
        //In questo modo si può gestire molto meglio!

        //Importante nella definiscione del nostro polinoimio è il costruttore copia!
        //Possiamo infatti inizializzare con gli stessi valori di un altro!
        //Come elemento per riferimento a questo costruttore, passiamo un altro polinomio
        Pol(const Pol&);

        //Dichiaro il distruttore
        ~Pol();//Molto importante in questo caso!
               //Poìchè abbiamo definito un oggetto che contiene un array, quindi dobbiamo eliminare tutta la memoria che esso contiene

        //Importante come terzo elemento all'interno della nostra classe è l'overload dell'operatore=
        Pol& operator=(const Pol&);

        //Definisco l'operatore "+="
        Pol& operator+=(const Pol&);

        //Definisco l'operatore per andare a  moltiplicare tutti i termini del polinomio per una costate
        Pol& operator*=(double);

        int grado(){return size-1;}

        Pol& operator*=(const Pol&);

};


//Possiamo anche andare a definire delle non-member function che implementano altri tipi di operatori utili per svolgere determinate funzioni
//Pol operator*(const Pol&, const Pol&);
Pol operator*(const Pol&, double);
Pol operator*(double, const Pol&);

Pol operator+(const Pol&, const Pol&);

#endif