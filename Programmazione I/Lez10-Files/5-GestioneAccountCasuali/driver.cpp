//Vado a creare un programma in grado di gestire una rubrica 
#include <iostream>
#include "accounts.h"
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using std::ios;
using std::cout;
using std::cin;
using std::endl;
using std::fstream; //In modo che il file che noi andiamo a definire possa essere aperto sia in lettura che in scrittura 
 

enum class Choice{PRINT=1, UPDATE, NEW, DELETE, END};

Choice scelgo();
void vedo(fstream&);
void salvataggiosufile(fstream&);
void aggiornaEl(fstream&);
void aggiungiEl(fstream&);
void eliminaEl(fstream&);
void mostro(std::ostream&, const Account&);
int numeroAccount(const char* const);

int main(){

    fstream InOutFile{"account.dat", ios::out | ios::in | ios::binary};

    if(!InOutFile){
        std::cerr<<"Non riesco ad aprire il file iniziale"<<std::endl;
        exit(EXIT_FAILURE);
    }

    Choice choise;

    while((choise=scelgo())!=Choice::END){
        switch(choise){
            case Choice::PRINT:
                salvataggiosufile(InOutFile);
                break;
            
            case Choice::UPDATE:
                aggiornaEl(InOutFile);
                break;

            case Choice::NEW:
                aggiungiEl(InOutFile);
                break;

            case Choice::DELETE:
                eliminaEl(InOutFile);
                break;

            default:
                std::cerr<<"Scelta, sbaliata!, devi scegliere tra 1 e 5!"<<endl;
                break;

        }
    }


}

Choice scelgo(){
    int scelt;
    cout<<"Scegli una tra le seguenti opzioni: \n";
    cout<<"[1] - Salva gli elementi in un file di testo!\n";
    cout<<"[2] - Aggiornare gli elementi\n";
    cout<<"[3] - Aggiungi elemento\n";
    cout<<"[4] - Elimina elemento\n";
    cout<<"[5] - Chiudi il programma\n";

    cin>>scelt;

    //Faccimo un cast 
    return static_cast<Choice>(scelt);

}

void mostro(std::ostream& output, const Account& conto){
    output<<conto.getNum()<<std::setw(12)<<conto.getName()<<std::setw(12)<<conto.getLast()<<std::setw(12)<<conto.getBal()<<endl;
}

int numeroAccount(const char* const msg){

    int numero;
    do{
    cout<<msg<<"\n";
    cin>>numero; 

    if(numero<1 && numero>100){
        cout<<"Il valore che mi hai detto non è corretto\n";
        cout<<"Deve essere compreso tra 1-100!\n";
    }

    }while(numero<1 && numero>100);

    cout<<"Hai inserito il numero: "<<numero<<"\n";

    return numero; 
}

void vedo(fstream& files){

    cout<<"TI mostro gli elementi contenuti nel file, così mi dici quali vuoi modificare!\n";

    Account conto;

    files.seekg(0);

    files.read(reinterpret_cast<char*>(&conto), sizeof(Account));

    while(files){
     
        if(conto.getNum()!=0){
            mostro(cout, conto);
        }

        files.read(reinterpret_cast<char*>(&conto), sizeof(Account));
    }

    files.seekg(0, std::ios::beg);


}

void salvataggiosufile(fstream& salvo){

    std::ofstream salvataggio{"salvo.txt", std::ios::out};

    if(!salvataggio){
        std::cerr<<"Guarda che non posso aprire il file"<<endl;
        exit(EXIT_FAILURE);
    }

    salvataggio<<"Numero"<<std::setw(12)<<"Nome"<<std::setw(12)<<"Cognome"<<std::setw(12)<<"Bilancio"<<endl;

    //Sposto il puntatore all'inizio del file, poicè può essere che si trovi in una situazione differente  
    salvo.seekg(0);

    Account conto; 

    salvo.read(reinterpret_cast<char*>(&conto), sizeof(Account));

    while(!salvo.eof()){

        if(conto.getNum()!=0){
            mostro(salvataggio, conto);
        }

        salvo.read(reinterpret_cast<char*>(&conto), sizeof(Account));

    }


}

