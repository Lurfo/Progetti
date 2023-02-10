#include <iostream>

using std::cout;
using std::endl;
using std::cin;

//Andiamo a dichiarare il prototype della funzione!
unsigned long int fibonacci(int);

int main(){

    cout<<"Primi "<<10<<" numeri della serie:\n";
    //Tramite il ciclo for andiamo a mostrare i vari numeri della successione di fibonacci!!
    //Abbiamo scelto, in questo caso, di mostrare i primi 10 numeri della serie di fibonacci!!!
    for(int k=0; k<=10; k++){
            //Abbiamo la chiamata a funzione che ci permette di calcolare i singoli valori della serie di fibonacci!!!
        cout<<fibonacci(k)<<", ";
    }


}

//Questa è la nostra funzione che ci permette di calcolare la successione di fibonacci

//Tuttavia la definizione di questa funzione ricorsiva, rispetto alla formula iterativa della funzione è molto svantaggiosa poichè si presenta il 
//SUBPROBLEM OVERLAPPING vale cioè a dire che, andiamo a risolvere molte più volte lo stesso problema

//Es: nel caso di fibonacci(3) andiamo a risolvere per 2 volte il problema fibonacci(1); 

//Questo è molto svantaggioso perchè, nel caso di numeri molto più grandi,andremo a risolvere un numero molto più elevato di volte gli stessi
//problemi, rendendo questo algoritmo molto svantaggioso!!!

//PER FIBONACCI È MOLTO VANTAGGIOSO USARE LA FUNZIONE ITERATIVA TRAMITE UN CICLO FOR O UN CICLO WHILE PIUTTOSTO CHE LA VARIANTE RICORSIVA
unsigned long int fibonacci(int numero){
  
    if(numero==1 || numero==0){
        return 1;
    }

    else 
        return fibonacci(numero-1)+fibonacci(numero-2);
}