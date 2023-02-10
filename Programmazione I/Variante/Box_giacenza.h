//Specifica della classe che contiene anche l'id del container in cui è contenuto il pacco!
#include "Box.h"

#ifndef BOX_GIACENZA_H
#define BOX_GIACENZA_H

class BoxGiacenza: public Box{
    private: 
        int id_container; 
    public:
        BoxGiacenza(const int& box_id=0, const double& weight=0.0, const double& value=0.0, bool perish=true, const int& id=0) : 
            Box(box_id, weight, value, perish), id_container{id} {};
};

#endif