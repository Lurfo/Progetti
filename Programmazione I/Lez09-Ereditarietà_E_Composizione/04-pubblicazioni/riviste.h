//Definizione della classe di publicazioni di articli su riviste!
#include "publication.h"

#ifndef RIVISTE_H
#define RIVISTE_H

class Riviste: public Publication{

    static int numRiviste;

    private:
        string nome;
        int num;
        int pag[2]; //Semplice array che tiene conto del numero delle pagine che contiene la rivista!

    public: 
        //Definizione del costruttore!
        Riviste(const string&, int, const string&, int, int, int);

        //Definizione del distruttore!
        virtual ~Riviste();

        void setPages(int, int);
        string getPages();

        void setNum(int);
        int getNum();

        void setName(string&);
        string getName();

        virtual string toString() override;





};


#endif