//All'interno di questo file, andiamo ad implementare le funzioni che sono necessarie
//alla nostra classe!

//Nell'implementazione, dobbiamo sempre specificare al pre-processore dove sono definire le
//funzioni che vogliamo andare ad implementare, quindi dobbiamo includere la classe che abbiamo definito!
#include "timeClass.h"

#include <iostream>

#include<string>

//Tale classe ci serve per andare ad utilizzare alcune funioni quali: setfill(), che consente di inserire degli 0!
#include<iomanip>

//Questa libria usa una funzione molto importante, chiamata ostringstram, che serve per andare a copiare, all'interno di
//una stringa determinati elementi, in modo da poter salvare il formato dell'ora all'interno di una stringa e restituirla come tale
#include <sstream>

//La classe except, ci serve per andare ad individuare eventuali errori che si possono verificare all'interno del nostro programma,
//dovuto, ad esempio all'interimento di un valore che non può rientrare in quell'intervallo!
#include <stdexcept>

using std::string;
using std::ostringstream;
using std::invalid_argument;

//La prima cosa da andare a definire è il nostro constructor!
//Andiamo ad usare l'operatore "::" che va a definire che la funzione che qui stiamo specificando, 
//appartiene alla classe Time!

//Come vediamo, nel constructor, passiamo delle variabili di default, che sono 0, qual'ora non dovesse essere inizializzato
//dalla funzione chiamante
Time::Time(int h, int m, int s){

    //Usiamo la funzione che abbiamo definito prima, setTime, per andare ad inserire questi valori dell'interno del nostro della nostra classe
    //in questo modo, possiamo usare le condizioni che andiamo ad inserire all'interno di essa per controllare i valori!

    setTime(h,m,s);

}

//Dopo aver definito il constructor possiamo andare a definire il nostro destructor!

Time::~Time(){
    
    //Usiamo questo tipo di oggetto solo per andare ad identificare rispetto a che orario stiamo andando a chiamare il distruttore
    ostringstream orario;

    orario<<std::setfill('0')<<std::setw(2)<<hour<<":"<<std::setw(2)
        <<minut<<":"<<std::setw(2)<<sec;

    //Facciamo dire al nostro distruttore su quale elemento è stato chiamato!
    std::cout<<"Destructor per: "<<orario.str()<<std::endl;

}

void Time::setTime(int h, int m, int s){

    //In questo caso, tale funzione ha il compito di andare ad inserire i valori che o sono dati dal costruttore, oppure sono dati 
    //dall'utente in fase di inserimento!
    if((h>=0 && h<=24) && (m>=0 && m<=59) && (s>=0 && s<=59)){
        hour=h;
        minut=m;
        sec=s;
    }

    else{
        //NOTA: Quello che andiamo ad inserire qui è un tipo di eccezione, definita dalla libreria standard "stdexcept"
        //In particolare, questo tipo di eccezione serve per andare a convalidare i valori che inviamo alla funzione
        //Il tipo di eccezione, infatti "invalid_argument" definisce proprio che stiamo inviando un tipo di eccezione dovuta all'inserimento
        //di valori non corretti alla nostra funzione!
        
        //Possiamo anche lanciare(throw, appunto) inviare un messaggio alla funzione chiamante!
        throw invalid_argument(
            "I valori che hai inserito di ore, minuti o secondi non sono corretti!"
        );
    }
}

string Time::toUniversal() const{

    //Andiamo ad usare questo tipo di oggetto per definire una stringa che contiene il nostro orario!
    //la funzionalità di questo oggetto è che, legge tutti i valori che gli sono dati in ingresso, proprio come viene 
    //fatto anche con un cout e li formatta inserendoli all'interno di una stringa!
    ostringstream orario;

    //Usando quindi "<<", stiamo passando al nostro oggetto tutti i valori che dovrà poi leggere e inserire all'interno di una
    //stringa!
    //In particolare, usiamo due funzioni molto importanti:
    /* Esse sono
       1) setfill()--> questa va riempire tutti i caratterei necessari per definire una variabile con il valore che inseriamo tra le parentesi!
       
       2) setw()--> indica con quanti valori dobbiamo rapprensentare un certo elemento!, in questo caso, abbiamo scelto il valore 2
                    in modo che abbiamo la possibilità di andare ad inserire uno zero, se il valore è rappresentato da un singolo numero!

        Usando queste due funzioni, dunqe, si ha che: 

        -Anzichè rappresenta un semplice numero come "3", viene rappresentato come "03", poichè deve essere scritto con 2 elementi, uno dei quali viene
        inserito dalla funzione setfill    
    */
    orario<<std::setfill('0')<<std::setw(2)<<hour<<":"<<std::setw(2)
        <<minut<<":"<<std::setw(2)<<sec;

    //Poichè la funzione è di tipo string, essa dovrà restituire questo tipo di elemento!
    //per ottenre la stringa prodotta dall'oggetto ostringstream, andiamo proprio ad usare la funzione .str()!
    //ovviamente, per mostrare a schermo la stringa basta poi usare un cout e chiamare la funzione!
    return orario.str();

}

string Time::toStandard() const {

    ostringstream orario;

    if(hour>=0 && hour<=12){

        orario<<std::setfill('0')<<std::setw(2)<<hour<<":"
            <<std::setw(2)<<minut<<":"<<std::setw(2)<<sec<<" AM";

    }

    else{

        orario<<std::setfill('0')<<std::setw(2)<<hour-12<<":"
            <<std::setw(2)<<minut<<":"<<std::setw(2)<<sec<<" PM";


    }

    return orario.str();

}
