#include "box.h"


//Specifica delle funzioni della classe box
Box::Box(const std::string& i, const int w , const int v , const bool p): box_id{i}, perishable{p}{
    setWeight(w);
    setValue(v);    
}

void Box::setId(const std::string& i){
    box_id=i;
}

void Box::setWeight(const int w){
    if(w<0){
        std::cerr<<"Guarda che il peso non può essere negativo\n";
    }

    else{
        weight=w;
    }

}

void Box::setValue(const int v){
    if(v<0){
        std::cerr<<"Guarda che il prezzo non può essere negativo\n";
    }

    else{
        value=v;
    }
}

void Box::setPerish(const bool p){
    perishable=p;
}

std::string Box::getId() const{
    return box_id;
}

int Box::getWeight() const{
    return weight;
}

int Box::getValue() const{
    return value;
}

bool Box::perish() const{
    return perishable;
}

std::string Box::toString(){ 
    std::ostringstream out; 

    out<<"Pack Id: "<<getId()<<"\nPack Weight: "<<getWeight()<<" Kg"
        <<" \nValue: "<<getValue()<<"€\n"<<"Perishable? "<<((perish()==true) ? "yes":"no")<<std::endl;

    return out.str();
    
}