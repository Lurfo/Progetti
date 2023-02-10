//Definizione della classe che memorizza l'atto di un convegno!
#include "publication.h"

#ifndef CONVEGNO_H
#define CONVEGNO_H

class Convegno: public Publication{
    static int numConvegno;

    private:
        string luogo; 
        int pagina;

    public:
        Convegno(const string&, int, const string&, int);
        ~Convegno();

        void setLuogo(string&);
        string getLuogo();

        void setPagina(int);
        int getPagina();

        virtual string toString() override;
        
        



};


#endif