//Usando uno speciale vettore che viene utilizzato dal nostro programma è possibile andare ad eseguire anche la copia degli elementi che sono contenuti 
//All'interno di un file per poterli inserire all'interno di un altro!

#include <iostream>
#include <fstream>
#include <string>

using std::ifstream;
using std::ofstream;
using std::ios;

int main(){
    
    char* buffer; //Dichiaro un puntatore a char che rappresenta la mia memoria "buffer", nella quale inserisco il testo che devo copiare 
    int lunghezza=0;

    //Specifico tutto il percorso che ho definito per poter trovare il mio file all'interno del sistema, in questo caso prendo un file che è 
    //ho creato dalla cartella 1!
    ifstream open{"prova.txt"};

    //check per controllare che il file si sia aperto
    if(!open){
        std::cerr<<"Non posso aprire il file!"<<std::endl;
        exit(EXIT_FAILURE);
    }

    //Uso due funzioni particolari e molto importanti che sono associati ad un file che servono per andare a definire 
    //la posizione del vettore che il c++ utilizza per leggere il file!
    //Questo perchè la lettura sequenziale di un file viene fatta proprio sfruttando questo puntatore che si "muove" dall'inizio 
    //del nostro file fino a che non raggiunge il carattere che specifica l'EoF!!!!

    //Andiamo a posizionare il file alla fine del file per verificare la lunghezza di questo 
    open.seekg(0, ios::end);
    //Per ferifivare la lunghezza del file, allora uso la funzione tellg
    lunghezza=open.tellg();

    //Dopo aver trovato la lunghezza del file, riporto il puntatore alla parte iniziale 
    open.seekg(0, ios::beg);

    //Definisco quindi che il puntatore a char, punta ad una zona di memoria che contiene un array di char con lunghezza pari a quella del file
    buffer=new char[lunghezza];

    //Uso una funzione molto importante, che fa la copia degli elementi per salvare gli elementi del file all'interno del buffer che ho definito 
    open.read(buffer, lunghezza);

    //Quando raggiunge l'EoF, allora la funzione conclude il suo lavoro

    open.close();

    //Andiamo quindi ad effettuare la copia degli elementi del buffer all'interno del nostro file nuovo

    ofstream provo{"nuovo.txt"};

    if(!provo){
        std::cerr<<"Non posso aprire il file!"<<std::endl;
        exit(EXIT_FAILURE);
    }

    //Usiamo un'altra funzione, .write, che serve per copiare gli elementi dal buffer che abbiamo definto, all'interno del file!
    provo.write(buffer, lunghezza);

    //Dopo aver finito la copia, posso eliminar gli elementi che sono contenuti all'interno del buffer
    delete[] buffer;

}