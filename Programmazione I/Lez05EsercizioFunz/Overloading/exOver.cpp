//Facciamo un esempio del FUNCTION OVERLOADING 
#include<iostream>
using std::cout;
using std::cin; 
using std::endl;

//Abbiamo usato lo stesso nome per due funzioni che trattano tipi di dati differenti, qui entra in gioco il function overloading!
//Il compilatore, controlla tutta la signature della funzione, compreso dunque anche il tipo di parametro che inviamo ad essa 
//conseguentemente sceglie di utilizzare la funzione che va in accordo con i parametri che gli abbiamo inviato!
int square(int& x);
double square(double& y);

int main(){
    int x;
    double y;

    cout<<"Inserisi un intero\n";
    cin>>x; 

    //Gli abbiamo passato il valore intero, di conseguenza abbiamo che il compilatore sceglie la funzione che restituisce l'intero!
    cout<<"Il quadrato del numero inserito è: "<<square(x)<<endl;

    cout<<"Inserisci un razionale\n";
    cin>>y;

    //Gli abbiamo passato il valore razionale, dunqe il compilatore "sceglie" la funzione che restituisce lo stesso tipo di valore!
    cout<<"Il quadrato del numero inserito è: "<<square(y)<<endl;
}

int square(int& x){
    return x*x;
}


double square(double& y){
    return y*y;
}