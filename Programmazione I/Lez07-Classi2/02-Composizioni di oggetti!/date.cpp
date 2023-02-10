//In questo file andiamo a specificare quali sono le funzioni della nostra classe!
//Come prima cosa dobbiamo includere il nostro header che contiene la signature delle funzioni!
#include "date.h"

//Ci sarà poi molto utile per il costruttore!
#include <iostream>

//Utile per l'oggetto ostringstream
#include <sstream>

#include <iomanip>

//Per verificare l'inserimento di alcuni dati evetualmente errati!
#include <stdexcept>

//Andiamo, come prima cosa a definire il costruttore!
//Il costruttore, non fa altro che prendere in ingreesso dei dati e inviarli alle varie funzioni, in modo che essi possano eseguire un controllo
//Inoltre il nostro costruttore contiene anche dei dati "base" che vengono inizializzati se il driver non specifica differentemente
Data::Data(int d, int m, int y){
    //Come si vede la funzione per impostare la data contiene due argomenti, poichè dobbiamo effetturare il constrollo della dat
    //verificando che essa sia valida per il mese che abbiamo inserito!
    setMonth(m);
    setYear(y);
    setDay(d);

    count++;
}

Data::~Data(){
    std::cout<<"Sono il distruttore per la data: "<<toString()<<std::endl;
    count--;
    std::cout<<"Sono rimaste: "<<count<<" date\n";
}


unsigned int Data::checkDay(int d) const{
    //All'interno di questo built-In Array andiamo ad inserire i numeri di giorni per ognir mese dell'anno!
    //Il primo valore viene inizializzato a 0, in modo che, quando viene indirizzato, si ha che dayPerMonth[1]=31
    //cioè: i giorni del primo mese sono 31!
    static const int dayPerMonth[13]{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    //Andiamo quindi a constrollare il giorn che si è inserito!
    if(d>0 && d<=dayPerMonth[month]){
        return d;
    } 

    //Questo if serve per controllare se l'anno che stiamo considerando è un anno bisestile!
    if(month==2 && d==29 && (year % 400 ==0 || (year%4==0 && year%100 !=0))){
        return d;
    }


    //Se nessuna delle due condizioni precedenti viene soddisfatta, allora lanciamo l'eccezione di argomento non valido!
    else throw std::invalid_argument("Oh, guarda che non è corretto il giorno che hai inserito!");
}


Data& Data::setDay(int d){

    //Nella funzione setDay, vado a chiamare la funzione checkDay, in questo modo
    //Impongo cioè che il valore della variabile day, della classe è uguale a quello che restituisce la funzione check!
    this->day=checkDay(d);

    return *this;
}

Data& Data::setMonth(int m){

    if(m>0 && m<=12){
       this->month=m;
    }

    //Anche qui lanciamo l'eccezione se il mese che abbiamo inserio non corrisponde alla condizione che è stata definita prima!
    else{
        
        throw std::invalid_argument("Oh, il mese che hai inserito non è corretto, deve essere compreso tra 1-12!");
    
    }

    return *this;
}

Data& Data::setYear(int y){
    if(y>0){
        this->year=y;
    }

    else{
        throw std::invalid_argument("L'anno deve essere maggiore di zero oh");
    }

    return *this;
}

std::string Data::toString() const{

    std::ostringstream output;

    output<<std::setfill('0')<<std::setw(2)<<day<<'/'<<std::setw(2)<<month<<"/"<<year;

    return output.str();

} 