void aggiornaEl(fstream& files){

    vedo(files);

    int numeroconto{numeroAccount("Dimmi il numero di Account che vuoi modificare!\n")};

    //Vado a spostare il puntare all'interno del file alla posizione che mi occorre!
    files.seekg((numeroconto-1)*sizeof(Account));

    Account elemento; 

    //Inserisco all'interno dell'account il valore puntato dal puntatore del file
    files.read(reinterpret_cast< char*>(&elemento), sizeof(Account));

    if(elemento.getNum()!=0){
      
        cout<<"Hai selezionato l'elemento: \n";
        mostro(cout, elemento);
    

        cout<<"Inserisci il prelievo o il depsito\n";
        double transazione; 
        cin>>transazione;

        double vecchio=elemento.getBal();
        elemento.setBal(vecchio+transazione);
        cout<<"Hai effettuato il cambiamento:\n"; 
        mostro(cout, elemento);

        //Riposiziono il puntatore alla stessa posizione in cui si trovava quando ho prelevato il dato
        //Mi serve sfruttare la funzione seekp, in modo che il puntatore sia pronto per inserire il dato in quella posizione
        files.seekp((numeroconto-1)*sizeof(Account));

        files.write(reinterpret_cast<const char*>(&elemento), sizeof(Account));

        files.seekp(0, std::ios::beg);

    }

    else{

        std::cerr<<"Il numero di account: "<<numeroconto<<" non ha informazioni!"<<endl;

    }

}

void aggiungiEl(fstream& elemento){
    int numero{numeroAccount("Inserisci il numero di conto")};
    cout<<"Hai inserito il numero: "<<numero<<"\n";

    //Sposto il puntatore nel punto definito
    elemento.seekg((numero-1)*sizeof(Account));

    Account conto;
    //Inserisco l'elemento puntato dal vettore all'interno della classe!
    elemento.read(reinterpret_cast< char*>(&conto), sizeof(Account));

    cout<<conto.getNum()<<endl;

    //Verifico che effettivamente la classe non abbia già un elemento in quella posizione!
    if(conto.getNum()==0){
        string nome; 
        string cognome; 
        double saldo; 

        cout<<"Inserisci il Nome, Cognome, Saldo\n";
        cin>>nome;
        cin>>cognome; 
        cin>>saldo;

        conto.setNum(numero);
        conto.setName(nome);
        conto.setLast(cognome);
        conto.setBal(saldo);

        cout<<"Numero: "<<conto.getNum()<<endl;
        cout<<"Nome: "<<conto.getName()<<endl;
        cout<<"Cognome: "<<conto.getLast()<<endl;
        cout<<"Saldo: "<<conto.getBal()<<endl;

        //Vado quindi ad inserire la classe all'interno del file 
        elemento.seekp((numero-1) * sizeof(Account));

        //Inserisco la classe all'interno del file
        elemento.write(reinterpret_cast<const char *>(&conto), sizeof(Account));
    }

    else {
        std::cerr<<"Il numero di conto inserito è già occupato!\n";
        cout<<"L'elemento che occupa la posizione inserità è ugale a:\n";

        elemento.seekg((numero-1)*sizeof(Account));

        elemento.read(reinterpret_cast<char*>(&conto), sizeof(Account));
        mostro(cout, conto);

    }
}

void eliminaEl(fstream& files){
    int numero{numeroAccount("Dimmi il numero di conto che devo verificare!\n")};
    //Sposto il puntatore che fino all'account desiderato
    files.seekg((numero-1)*sizeof(Account));

    Account salvo; 
    //Copio i dati contenuti nel file all'interno di salvo!

    files.read(reinterpret_cast<char*>(&salvo), sizeof(Account));

    if(salvo.getNum()!=0){

        //Creo una nuova classe Account, che lascio vuota per andare ad inserirla all'interno della lista 
        Account vuoto; //Classe che resta vuota per essere inserita all'interno della lista 

        //Sposto il puntatore di inserimento alla posizione dove devo inserire la classe 
        files.seekp((numero-1)*sizeof(Account));

        //Inserisco quindi la variabile all'interno del file
        files.write(reinterpret_cast<char*>(&vuoto), sizeof(Account));

        cout<<"Account: "<<numero<<" eliminato con successo!\n";



    }

    else{
        std::cerr<<"Il numero che hai inserito corrisponde già ad un account vuoto!\n";
    }


}

