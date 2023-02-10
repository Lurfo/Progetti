//Specifica degli elemt della classe client
#include "cliente.h"
#include <iomanip>

cliente::cliente(int code, const std::string& name, const std::string& surname): codice{code}, scadenza{}{
    //Uso le funzioni che ho definito all'interno della classe per andare a controllare se gli elemtni che ho sono
    setName(name); 
    setSecond(surname);
}

//Definizione del costruttore di ogni elemento che ho nella classe!
cliente::~cliente(){}

void cliente::setCode(int code){
    codice=code;
}

int cliente::getCode() const{
    return codice;
}

void cliente::setName(const std::string& name){
  
    //Poichè hanno una dimensione prefissata allora ho bisogona di designare una lunghezza
    //fissata, andando ad inserire il carattere terminatore alla fine del nome!
    size_t lung=name.size();

    lung = (lung<15 ? lung : 14);

    name.copy(nome, lung);

    nome[lung]='\0';

}

std::string cliente::getName() const{
    return nome;
}

void cliente::setSecond(const std::string& surn){
    
    //Allo stesso modo vado anche a svolgere il medesimo procedimento anche per la data!
    size_t lung=surn.size(); 

    lung=(lung<15 ? lung : 14);

    surn.copy(cognome, lung); 

    cognome[lung]='\0';

}

std::string cliente::getSecond() const{
    return cognome;
}

void cliente::setData(int g, int m, int a){
    scadenza.setData(g,m,a);
}

std::string cliente::getData(){

    return scadenza.getData();

}

cliente& cliente::operator=(const cliente& second){
    codice=second.codice; 
    setName(second.nome); 
    setSecond(second.cognome); 
    scadenza=second.scadenza;

    return *this;

}



