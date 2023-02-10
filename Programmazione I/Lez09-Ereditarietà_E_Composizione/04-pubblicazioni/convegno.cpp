//Specifica delle funzioni della classe convegno he ho definito
#include "convegno.h"
#include <sstream>

Convegno::Convegno(const string& nome, int anno, const string& luog, int pag):
Publication{"Dimmi il nome degli autori del convegno!", nome, anno}, luogo{luog}, pagina{pag}{
    numConvegno++;
}

Convegno::~Convegno(){
    --numConvegno;
}

void Convegno::setLuogo(string& citt){
    luogo=citt;
}

string Convegno::getLuogo(){
    return luogo;
}

void Convegno::setPagina(int pag){
    pagina=pag;
}

int Convegno::getPagina(){
    return pagina;
}

string Convegno::toString(){
    std::ostringstream out;

    out<<Publication::toString()<<"Convegno tenutosi a: "<<getLuogo()<<"\nInserito alla pagina "<<getPagina()<<" del registro\n";

    return out.str();
}