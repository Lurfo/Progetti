//Specifica della classe che contiene anche l'id del container in cui è contenuto il pacco!
#include "box.h"

#ifndef BOX_GIACENZA_H
#define BOX_GIACENZA_H

class Giacenza: public Box{
    private: 
        std::string id_container; 
    
    public: 
        Giacenza(const std::string& =" ", const int =0, const int =0, const bool =false, const std::string& =" ");

        void setIdCont(const std::string&); 

        std::string getIdCont() const;

        virtual std::string toString() override;

};



#endif