//Andiamo a generare un array multidimensionale, in questo caso abbiamo sia colonne che righe
#include <iostream>
#include <array>

#include <ctime>
#include <cstdlib>



//Andiamo a dichiarare come variabile globale sia righe che colonne i modo da poterle modificarle molto semplicemente
const size_t raws{3};
const size_t col{4};

using std::array;
using std::cin;
using std::cout;
using std::endl;

void mostro(const array< array<int, col>, raws>&);

void ins(array< array<int, col>, raws>&);

int main(){
    //In questo modo andiamo a dichiarare un array multidimensionale
    //Il primo valore indica le colonne e il secondo indica le righe
    array< array<int, col >, raws> tab{};


    cout<<"Ti mostro il valore dell'array\n";
    
        mostro(tab);

    cout<<"Inseriamo i valori del nostro array\n";
        
        ins(tab);

    cout<<"Ti mostro la tabella completa\n";

        mostro(tab);


}

void mostro(const array< array<int, col>, raws>& tab){

    //Come vediamo, per mostrare il doppo arrai tramite il range based, dobbiamo dichiarare questo tipo di variabile auto const!
    //Questo for serve per scorrere le varie righe dell'array complesso
    for(auto const& rows: tab ){

        //Il secondo for serve per andare a scorrere le varie colonne della tabella!!!
        for(auto const& col: rows){
            cout<<col<<", ";
        }

        cout<<endl;
    }
}

void ins(array< array<int, col>, raws>& tab){

    srand(static_cast<unsigned int>(time(0)));

    for(auto& raws: tab){
        for(auto& col: raws){
            col=1+rand()%100;
        }
    }
}


