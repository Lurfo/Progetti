//Specifica delle funzioni della classe publication!
#include <iostream>
#include "publication.h"
#include <sstream>
using std::cout;
using std::cin;
using std::ostringstream;

Publication::Publication(const std::string& out, const string& titolo, int y): title{titolo},anno{y}{
    string autor; 
    cout<<out<<"\n";
    cout<<"[0 - Per terminare]\n";
    getline(cin, autor);

    while(autor!="0"){
        setAuthors(autor);
        cout<<"Dimmi il nome dell'autore\n";
        getline(cin, autor);
    }
}

void Publication::setAnno(int y){
    anno=y;
}

void Publication::setTitolo(const string& titol){
    title=titol;
}

void Publication::setAuthors(const string& nome){
    autori.push_back(nome);
}

int Publication::getYear(){
    return anno;
}

string Publication::getTitle(){
    return title;
}

//Mostra il contenuto dell'array di autori che ho definito!
string Publication::getAuthors(){
    int num=autori.size();
    std::ostringstream out;

    for(int i=0; i<num; i++){
        out<<autori[i]<<((i!=num-1) ? ", " : " ");
    }

    return out.str();
}

//Funzione che permette di andare ad inserire gli elementi all'interno di una stringa!
string Publication::toString(){

    //Per fare ciò andiamo ad usale le funzioni che abbiamo già dichiarato in precedenza!
    ostringstream out;

    out<<getAuthors()<<"("<<getYear()<<"): "<<getTitle()<<"\n";

    return out.str();


}

//Override dell'operatore < per le pubblicazioni!
//Tale operazione ci permette di effettuare l'operazione < sulle operazioni!
bool Publication::operator<(const Publication& sec){
          
    if(autori==sec.autori){
        //Faccio ordinamento secondo l'anno di pubblicazione!
        return anno<sec.anno;
                
    }

 //Uso l'operazione del minore sui vettori (che è già effettuato come overload!)

     return autori<sec.autori;


}