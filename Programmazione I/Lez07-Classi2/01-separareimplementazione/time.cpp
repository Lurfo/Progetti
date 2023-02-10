#include <iostream>
#include <string>
#include <stdexcept>
#include "timeClass.h"

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::invalid_argument;


void mostro(const string&, const Time&);
void riempio(Time&);
void riempioptr(Time*);

int main(){

    Time orario;
    Time orario2{23};
    Time orario3{15, 45};

    cout<<"Ho registrato i seguenti orari, te li mostro!\n";

    mostro("primo", orario);
    mostro("secondo", orario2);
    mostro("terzo", orario3);

    cout<<"Andiamo ad inserire un orario all'interno di del primo!\n";
    
    riempio(orario);

    cout<<"Hai modificato l'orario, ora è uguale a: \n";

    mostro("Primo modificato: ", orario);

    //Così come accadeva anche con gli altri tipi di variabili, possiamo andare a creare dei puntatori o delle variabili che hanno come riferimento la nostra classe!

    //In questo modo non stiamo facendo altro che dichiarare un puntatore di tipo class time!
    //Questo puntatore è inizializzato all'indirizzo di memoria dell'oggetto orario2!
    //Tramite questo tipo di puntatore possiamo andare a modificare e a visualizzare elementi di questo oggetto!
    Time* orario2ptr{&orario2};

    mostro("Ti faccio vedere orario2: ", orario2);

    cout<<"Vado a modificare orario2, usando un puntatore!\n";
        //Usiamo una funzione apposita che ha come argomento il nosro puntatore!
        riempioptr(orario2ptr);

    //Abbiamo quindi modificato il nostro orario2, usando un puntatore!
    //Ovviamente questo processo ha modificato il valore i orario2!

    mostro("Questo è orario2 dopo la modifica", orario2);

    //Possimo usare il puntatore anche per mostrare il contenuto di orario2!

    cout<<"Ti mostro il contenuto di orario2, usando il puntatore:\n "<<"Stantard: "<<orario2ptr->toStandard()<<"\n"
        <<"Universale: "<<orario2ptr->toUniversal()<<endl;

    //Dunque, possiamo usare con gli oggetti di una classe, sia un riferimento che un puntatore, allo stesso modo di come si è fatto anche per gli altri tipi di variabili!!!
    //Con i puntatori che puntano ad un oggetto di una classe, dobbiamo usare un tipo differente di "deferenziazione", per esprimere a quale membro 
    //di quell'oggetto vogliamo accedere, defereniazione espressa proprio dall'operatore "->"


    cout<<"Ti mostro in che modo agisce il distruttore:\n";

}

void mostro(const string& mess, const Time& h){

    cout<<mess<<": "<<"\n In formato universale: "<<h.toUniversal()
        <<"\n In formato Standard: "<<h.toStandard()<<"\n"<<endl;

}

void riempio(Time& t){
    int h,m,s;

    bool sbagliato;
    
    //Andiamo ad usare un do-while per poter permettere all'utente di inserire i valori corretti all'interno della 
    //nostra classe
    do{
    
    sbagliato=false;

    cout<<"Dimmi i valori di ore(formato 0-24), minuti e secondi:\n";
        cin>>h >>m >>s;

    //Come vediamo qui usiamo la struttura necessaria a gestire le eccezioni, la prima cosa da usare è questo try
    //esso ha il compito di tentare di eseguire quello che è racchiuso tra le parentesi!
    try{

        t.setTime(h,m,s);

    }
    
    //Subito dopo abbiamo il catch, legato a quale risultato ha concluso il try!
    //esso appunto "acchiappa", l'eccezione che si è generata
    catch (invalid_argument& cosa){

        //Compito poi di questa istruzione è farci vedere quale eccezione si è generata!
        cout<<"Ooooooh, ma che fai: "<<cosa.what()<<"\n\n";
        sbagliato=true;
    }

    }while (sbagliato);

}

void riempioptr(Time* ptr){

    int h,m,s;

    cout<<"Dimmi l'orario: \n";
    cin>>h >>m >>s;

    //ATTENZIONE--> Per specificare a quale elemento dell'oggetto ci stiamo riferendo, dobbiamo sempre usare questa freccia!
    //in questo modo abbiamo che il nostro puntatore, sposta la sua attenzione direttamente su quell'oggetto!
    //La freccia che qui vediamo è proprio un operatore, di grande importanza!
    ptr->setTime(h,m,s);


}