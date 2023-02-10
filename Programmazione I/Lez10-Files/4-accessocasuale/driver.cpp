//Vado a definire il programma che ha la capacità di sfruttare la clase come definita prima per scriver in maniera random all'interno di un file
#include "accounts.h"
#include <string>
#include <iostream>
#include <fstream>

using std::cin; 
using std::cout; 
using std::endl;
using std::fstream;

void mostro(std::ostream&,  Account&);

int main(){
    //Andiamoa a salvare tutti gli elementi all'interno di un file denominato.dat che serve per inserire gli elementi in formato binario!

    //In particolare, per salvare gli elementi all'interno di un file, dobbiamo definre la modalità di apertura come "binary"
    //solo in questo modo possiamo andare a salvare delle definizione in modalità a lunghezza fissa
    fstream files;
    files.open("client.dat", std::ios::out | std::ios::in | std::ios::binary);
                                            //Usiamo l'operatore or bitwise, che serve per definire l'operazione con cui andiamo ad aprire il file 


    if(!files){
        std::cerr<<"Non riesco ad aprire il file in lettura oh!\n";
        exit(EXIT_FAILURE);
    }


    int number; 
    string nome, cognome;
    double saldo; 

    //Faccio in modo che, il numero di conto serve per inserire il numero di conto 

    cout<<"Inserisci il numero di conto da 1 a 100 (Lo 0 serve per terminare)!\n";
    cin>>number;

    while(number>0 && number<=100){
        cout<<"Inserisci: Nome, Cognome, saldo del conto\n";
        cin>>nome;
        cin>>cognome;
        cin>>saldo; 

        //Andiamo a definire un oggetto account, inizializzato con i valori che abbiamo definito!
        Account salvo{number, nome, cognome, saldo};

        //Spostiamo il puntatore all'interno del file, per trovare la posizione in cui andare a salvare il nostro acocunt, usando la funzione
        //seekp
        files.seekp((salvo.getNum()-1)*sizeof(Account));

        //Ora dobbiamo però scriver il file usando dei byte e non dei caratteri, in questo modo, per ogni dato che andiamo ad inserire abbiamo un tipo 
        //di scrittura costante
        
        //Usiamo quindi la funzione write, che ci permette di scrivere il contenuto del file come una sequenza di byte
        files.write(reinterpret_cast<const char*>(&salvo), sizeof(Account));
        //In questo modo dobbiamo usare per forza la funzione di reinterpret_cast, in modo che gli stiamo dicendo che vogliamo trattare
        //il dato non ha un tipo particolare 

        //Senza definire questo tipo di casting, si genera un errore di compilazione

        cout<<"Inserisci un numero di conto: \n";
        cin>>number;


    }
    

    files.close();

    //Apro il file in lettura
    files.open("client.dat", std::ios::in | std::ios::binary);

    if(!files){
        std::cerr<<"Non riesco ad aprire il file in lettura!\n";
        exit(EXIT_FAILURE);
    }

    Account leggo;

    //usiamo sempre la funzione read, in modo da andare a leggere il primo valore dal file
    //La funzione legge in memoria, in base al numero di byte della classe che ho definito e poi lo inserisce all'interno della variabie oggetto leggo
    files.read(reinterpret_cast<char*>(&leggo), sizeof(leggo));

    while(files){

        if(leggo.getNum()!=0){
            //Funzione che ha il compito di andare a mostrare a video il file
            mostro(cout, leggo);
        }

        //vado ad aggiornare l'oggetto spostando il puntatore!
        files.read(reinterpret_cast<char*>(&leggo), sizeof(leggo));
    
    }

    files.close();


    //Vado a salvare gli elementi dal file in binario all'interno di un file di testo
    std::ofstream salvo{"salvataggio.txt", std::ios::out};

    if(!salvo){
        std::cerr<<"Non posso aprire il file in cui copiare i dati"<<endl;
        exit(EXIT_FAILURE);
    }
    
    //Apro il file che mi serve per prelevare 
    files.open("client.dat", std::ios::in);

    if(!files){
        std::cerr<<"Non riesco ad aprire il file"<<endl;
        exit(EXIT_FAILURE);
    }

    //uso la funzione read per andare a leggere il contenuto del file
    files.read(reinterpret_cast<char*>(&leggo), sizeof(leggo));

    while(files){

        //Devo per forza usare le funzioni membro per andare a salvare gli elementi all'interno del files
        //Poichè la funzione read, legge il file in modalità binario!
        salvo<<leggo.getNum()<<" "<<leggo.getName()<<" "<<leggo.getLast()<<" "<<leggo.getBal()<<endl;

        files.read(reinterpret_cast<char*>(&leggo), sizeof(leggo));

    }


    files.close();
    salvo.close();

}






void mostro(std::ostream& output, Account& elemento){
    output<<"Numero di conto: "<<elemento.getNum()<<";\nNome:  "<<elemento.getName()<<"\nCognome: "<<elemento.getLast()<<"\nSaldo: "<<elemento.getBal()<<"\n";
    cout<<"------------------------------\n";
}