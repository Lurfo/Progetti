//Andiamo a definire un programma che è in grado di andare ad inserire degli elementi all'interno di una file di testo che scegliamo!
#include <iostream>
#include <string>


//Dobbiamo andare, ad inserire la classe che ci permette di andare a creare un oggetto con il quale andare a scambiare informazioni per scrivere degli 
//elementi all'interno di un fie di testo!
//NOTA BENE: Esistono differenti classi che ci possono essere di aiuto in questo processo!
#include <fstream> //Contiene tutti gli elementi necessari per poter comunicare con la nostra classe e scambiare i dati!

using std::cin; 
using std::cout;
using std::string;
//Per andare a definire la classe che ci serve per gestire i file possiamo inserire:
using std::ofstream; //Questa ci consente di aprire i file solo in scrittura!
//Possiamo anche considerare: 
//using std::ifstream; Questa ci consente di aprire i file solo in lettura 
//using std::fstream; Questa classe è più completa e ci consente di andare sia a scrivere che leggere su di un file 

using std::ios; //Tale è invece la funzione che ci permette di specificare le modalità di apertura di un file, poichè ne possono esistere di differenti!


//Definisco un programma che salva su di un file alcune variabili di un conto bancario come, numero, nome intestatario e saldo
int main(){
    string nome, cognome;
    int conto; 
    double saldo; 

    //Dobbiamo quindi specificare la classe che ci permette di comunicare con il file
    //Siccome il file dobbiamo aprirlo solo in scrittura, allora andiamo a definire 

    //In questo modo abbiamo specificato un oggetto di tipo ofstream, che va ad aprire un file chiamato "prova.txt", che se non esiste
    //viene creato dal sistema operativo nella stessa cartella in cui si trova il nostro programma, in modalità di scrittura!
    //NOTA: La modalità di apertura che abbiamo specificato consente solo di andare a scrivere nel nostro file, eliminando tutti i contenuti che esso 
    //aveva al suo interno!
    
    //Per poter scrivere il file andandolo ad aggiornare, possiamo aprirlo in modalità "append", definendo ios::app
    //In questo modo andremo sempre a scrivere alla fine del file di testo!
    ofstream fileoutput{"prova.txt", ios::out};

    //Oltre che andare ad inserire tutto all'interno della stessa riga, potevamo anche definire l'oggetto di tipo ofstream e poi aprirlo: 
    /*  ofstream fileoutput;
        
        fileoutput.open{"prova.txt", ios::out}; 

        Andando quindi a separare la definizione dell'oggetto e l'apertura del file!   
    
    */

    //Dunque, tramite l'oggetto di tipo ofstream, possiamo andare a gestire il nostro file 
    //La prima cosa è controllare che esso si sia aperto in maniera corretta!

    //Andiamo ad usare l'overload dell'operatore booleano ! per verificare se il file si sia aperto o meno!
    if(!fileoutput){ //Overload dell'operatore! già specificato dall'oggetto ofstream!
        //cerr che viene specificato qui non è altro che il flusso dati verso lo schermo che viene utilizzato per trasmettere dei messaggi di errore!
        //è contenuto all'interno della libreria standard come anche il flusso dati cout!
        std::cerr<<"Il file non può essere aperto!"<<std::endl;

        //Se abbiamo questo errore, allora usiamo la funzione che termina il programma 
        exit(EXIT_FAILURE); //Così il programma termina normalmente!
    }

    cout<<"Si prefa di inserire: \n";
    cout<<"NumeroConto Nome Cognome Bilancio\n";

    while(cin>>conto >>nome >>cognome >>saldo){
        //Salvo il valore all'interno del file!

        //Dunque, per andare a scrivere all'interno del file usiamo l'operatore che già si è visto "<<"!
        fileoutput<<conto<<" "<<nome<<" "<<cognome<<" "<<saldo<<std::endl;

    }


    //Quando poi abbiamo aperto il file, come definito sopra, possiamo andare anche a chiuderlo, in modo da non creare un programma che genera senza 
    //alcun controllo un numero enorme di file!

    //Per fare ciò andiamo ad usare la funzione .close, definita dall'oggetto di tipo ofstream
    fileoutput.close();


}