#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void provoStatic(){

    //Generando una variabile di tipo static all'interno della funzione, il valore che è allocato quando questa viene chiama NON VIENE DEALLOCATO
    //QUANDO LA FUNZIONE RESTITUISCE IL CONTROLLO AL MAIN, MA CONTINUA AD ESISTERE ALL'INTERNO DELLA MEMORIA!!!
    //In questo modo, ogni volta che questa viene chiamata può accedere allo stesso valore che aveva precedentemente!!!
    //Notiamo infatti che quando parte il programma, il valore di i dichiarato all'interno di questa funzione esterna viene incrementato ogni volta
    //che essa viene chiamata tramite il ciclo while del main!!!
    static int i{1};
    cout<<i<<endl;
    i++;
    return;
}

int main(){

    int i{0};

    while(1){
        
        provoStatic();
    
    i++;

    }
}