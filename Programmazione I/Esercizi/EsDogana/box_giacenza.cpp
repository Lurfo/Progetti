#include "box_giacenza.h"

Giacenza::Giacenza(const std::string& i, const int w , const int v , const bool p, const std::string& id_con)
: Box(i,w,v,p), id_container{id_con}{}


void Giacenza::setIdCont(const std::string& id){
    id_container=id;
}

std::string Giacenza::getIdCont() const{
    return id_container;
}

std::string Giacenza::toString(){
    std::ostringstream out; 

    out<<"Pacco contenuto nel container: "<<getIdCont()<<"\nPack Id: "<<Box::getId()<<"\nPack Weight: "<<Box::getWeight()<<" Kg"
        <<" \nValue: "<<Box::getValue()<<"€\n"<<"Perishable? "<<((Box::perish()==true) ? "yes":"no")<<std::endl; 
    
    return out.str();
}
