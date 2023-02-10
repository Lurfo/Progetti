//Specifica delle funzioni della classe book
#include "book.h"
#include <sstream>
using std::ostringstream;

//Costruttore, che va a chiamare il costruttore della classe precedente!
Book::Book(const string& titolo, int anno, const string& casa,const  string& code): 
Publication{"Dimmi il nome degli autori del libro", titolo, anno}, editor{casa}, ISBN{code}{
    numLibri++; //Incremendo il contatore degli elementi della classe
}

//Distruttore della classe
Book::~Book(){
    --numLibri; //Il distruttore della classe va a diminuire il numero di elementi che ho conservato!
}

void Book::setEditor(string& nome){
        editor=nome;
}

string Book::getEditor(){
    return editor;
}

void Book::setISBN(string& code){
    ISBN=code;
}

string Book::getISBN(){
    return ISBN;
}

string Book::toString(){
    ostringstream out;

    out<<Publication::toString()<<"Casa editrice: "<<getEditor()<<", ISBN: "<<getISBN()<<"\n";

    return out.str();

}