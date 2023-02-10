//Andiamo a definire un esempio di Polimorfismo sulle classi che abbiamo definito in 01

#include "account.h"
#include "CheckingAccount.h"
#include <iostream>

int main(){
    std::cout<<"Ti faccio vedere un esempio di polimorfismo:\n";

    Account nuovo1;
    CheckingAccount nuovo2;

    std::cout<<nuovo1.type()<<"\n";
    std::cout<<nuovo2.type()<<"\n";

    std::cout<<"Ho invocato lo stesso messaggio su due oggetti differenti e hai avuto due risposte differenti, questo è l'esempio di un polimorfismo\n";
    //Questo vuol dire che il nostro driver, anche se lancia lo stesso messaggio, essendo riferiti a due oggetti differenti, abbiamo che esso viene 
    //interpretato in maniera differente a seconda dell'oggetto a cui questo si riferisce!
    //Potrei andare ad aggiungere anche un altra classe, ma lanciando il medesimo messaggio, otterei sempre la risposta riferita a quella classe!


}
