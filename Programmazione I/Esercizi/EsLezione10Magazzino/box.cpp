//Definizioen degli elementi che appartengono alla classe box 
#include "box.h"


//Definizione del costruttore che contiene anche argomenti di default!
Box::Box(int c, const std::string& name, int q, double prc): code{c}, qnt{q}, price{prc}{
    //In questo vado ad utilizzare, per inserire il nome del prodotto all'interno della classe
    //la funzione di setName
    setName(name);
}

//Distruttore
Box::~Box(){} //Uso il distruttore di default dei vari elementi che compongno la classe

//Definizione delle funzioni set e get!
void Box::setCode(int c){
    code=c;
}

int Box::getCode() const{
    return code;
}

//Definizione della funzione che va ad impostare il nome del box 
void Box::setName(const std::string&  n){
    //Definisco un intero con la lunghezza della stringa
    //Deo sempre usare, come tipo per definire una lunghezza, il tipo 
    //"size_t"
    size_t lung =n.size();

    //Controllo che la lunghezza della stringa non sia superiore al valore massimo della stringa del nome 
    //Che ho impostato a 15

    //Se è minore allora la lunghezza resta invariata, se è minore, la imposto uguale a 14!
    lung=(lung<15 ? lung : 14);

    //copio il valore della stringa all'interno della variabile nome
    //Uso la funzione di classe copy per andare a copiare tale valore
    n.copy(name, lung);

    //A questo punto, imposto come ultimo valore all'interno della stringa il carattere di terminazione 
    //che, con il fatto che il valore della stringa è preimpostato, il carattere di terminazione può essere omesso
    //se la stringa ha una lunghezza maggiore rispetto a quella che ho definito
    name[lung]='\0';

}

std::string Box::getName() const{
    return name;
}


void Box::setQuant(int q){
    qnt=q;
}

int Box::getQuant() const{
    return qnt;
}

void Box::setPrice(double p){
    price=p;
}

double Box::getPrice() const{
    return price;
}

std::string Box::toString() const{
    std::ostringstream out; 

    out<<"Box Name: "<<name<<"\n"; 
    out<<"Code: "<<code<<"\n"; 
    out<<"Quant.: "<<qnt<<" Price: "<<price<<"€\n";

    return out.str();

}
