//Andiamo a definire un programma che ha la possibilità di andare a leggere il contenuto di un file di testo!
#include <iostream>
#include <string>

#include <fstream>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ios;
using std::ifstream; //Classe che ci occorre per andare a aprire il file in lettura!

void mostrocontenuto(int, string&, string&, double);



int main(){
    string nome, cognome;
    int numero; 
    double saldo; 

    ifstream leggo;//Usando ios::in, andiamo a definire che la modalità di apertura del file è per la lettura!

    leggo.open("prova.txt", ios::in);

    //Sfruttiamo il ciclo while per andare ad inserire il contenuto del file di testo all'interno delle variabili che abbiamo definito
    //Ovviamente il while continua fino a che non si raggiunge il carattere di end of file!
    //Per leggere il contenuto del file usiamo sempre l'operatore ">>" che usiamo anche con il normale flusso dati cin!
    while(leggo>>numero >>nome >>cognome >>saldo ){
        mostrocontenuto(numero, nome, cognome, saldo);
    }

    //Nel nostro caso stiamo leggendo in modo sequenziale il file, così facendo andiamo a leggere e mostrare a video ogni riga del nostro file, partendo dalla prima
    //fino a che non si raggiunge il carattere che segna "end of file"!
    //Questo perchè il nostro programma "vede" il file come una sequena di byte, in base al tipo di informazioni che noi adiamo  a definire al suo interno!
    //E alla fine di questo flusso di byte viene indicato il termine che indica, appunto, l'end of file!
    leggo.close();
    
}

void mostrocontenuto(int numero, string& nome, string& cognome, double saldo){
    cout<<"Numero: "<<numero<<"\n"<<"Intestato a: "<<nome<<" "<<cognome<<"\n"<<"Saldo: "<<saldo<<"€\n";
    cout<<"------------------------\n";
}