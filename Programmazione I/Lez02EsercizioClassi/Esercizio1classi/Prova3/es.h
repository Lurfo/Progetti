#include <string>

class Account{

//Zona dei dati inaccessibile
private: 

    std::string name;
    int balance{0};

//Zona accessibile delle funzioni
public:

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
        balance-=b1;
    }

//Visualizzare Nome e denaro
    std::string getName() const{
        return name;
    }

    int getBalance() const{
        return balance;
    }


};
