//All'interno di questo file andiamo poi a specificare tutte le funzioni che sono state inserite all'interno della classe!
#include <iostream>
#include <sstream>

//Ovviamente dobbiamo includere all'interno di questa specifica il proprio file header!
//NOTA: Poichè il file header che specifica la classe è stato già inserito all'interno di employee.h, non dobbiamo andare 
//a reinserirlo nuovamente all'interno di questo!
#include "employee.h"

using std::string;
using std::cout;
using std::endl;
using std::ostringstream;


//Abbiamo definito il costruttore per il nostro impiegando, fornendo tutti i dati che ci occorrevano
//In queto moso, viene chiamato il costruttore di defaul per quanto riguarda le date di compleanno e di assunzione!
Emp::Emp(const string& fName, const string& sName, const Data& hDay, const Data& bDay)
: firstName{fName}, secName{sName}{

    //Ad ogni chiamata del costrutto andiamo ad incrementare il conteggio del conteggio!
    empCount++;

}

Emp:: ~Emp(){
    cout<<"Sono il distruttore per:\n"<<toString()<<endl;
    empCount--;
    //Mentre ad ogni chiamata del distruttore, andiamo a incrementare il valore del conteggio
    cout<<"Sono rimasti: "<<empCount<<" impiegati!\n";
}

string Emp::toString(){
    ostringstream output;

    //Come vediamo, possiamo andare a richiare sugli oggetti membro tutte le funzioni della classe data!
    output<<"Nome: "<<firstName<<"\nCognome: "<<secName<<"\nData di Nascita: "<<birthDay.toString()
        <<"\nAssunto dal: "<<hireDate.toString();

    return output.str();
}

Emp& Emp::setFirstName(string& firstName){
    this->firstName=firstName;

    return *this;
}

Emp& Emp::setSecName(string& secName){
    this->secName=secName;

    return *this;
}

Emp& Emp::setHireDate(const Data & h){

    //Nella funzione che va ad impostare la data, andiamo ad utilizzare il cascading che abbiamo usato nella classe data!
    //Usiamo un memberwhise assignements, in modo da copiare tutti i valori che sono contenuti all'interno della classe h, nella classe hireDate
   
    //ATTENZIONE: in questo caso possiamo pienamente sfruttare questa cosa poichè entrambi le classi di dati contengono solo delle variabili!
    //se ci fossero stati dei puntatori, sarebbe sorto un problema, poichè avremmo copiato il medesimo indirizzo di memoria, dunque avremmo 
    //avuto eventuali errori dovuti alla modifica di una variabile che non deve essere modificata!
    hireDate=h;

    return *this;
}


Emp& Emp::setBirthDate(const Data& b){

    //Allo stesso modo andiamo ad usare il memberwhise assignement anche nel caso della data del Compleanno!
    birthDay=b;

    return *this;

}


