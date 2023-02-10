#include "prestiti.h"
#include <sstream>
#include <iostream>

Data operator+(const Data& d, int g){

    Data nuovo=d;

    nuovo+=g;

    return nuovo;


}

void Prestato::setDataRestituzione(const Data& prestito){
    //Usando gli operatori della classe data posso andare ad impostare la data di restituzione 30 giorni dopo la data di prestito!
    restituzione=(prestito+30);
}

Prestato::Prestato():prestato{nullptr}, prestito{}, restituzione{}{}

Prestato::~Prestato(){}

void Prestato::setLibro(const Book& libro){
    prestato=&libro;
}

std::string Prestato::getLibro(){
    std::ostringstream out; 

    out<<"Id del libro: "<<prestato->getBook_id()<<"\n";
    out<<"Titolo del libro: "<<prestato->getTitle()<<"\n"; 
    out<<"Anno di pubblicazione: "<<prestato->getYear()<<"\n";
    out<<prestato->getAuthor();

    return out.str();

}

std::string Prestato::getTitolo(){
    return prestato->getTitle();
}

void Prestato::setPrestito(int g, int m, int a){
    prestito.setData(g, m, a);

    //A questo punto faccio in modo di imposto la data di restituzione con la funzione apposita!
    setDataRestituzione(prestito);
}

std::string Prestato::getPrestito(){
    return prestito.getData();
}

std::string Prestato::getDataRestituzione(){
    return restituzione.getData();
}

int Prestato::calcoloMulta(Data& oggi){

    //Variabile che uso per tenere conto dei giorni che sono passati!
    int i{0};

    //Confronto se la data odierna è minore della dat di restituzione, proseguo con il calcolo della multa!
    if(restituzione<oggi){

        while(restituzione<oggi){
           
            restituzione++; 
            i++;
        }

        
    }
    
    //Poichè per ogni giorno la multa è uguale ad 1$, passo direttamente come riferimento
    return i;

}

//NECESSARIE PER IL MANTENIMENTO ORDINATO DELLA LISTA!
bool Prestato::operator<(const Data& sec){
    //Uso l'overload fatto sugli oggetti di tipo data!
    return restituzione<sec;
}

bool Prestato::operator>(const Data& sec){
    //Come sopra 
    return restituzione>sec;
}

