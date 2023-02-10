//definizione della classe box

#include <string>
#include <sstream>


#ifndef BOX_H
#define BOX_H

class Box{
    private: 
        int code; //Codice che ci permette di accedere all'inseieme dei pacchi e ricercare il nostro pacco

        char name[15]; //Definsco anche un nome per il pacco, la cosa impostante è che siccome ho a che fare con un file binario in accesso sequenziale devo necessariamente utilizzare un
        //valore predefinito per il file, in questo modo ogni pacco occupa lo stesso numero di byte!

        int qnt; //Indica quanti di questi pacchi sono presenti all'interno del magazzino

        double price; //Usiamo un double per definire il prezzo di ogni pacco!

    public: 
        //Definizione del costruttore con argomenti di default, in questo modo si può escegliere quale tipo di elementi si possono visualizzare o meno!
        //Possiamo andare ad usare all'interno del costruttore, una variabile di tipo string, in questo modo però ho che se inserisco un nome, con una lunchezza
        //maggiore di 15 caratteri, vengono copiati all'interno della variabile nome solo i primi 15
        Box(int=0, const std::string& =" " , int =0, double =0.0);

        //Definizione del distruttore
        ~Box();

        //Funzioni get e set
        void setCode(int); 
        int getCode() const; 

        void setName(const std::string&);
        std::string getName() const; 

        void setQuant(int); 
        int getQuant() const;

        void setPrice(double); 
        double getPrice() const;

        std::string toString() const;


};




#endif 