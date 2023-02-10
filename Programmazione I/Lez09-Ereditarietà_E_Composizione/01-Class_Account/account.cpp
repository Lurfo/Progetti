//Specifica delle funzioni della classe account.h 
#include "account.h"
#include <sstream>

Account::Account(double b){
    setBalance(b);
}

void Account::setBalance(double b){
    balance=b;
}

double Account::getBalance() const{
   

    return balance;
}

void Account::withdrawBase(double w){
    balance-=w;
}

void Account::depositBase(double w){
    balance+=w;
}

std::ostream& operator<<(std::ostream& out, const Account& b){

    out<<b.getBalance();

    return out;
}