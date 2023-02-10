//Andiamo a definire una  nuova classe, chiamata checkingAccount, come classe derivata di account, la quale va ad aggiungere la specifica della commissione sul prelievo
#include "account.h"
//Dobbiamo ovviamente includere il file .h della classe account, altrimenti non possiamo dichiarare la nuova classe come derived di account



#ifndef  CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

//Per specificare che la classe che stiamo definendo è una classe che eredita determinati membri dalla classe base Accout, scriviamo in questo modo
//Questo è chiamato "public inheritance" ed è il tipo più comune, esistono anche il private e quello protected, ma sono usati molto raramente
class CheckingAccount: public Account{

    //Nella classe derivata bisogna andare a definire nuovamente anche tutti gli operatori su cui abbiamo precedentemente eseguito l'override!
    friend std::ostream& operator<<(std::ostream&, const CheckingAccount&);

    //La classe derivata ovviamente contiene tutte le operazioni e i dati dell classe da cui deriva, ma dobbiamo aggiungere in questo caso 
    //Un valore che indica le commissioni di prelievo
    private: 
        double tassePrelievo;
        double totaleTasse;
        //Nuove variabili che hanno lo scopo di considerare il numero di prelievi che ho effettuato e il numero di depositi
        int numeroPrelievi;
        int depositi;

    public: 
        //Una delle cose che la classe non può ereditare è il costruttore, dobbiamo quindi andare a definire un nuovo costruttore per questo tipo di classe 
        CheckingAccount(double =0.0, double=0.0);

        //Aggiungo la funzione che va ad impostare la tassa 
        void setTasse(double);

        //Andiamo, a definire una nuona funzione di prelievo che ha il compito di andare a prelevare, in questo caso, la andiamo a definire poichè
        //Dobbiamo tenere il conto anche della tassa di prelievo che dobbiamo sottrarre al totale 
        void withdraw(double);

        //Andiamo ad eseguire un ovveride della funzione per il deposito da usare con questa classe 
        void deposit(double);

        //Per mostrare le trattenute ad ogni prelievo!
        double getTotaleTasse();

        //ATTENZIONE, NON BISOGNA ANDARE A DEFINIRE UNA FUNIONE PER MOSTRARE IL DENARO IN QUANTO POSSIAMO USARE QUELLA CHE HO EREDITATO
        //DALLE CLASSE BASE ACCOUNT!








};

#endif