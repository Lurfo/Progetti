//Specifica della classe rivista!
#include "riviste.h"
#include <sstream>
#include <iostream>
using std::cout;

Riviste::Riviste(const string& titolo, int anno, const string& nomer, int numr, int pagI, int pagF): 
Publication{"Dimmi gli autori dell'articolo", titolo, anno}, nome{nomer}, num{numr}{
    setPages(pagI, pagF);
    numRiviste++;
}

Riviste::~Riviste(){
    --numRiviste;
}

void Riviste::setName(string& nomer){
    nome=nomer;
}

string Riviste::getName(){
    return nome;
}

void Riviste::setNum(int numero){
    num=numero;
}

int Riviste::getNum(){
    return num;
}

void Riviste::setPages(int pagI, int pagF){
    pag[0]=pagI;
    pag[1]=pagF;
}

string Riviste::getPages(){

    std::ostringstream out;


    //Uso il ciclo for per mostrare a video la pagine della rivista!
    for(int i=0; i<2; i++){
        out<<pag[i]<<((i==1) ? " " : "-");
    }

    return out.str();
}

string Riviste::toString(){
    std::ostringstream out; 

    out<<Publication::toString()<<"Sulla Rivista: "<<getName()<<" N^ "<<getNum()<<" Pagine: "<<getPages()<<"\n";

    return out.str();
}