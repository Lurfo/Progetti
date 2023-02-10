//Specifica delle funzioni che appartengono alla classe CheckingAccount!
#include "CheckingAccount.h"
#include <sstream>


//Andiamo a definire il costruttore per la classe derivata!
//Come si vede, all'interno del costruttore della nostra classe andiamo a chiamare il costruttore della classe base per impostare il valore del saldo iniziale!
CheckingAccount::CheckingAccount(double bil, double tassa): 
Account(bil), totaleTasse{0.0}, numeroPrelievi{0}, depositi{0}{
    setTasse(tassa);
}

void CheckingAccount::setTasse(double t){
    tassePrelievo=t;
}

//Andiamo a riscrivere le funzioni per il prelievo!
void CheckingAccount::withdraw(double prelievo){
    totaleTasse+=tassePrelievo; //Andiamo  ad impostare il totale di quanto abbiamo pagato per ogni prelievo!
    numeroPrelievi++; //Segnamo il numero di prelievi che sono stati effettuati
    withdrawBase(prelievo+tassePrelievo);   //Andiamo a chiamare la funzione della classe base!
    //Questo è possibile poichè la classe derivata contiene sempre tutti i dati della classe da cui deriva!
}

void CheckingAccount::deposit(double deposit){
    depositi++;

    depositBase(deposit);
}

double CheckingAccount::getTotaleTasse(){
    return totaleTasse;
}


//Sovrascrivo l'operatore per andare a visualizzare tutto il contenuto della classe!
std::ostream& operator<<(std::ostream& out, const CheckingAccount& a){

    std::ostringstream output; 

    output<<"Bilancio totale dell'account: "<<a.getBalance()<<"€\nSono stati effettuati:\n"
        <<a.numeroPrelievi<<" prelievi;\n"<<a.depositi<<" depositi;\n"<<"Sono stati sottratti: "<<a.totaleTasse<<"€ di trattenute\n";

    out<<output.str();

    return out;

    
}