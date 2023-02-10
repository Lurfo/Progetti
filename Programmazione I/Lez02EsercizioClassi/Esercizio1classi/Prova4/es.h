#include <string>
#include <iostream>

class Account{

//Zona dei dati inaccessibile
private: 

    std::string name;
    int balance{0};

//Zona accessibile delle funzioni
public:

    Account(std::string accountName,int b1):
        name{accountName}{
            balance=b1;
        }
        

//Imposto nome e saldo 
    void setName(std::string nomeIng){
        name=nomeIng;
    }

    void setBalance(int b1){
        balance=b1;
    }

//Funzioni per aggiungere o togliere denaro
    void addBalance(int b1){
        balance= balance + b1;
    }

    void subBalance(int b1){
        if(b1<=balance)
        balance-=b1;

        else if(b1<0 or b1>balance)
        std::cout<<"Impossibile effettuare operazione\nSomma da prelevare maggiore del saldo disponibile"<<std::endl;
    }

//Visualizzare Nome e denaro
    std::string getName() const{
        return name;
    }

    int getBalance() const{
        return balance;
    }


};
