//Specifica delle funzioni della classe account!
#include "accounts.h"

Account::Account(int num, const string& nome, const string& cognome, double saldo): accNum{num}, balance{saldo}{
    setName(nome);
    setLast(cognome);
}

Account::~Account(){}

void Account::setName(const string& nome){
    //Definire la funzione che deve imposrar il nome è particolare
    //segno la dimensione della stringa in ingresso 
    size_t lung{nome.size()};

    //Verifico la dimensione della variabile in ingresso in modo che non sia maggiore di 15
    //Se maggiore di 15, la imposto a 15
    lung=(lung<15 ? lung : 14);

    //Copio il valore della stringa all'interno dell'array della mia classe!
    nome.copy(name, lung);

    //Inserisco alla fine il carattere di terminazione!
    name[lung]='\0';
}

string Account::getName() const{
    return name;
}

void Account::setLast(const string& cognome){
    //Definire la funzione per impostare il cognome è identica a quella del nome
    size_t lung{cognome.size()};

    lung=(lung<15 ? lung : 14);

    cognome.copy(lastName, lung);

    lastName[lung]='\0';

}

string Account::getLast() const{
    return lastName;
}

void Account::setBal(double bal){
    balance=bal; 
}

double Account::getBal() const{
    return balance; 
}

void Account::setNum(int num){
    accNum=num;
}

int Account::getNum() const{
    return accNum;
}