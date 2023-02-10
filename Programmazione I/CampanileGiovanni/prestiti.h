//Specifica della classe che deve contenere un riferimento al libro che ho prestato!

#include "book.h"
#include "data.h"


#ifndef PRESTITI_H
#define PRESTITI_H

class Prestato{

    private: 
        //La classe contiene l'indicazione del libro prestato! 
        //Lo definiamo come un puntatore al libro!
        //Un puntatore costante poichè la classe prestito non deve in alcun modo andare a modificare il libro prestato!
        const Book* prestato;

        //Inserimento della data di presito
        Data prestito;
        Data restituzione; //La data di restituzione non sarà modificabile, necessariamente 30 giorni dalla data di prestito!

        //La dichiarazione della funzione per l'impostazione della data di riferiment la lascio come privata poichè viene sfruttata dalle funzioni membro una volta che ho definito una data di prestito
        void setDataRestituzione(const Data&);

    public: 
        Prestato(); 

        ~Prestato();

        void setLibro(const Book&); 
        std::string getLibro();

        std::string getTitolo();

        //Specifica delle varie funzioni!
        void setPrestito(int, int, int);
        std::string getPrestito();

        std::string getDataRestituzione();

        //Funzione che ha il compito di andare a calcolare il costo degli elementi che sono stati prestati
        //In base alla data odierna chiesta dal driver al momento dell'esecuzione! e alla data di restituzione!
        int calcoloMulta(Data&);

        //Definizione degli operatori di confronto per mantenere la lista ordinata!
        bool operator<(const Data&); 

        bool operator>(const Data&);

        Data& scadenza(){
            return restituzione;
        }
        

};

#endif