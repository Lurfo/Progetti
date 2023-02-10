//Definizione della classe abstract sull quale andiamo poi a specificare le altre 

#include <string>
#include <vector>
using std::string;

#ifndef PUBLICATION_H
#define PUBLICATION_H
 
class Publication{
    private: 

        std::string title;//Titolo della pubblicazione
        std::vector<std::string> autori; //Vettore contenete gli autori della pubblicazione!
        int anno;  //Devinizione dell'anno di pubblicazione!

    public: 

        //Costruttore della classe che prende in ingresso tutte le variabili necessarie!
        Publication(const std::string&, const string&, int); //Inserimento degli autori che viene fatto quando andiamo a chiamare il costruttore!
        //Definisco un distruttore di default in modo che la classe sia una funzione pure virtual!
        ~Publication()=default;
        
        //setFunctions!
        void setAnno(int);
        void setTitolo(const string&);
        void setAuthors(const string&);

        //getFunctions!
        string getTitle();
        int getYear();
        string getAuthors();

        //Definizione della funzione che la mette sottoforma di stringa non conviene porla in modalità pure virtual, in modo che possiamo riusarla!
        //La definisco però virtual in modo che posso andare a riscriverla!
        virtual string toString();

        //Override dell'operatore < per le pubblicazioni!
        //Tale operazione ci permette di effettuare l'operazione < sulle operazioni!
        bool operator<(const Publication& sec); 



};



#endif