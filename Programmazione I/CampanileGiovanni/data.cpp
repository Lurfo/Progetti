//Vado a specificare l'implementazione delle funzioni

#include "data.h"
#include <sstream>
#include <string>
#include <iostream>
#include <stdexcept>
#include <iomanip>



//Specifica del costruttore
Data::Data(int g, int m, int y){
    //Chiama la funzione per impostare giorno mese e anno!
    setData(g,m,y);
}

//Specifica del distruttore
Data::~Data(){
  // std::cout<<"Elimino la data: "<<getData()<<std::endl;
}

//Specifica delle funzioni che hanno il compito di impostare giorno, mese e anno
void Data::setData(int g, int m, int a){
    //Sequenza di impostazione importante!-->Dobbiamo considerarla per andare a verificare il valore del giorno che abbiamo inserito!
    //Facciamo in modo di verificare che il valore che abbimo inserito sia vorretto!
   try{

    setYear(a);
    setMonth(m);
    setDay(g);

    }

   catch(const std::exception& e){

       std::cout<< e.what() <<'\n';
    }

}


//La funzione dell'anno e del mese vanno a effettuare un controllo che il valor inserito sia corretto
void Data::setYear(int a){
    if(a<=0){
        throw std::invalid_argument("Guarda che hai inserito un valore che non va bene");
    }

    else{
        year=a;
    }

    return;

}

void Data::setMonth(int m){
    if(m<1 || m>12){
        throw std::invalid_argument("Il valore del mese che hai detto non è corretto, dovresti metterne uno compreso tra 1-12");
    }

    else 
        month=m;

    return;
}


//La funzione setDat esegue anche il controllo sul fatto che l'anno può essere bisestile!
void Data::setDay(int g){

    if(g<=dayPerMonth[month] && g>0){
        day=g;
    }
    
    //Controllo per anno bisestile
    else if(month==2 && (year%400==0 || (year%4==0 && year%100!=0))){
        day=g;
    }

    else{
        throw std::invalid_argument("Guarda che il valore che hai inserito non è valido!");
    }

    return;


}

//Specifica della funzione che ha il compito di vedere se una data è minore dell'altra
bool Data::operator<(const Data& d2){

            //Si confrontano prima gli anni
            if(year<d2.year){
                return true;
            }

            //Se la condizione fallisce si confrontano i mesi
            else if(month<d2.month){
                return true;
            }

            //Altrimenti i giorni
            else if(day<d2.day){
                return true;
            }


            //Se nessuno delle condizioni di prima è verificata allora non vale la condizione di minoranza
            else 
                return false;
}


//Imposto la funzione che ha il compito di andare a mostrare a video la data
std::string Data::getData(){
    std::ostringstream output;

    output<<std::setfill('0')<<std::setw(2)<<day<<"/"<<std::setw(2)<<month<<"/"<<year;

    return output.str();

}

//Vado ad impostare la funzione che serve ad incrementare la data
void Data::increment(){

    //La condizione incrementa il giorno se non siamo alla fine del mese e se il mese non corrisponde a febbraio e l'anno e bisestile
    if((day<dayPerMonth[month]) || (day==28 && month==2 && (year%400==0 || (year%4==0 && year%100!=0)))){
        day++;
    }

    //La condizione controlla che siamo alla fine del mese e il mese non è dicembre!
    //Controlla anche se siamo alla fine di febbraio e se non è composto da 29 giorni!
    else if((day==dayPerMonth[month] && month!=12) || (day==29 && month==2 && (year%400==0 || (year%4==0 && year%100!=0)))){
        day=1;
        month++;
    }

    //Se siamo alla fine dell'anno reimpostiamo il giorno e il mese e andiamo ad incrementare l'anno!
    else if(month==12 && day>=dayPerMonth[month]){
        day=1;
        month=1;
        year++;
    }


}

//Specifica della funzione di decremento!
//La specifica di tale funzione è molto simile a quella dell'incremento!
//Solo che, in questo caso è stata fatta "al contrario, in modo da verificare il passaggio di mese e il passaggio di anno!"
void Data::decrement(){
    if(day==1 && month==1 && year>0){
        month=12;
        day=dayPerMonth[12];
        year--;
    }

    else if(day==1){
        if(month==3 && (year%400==0 || (year%4==0 && year%100!=0))){
            day=29; 
            month--;
        }

        else{
            month--;
            day=dayPerMonth[month];
        }
    }

    else{
        day--;
    }


}

//Restituisce un tipo di operatore data, in quanto può essere sfruttato proprio con il cascading per fare in modo da concatenare più operatori 
//tra loro
Data& Data::operator++(){
    increment();

    return *this;
}

//Specifica dell'operatore di post-incremento!
//il dato di ritorno deve essere di tipo data, ovviamente!
Data Data::operator++(int){

    //Per salvare il valore della data prima che venga modificata
    Data salvo{*this};

    increment();

    //Facciamo ritornare il valore di salvo, quello che deve essere per primo mostrato a video!
    return salvo;


}

//Specifica dell'operatore "+=", come nel caso del ++ restituisce un riferimento al valore della variabile che abbiamo modifcato
Data& Data::operator+=(int i){

    //Strutture simile a quella che abbiamo visto per il pre-increment, facciamo solo in modo di incrementare la data in base a quanti giorni 
    //dobbiamo sommare-->motivo dell'uso del ciclo for!
    for(int j=0; j<i; j++){
      //  std::cout<<getData()<<std::endl;
        increment();
    }

    //In modo da abilitare il cascading
    return *this;

}

//Dobbiamo sempre aver un dato in ingresso, che corrisponde alla data con cui vogliamo andare a confrontare la nostra!
bool Data::operator!=(const Data& d){
    if(year==d.year && month==d.month && day==d.day){
        return true;
    }

    else 
        return false;
}

//Anche qui, come sopra, dobbiamo avere un dato in ingresso per il confronto tra le 2 date!
//Come si vede è l'opposto dell'operatore <!
bool Data::operator>(const Data& d){
    if(year>d.year){
        return true;
    }

    else if(month>d.month){
        return true;
    }

    else if(day>d.day){
        return true;
    }

    else 
        return false;
}

//Vado a specificare l'operatore di pre-decremento
Data& Data::operator--(){
    decrement();

    return *this;
}

//Ovviamente anche la strutture del post-decremento è molto simile a quella del post-incremento!
Data Data::operator--(int){

    Data temp{*this};

    decrement();

    return temp;

}

//Specifica dell'operatore -=
Data& Data::operator-=(int g){
    for(int i=0; i<g; i++){
        decrement();
    }

    return *this;
}

Data& Data::operator=(const Data& confronto){
    day=confronto.day;
    month=confronto.month;
    year=confronto.year;
    return *this;
}