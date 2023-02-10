//Andiamo quindi a scrivere l'implementazione delle funzioni in base a quello che ci occorre!
#include "tris.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

//Andiamo ad impostare il costruttore
//Il costruttore iniziale non deve fare altro che andare ad impostare degli spazi vuoti all'interno dell'array!
Tris::Tris(){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            tab[i][j]=' ';
        }
    }
}

Tris::~Tris(){
    std::cout<<"La partita è finita, è stato molto bello!\n";
}


//Vado ad impostare la funzione che ha il compito di mostrare a video la tabella!
void Tris::vedo() const{
    //Stampiano il numero delle colonne della tabella
    std::cout<<"   0   1   2\n\n";
    for(int i=0; i<3; i++){
        
        //Andiamo a stampare il numero della riga
        std::cout<<i;

        for(int j=0; j<3; j++){

            //Andiamo a stampare il valore contenuto in quella casella
            std::cout<<std::setw(3)<<tab[i][j];

            if(j!=2){
                //Andiamo a stampare un divisore tra un valore e l'altro, solo se non siamo nell'ultima colonne
               std::cout<<"|";
            }

             if(i!=2){
                 //Stampiamo poin un divisore tra una riga e l'altra, solo quando non siamo nell'ultima riga!
             //  std::cout<<"\n____|____|____\n    |    |    \n";
        }

        
        }

        std::cout<<"\n\n";

    }
}

//Andiamo a dichiarare la funzione che ha lo scopo di definire la valitidà della mossa inserita!
//Riceve come valori in ingresso il numero di righe e quello di colonne
bool Tris::validateMove(int i, int j) const{

    //Come valore di ritorno andiamo a definire una serie di operazioni logiche
    return i>=0 && i<3 && j>=0 && j<3 && tab[i][j]==' ';
    //Tramite questa serie di espressioni logiche possiamo trovare se la mossa è valida o meno

}

//Andiamo a verificare che non ci sia già un tris di elemeti all'interno della tabella!
Tris::Status Tris::gameSet() {
    //Come prima cosa andiamo a controllare le diagonali 
    //Controlliamo la diagonale superiore
    if(tab[0][0]!=' '&& tab[0][0]==tab[1][1] && tab[0][0]==tab[2][2]){
        return WIN; 
    }

    //Controlliamo la diagonale inferiore

    else if(tab[0][2]!=' ' && tab[0][2]==tab[1][1] && tab[0][2]==tab[2][0]){
        return WIN;
    }

    //Andiamo quindi a controllare le righe!
    for(int a=0; a<3; a++){
        if(tab[a][0]!=' ' && tab[a][0]==tab[a][1] && tab[a][0]==tab[a][2])
            return WIN;
    }

    //Andiamo a controllare le colonne

    for(int a=0; a<3; a++){
        if(tab[0][a]!=' ' && tab[0][a]==tab[1][a] && tab[0][a]==tab[2][a])
            return WIN;
    }

    //Se nessuna delle condizioni precedenti è stata verifica allora è possibile che o la partita debba continuare o sia finita in pareggio!
    //Andiamo a verificare la prima!

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(tab[i][j]==' '){
                return CONTINUE;
            }
        }
    }

    //Abbiamo quindi verificato se all'interno della nostra tabella è ancora disponibile qualche spazio vuoto che non è stato riempito!

    //Se neanche questa condizione è verificata, vuol dire che la partita è finita in partià 
    return DRAW;

}

//Andiamo ad impostare la funzione che ha i

bool Tris::xoMove(char m){
    int i, j;

    srand(static_cast<unsigned int>(time(0)));
    if(m=='x'){
        do{

            std::cout<<m<<", Dove devo metterlo?\n";
            std::cin>>i>>j;
            std::cout<<"\n";

        }while(!validateMove(i,j));
    }

    else{

        do{

            std::cout<<m<<" Faccio la mia mossa!\n";
            i=rand()%3;
            j=rand()%3;

        }while(!validateMove(i,j));




    }

    //vado ad inseriee la mossa all'interno della tabella
    tab[i][j]=m;
    //Andiamo quindi a stampare la tabella
    vedo();

    //Imposto la variabile di stato della partita
    Status gameStatus=gameSet();

    if(gameStatus==WIN){
        std::cout<<"Complimenti, ha vinto il giocatore: "<<m<<"\n";
        return true;
    }

    else if(gameStatus==DRAW){
        std::cout<<"La partita è finita in parità\n";
        return true;
    }

    else{//Questo è il valore che fa continuare il valore della partità!
        return false;
    }



}

//Andiamo a dichiarare la funzione che il compito di impostare la mossa!

void Tris::makeMove(){

    vedo();

    while(true){

        if(xoMove('x')){
            break;
        }

        else if(xoMove('y')){
            break;
        }
    }

}