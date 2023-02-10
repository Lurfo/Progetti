#include "poli.h"
#include <sstream>
#include <iostream>

//Specifica dei 3 costruttori!
//Se non diamo specifiche, oviamente possiamo andare a definire il fatto che il polinomio sia del tipo p(x)=0.0
Pol::Pol(): size{1}, coefs{new double[size]}{
    coefs[0]=0.0;
}

//Se mandiamo un elemento, sarà l'unico elemento contnuto nel polinomio 
Pol::Pol(double el): size{1}, coefs{new double[size]}{
    coefs[0]=el;
}

//Tero costruttore, inviamo anche un array che contiene i coefficienti
Pol::Pol(double element[], int numero): size{numero}, coefs{new double [size]}{
    //Ciclo che serve per salvare gli elementi all'interno del data memeber che contiene i coefficienti!
    for(int i=0; i<size; i++){
        coefs[i]=element[i];
    }
}

//Specifica del costruttore copia del nostro polinomio
Pol::Pol(const Pol& copio): 
//Copio la dimensione del primo e istanzio un array di coefficienti che ha la stessa dimesione
size{copio.size}, coefs{new double[size]}{

    //Copiamo i valori dei coefficienti del primo all'interno del secondo!
    for(int i=0; i<size; i++){
        coefs[i]=copio.coefs[i];
    }

}

Pol::~Pol(){
    delete [] coefs;
}

Pol& Pol::operator=(const Pol& conf){
    //Come prima cosa andiamo a confrontare l'indirizzo di memoria, in modo che, se essi sono uguali, ci risparmiamo di effettuare ulteriori operazioni

    if(this==&conf){
        return *this;
    }

    //Se i due elementi non sono uguali, ovviamente dobbiamo effettuare le opportine operazioni per poter eliminare il primo elemento e sovrascriverlo!
    else{
        delete[] coefs;
        size=conf.size;
        coefs=new double[size];

        for(int i=0; i<size; i++){
            coefs[i]=conf.coefs[i];
        }

        return *this;

    }



}

//In questo modo andiamo a definire l'operatore += tra due polinomi
Pol& Pol::operator+=(const Pol& p2){
    for(int i=0; i<size; i++){
        coefs[i]+=p2.coefs[i];
    }

    return *this;
}

//Specifica dell'operaotre *=
Pol& Pol::operator*=(double fact){
    for(int i=0; i<size; i++){
        coefs[i]*=fact;
    }

    return *this;
}

//Definizione dell'operatore che permette il prodotto tra due polinomi, quello su cui andiamo poi anche a basare la funzione *
Pol& Pol::operator*=(const Pol& p2){
    //Definiamo, come prima cosa il grado del polinomio risultante!, In base alla formuala matematica esso è uguale a quest'ultimo
    int newsize{(size+p2.size)-1};

    //Definiziamo quindi un array che ha come obiettivo quello di contenere tutti i coefficienti del "nuvovo" polinomio
    double conservo[newsize]{};

    //Ora, il prodotto tra polinomi corrisponde a moltiplicare tutti i termini del primo con tutti i termini del secondo
    //Tramite questi due cicli for possiamoandare a scorrere tutti gli elementi del primo e tutti gli elementi del secondo!
    for(int i=0; i<p2.size; i++){
        for(int j=0; j<size; j++){
            //Andiamo quindi a salvare all'interno del nuovo array tali prodotti
            //NOTA BENE LA POSIZIONE
            //Ovviamente nel prodotto tra polinomi anche il grado delle incognite varia, così facendo possiamo quindi andare a sfruttare una 
            //Proprietà delle potenze, andando quindi a sommare gli esponenti--> che corrispondono proprio ad i+j!
            //La presenza del += è utile prorprio perchè, se già abbiamo un coefficiente, ad esempio, per il termine di secondo grado, lo andiamo
            //Direttamente a sommare con esso!
            conservo[i+j]+=p2.coefs[i]*coefs[j];
        }
    }


    //Dopo aver svolto il prodotto tra i due polinomi, pichè la funzione che stiamo analizzando è quella +=, dobbiamo sovrascricere il primo polinomio
    //Eliminiamo i dati che esso contiene e li sostituiamo con quelli che abbiam ottenuto!
    delete[] coefs;
    size=newsize;
    coefs=new double[size];

    for(int i=0; i<size; i++){
        coefs[i]=conservo[i];
    }

    return *this;



}

//SPECIFICA DELLE FUNZIONI NON-MEMBER 
Pol operator*(const Pol& p, double fact){
    Pol nuovo{p};

    nuovo*=fact;

    return nuovo;
}

Pol operator*(double fact, const Pol& p){
    Pol nuovo{p};

    nuovo*=fact;

    return nuovo;
}

Pol operator+(const Pol& p1, const Pol& p2){
    Pol nuovo{p1};

    nuovo+=p2;

    return nuovo;

}






//Funzione che abbiamo eliminato poichè definito una funzione friend che ha lo stesso funzionamento, in questo modo si è condensato il funzionamento 
//all'interno di una sola funzione!
/*void Pol::trasformo(std::ostream& ouput){

        for(int i=size-1; i>0; i--){
            ouput<<coefs[i]<<"x^"<<i<<"+";
        }

        ouput<<coefs[0];

}*/

