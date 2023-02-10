//Creazione della classe account che serve al programma per leggere i dati casualmente 

#include <string>

using std::string;

#ifndef ACCOUNT_H
#define ACCUNT_H

class Account{
    private: 
        //La viariabile che definisce il numero del conto è quella che usiamo per andare a ricercare all'interno della nostra memoria tutti gli elementi che ci 
        //occorrono!
        int accNum;

        //Nota bene, per sfruttare il fatto che tutti i gli oggetti che ho devono essere costanti, devo necessariamente definire sia il nome che il 
        //cognome, come un array di caratteri, in questo modo sono sicuro di avere sempre una dimensione fissa per nome e cognome!
        char name[15];
        char lastName[15];
        double balance;

    public: 

        //Costruttore
        Account(int =0, const string& =" ", const  string& =" ", double =0.0);
        //Distruttore
        ~Account();

        void setName(const string&);
        string getName() const;

        void setLast(const string&);
        string getLast() const;

        void setNum(int);
        int getNum() const;

        void setBal(double);
        double getBal() const; 

};





#endif