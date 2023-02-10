//Abbiamo quindi definito tutte le cassi che ci occorrono, andiamo quindi a scriver il driver che ha lo scopo di mostrare e 
//gestire tutte le classi che abbiamo qui definito!
#include <iostream>
#include <string>

//Serve per definire gli oggetti di tipo data che possiamo utilizzare
#include "date.h"

//Serve per definire gli offetti di tipo employee!
#include "employee.h"

#include <stdexcept>

using std::cout;
using std::cin;
using std::endl;
using std::string;

void impostanome(Emp& , string&, string&);
void impostacompl(Emp&, Data&, int, int, int);
void impostaassunz(Emp&, Data&, int, int, int);

//Vediamo che questa è la funzione che abbiamo definito come amica della classe, in questo caso possiamo sfruttarla per utilizzare qualsiasi tipo di dato membro!
void provaAmico(Emp&);


//Vediamo che tale variabile, per essere utilizzata deve, ovviamente essere dichiarata, per andare effettivamente ad allocare spazio nella memoria!
int Emp::empCount{0};
int Data::count{0};

int main(){

    //Andiamo a dichiarare due oggetti di tipo data che segnano la data del compleanno e quella di assunzione!
    Data comp;
    Data assunz;

   Emp prova{"Nullo", "Nullo", assunz, comp};

    cout<<"Ti mostro quale operatore ho inserito: \n";
    cout<<prova.toString()<<endl;

    string nome;
    string cognome;

    cout<<"Dimmi il nome e cognome di chi vuoi inserire: \n";
    getline(cin, nome);
    getline(cin, cognome);

    impostanome(prova, nome, cognome);

    int g,m,a;

    cout<<"Dimmi la data di nascita:\n";
        cin>>g>>m>>a;

    impostacompl(prova, comp, g,m,a);

    cout<<"Dimmi la data di assunzione: \n";
        cin>>g>>m>>a;

    impostaassunz(prova, assunz, g,m,a);

    cout<<"Alla fine hai inserito numero: "<<Emp::empCount<<" impiegat*: \n"<<prova.toString()<<endl;


    cout<<"Ti mostro cosa posso fare con una funzione amica: "<<endl;

    provaAmico(prova);

    cout<<"Dopo aver chiamato la funzione vediamo l'operatore è uguale a:\n "<<prova.toString()<<endl;
    cout<<"Rispetto alla funzione iniziale, alcuni dati sono stati modificati!\n";
    
}

//Andiamo ad implementare in altre funzioni l'inserimento dei dati all'interno della nostra classe!

void impostanome(Emp& clas, string& nome, string& cognome){

    clas.setFirstName(nome).setSecName(cognome);

}


void impostacompl(Emp& clas, Data& comp, int g, int m, int a){
    try{
    comp.setMonth(m).setYear(a).setDay(g);
    }

    catch (std::invalid_argument& cosa){
        cout<<"Che fai oh, hai sbagliato: "<<cosa.what()<<endl;
    }

    clas.setBirthDate(comp);

}
void impostaassunz(Emp& clas, Data& ass, int g, int m, int a){

    try{
        ass.setMonth(m).setYear(a).setDay(g);
    }

    catch(std::invalid_argument& cosa){
        cout<<"Hai errato: "<<cosa.what()<<endl;
    }

    clas.setHireDate(ass);


}

void provaAmico(Emp& impieg){

    //Vediamo che la funzione amico è una funzione molto potente, essa infatti può accedere a tutti i valori privati della funzione membro e anche
    //modificarli!!!
    
    //Di conseguenza è molto importante prestare attenzione a quali funzioni vengono definite come amiche e quali no, in modo da evitare di fare casini
    //nella gestione della classe!

    //Molto utile però nel caso in cui abbiamo l'overloading di alcune funzioni!!!
    cout<<"Sonno in prova amico, voglio mostrarti tutti i dati contenuti nella classe!\n";
    cout<<"Nome: "<<impieg.firstName;
    cout<<"\nCognome: "<<impieg.secName;
    

    cout<<"\nMa posso anche modificare i dati!\n";
    cin>>impieg.firstName>>impieg.secName;

    cout<<"Ho finito il mio lavoro, torno al main!";

}
