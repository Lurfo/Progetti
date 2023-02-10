#include "box.h"


//Specifica delle funzioni della classe box
//Modifico il costruttore in modo da andare ad inizializzare la variabile!
Box::Box(const std::string& i, const int w , const int v , const bool p): box_id{i}, perishable{p}, scadenza{}{
    setWeight(w);
    setValue(v);    
}

//Specifica della funzione che restituisce la data!
std::string Box::getData(){

    return scadenza.getData();
}

void Box::setData(int g, int m, int a){
    scadenza.setData(g, m, a);
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

    if(perishable){
       
        int giorno; 
        int mese; 
        int anno;

        std::cout<<"Imposto il valore della data!\n"; 

        std::cout<<"Dimmi il giorno\n"; 
            std::cin>>giorno; 
        
        std::cout<<"Dimmi il mese\n"; 
            std::cin>>mese; 
        
        std::cout<<"Dimmi l'anno\n";
            std::cin>>anno; 
        
        scadenza.setData(giorno, mese, anno);
    
    }


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
        <<" \nValue: "<<getValue()<<"€\n"<<"Perishable? "<<((perish()==true) ? "yes, ":"no\n");
        
        if(perishable){
        
        out<<"Data di scadenza: "<<scadenza.getData()<<"\n";

        }

    return out.str();
    
}