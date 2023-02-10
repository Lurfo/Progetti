//Specifica degli elementi della classe palestra.h
#include "palestra.h"

Palestra::Palestra(const std::string& n): name{n},  client{}{}

Palestra::~Palestra(){

}

void Palestra ::setName(const std::string& n){
    name=n;
}

std::string Palestra::getName() const{
    return name;
}

void Palestra::aggiungiElemento(const cliente& nuovo){

    client.push_front(nuovo);

}

bool Palestra::trovato(int code){
    for(std::list<cliente>::iterator p=client.begin(); p!=client.end(); ++p){
        if(code==(*p).getCode()){
            return true;
        }
    }

    return false;
}