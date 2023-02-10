#include <string>

//Dichiaro la classe di cui ho bisogno
class Account{
private: //creo la "zona" di dati privata 
  
    std::string name; //impoto i dati necessari
    int balance{0};

public:
    //Imposto il nome
    void setName(std::string accountName){
        name=accountName;
    }
    //Imposto il saldo
    void setBalance(int b1){
        balance=b1;
    }
    //Prelevo il nome
    std::string getName() const{
        return name;
    }
    //Prelevo il saldo
    int getBalance(){
        return balance;
    }
};