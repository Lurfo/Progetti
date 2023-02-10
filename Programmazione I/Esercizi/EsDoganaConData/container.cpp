//Specifica degli elementi che appartengono alla classe container!
#include "container.h"

//Costruttore!
Container::Container(const std::string& id, const std::string& orig, const std::string& car)
:container_id{id}, state_origin{orig}, id_carrier{car}{
    //Vado ad utilizzare il costruttore base della lista!
    pac;

}

Container& Container::operator=(const Container& elm){
    container_id=elm.container_id;
    state_origin=elm.state_origin;
    id_carrier=elm.id_carrier;

    //Devo fare anche la copia della lista!
    pac=elm.pac;

    return *this;

}

void Container::setIdCont(const std::string& id){
    container_id=id;
}

void Container::setState(const std::string& st){
    state_origin=st;
}

void Container::setCarrier(const std::string& carr){
    id_carrier=carr;
    
} 

void Container::addPackage(const std::string& id, int w, int v, int p){
    Box* nuovo =new Box(id, w, v); 

    if(p==1){
        nuovo->setPerish(true);
    }

    else{
        nuovo->setPerish(false);
    }

    pac.push_front(nuovo); //Vado ad inserire il mio puntatore all'interno della lista!
}

std::string Container::getIdCont() const{
    return container_id;
}

std::string Container::getState() const{
    return  state_origin; 
}

std::string Container::getCarrier() const{
    return id_carrier;


}

int Container::getNumPacks() const{
    return pac.size();
}

std::string Container::getPackId(int pos) const{

    std::list<Box*>::const_iterator p=pac.begin();
    int i{0};
    for(p; p!=pac.end() && i<pos; p++){
        i++;
    }

    return (*p)->getId();
}

int Container::getPackW(int pos) const{
    std::list<Box*>::const_iterator p=pac.begin();
    int i{0};
    for(p; p!=pac.end() && i<pos; p++, i++){
        i++;
    }

    return (*p)->getWeight();
}

int Container::getPackV(int pos) const{
    std::list<Box*>::const_iterator p=pac.begin();
    int i{0};
    for(p; p!=pac.end() && i<pos; p++){
        i++;
    }

    return (*p)->getValue();
}

int Container::getPackP(int pos) const{
   
    std::list<Box*>::const_iterator p=pac.begin();
   
    int i{0};
    for(p; p!=pac.end() && i<pos; p++){
        i++;
    }

    if((*p)->perish()){
        return 1;
    }

    else{
        return 0;
    }
    

}

std::string Container::getPackageList() const{
  
    std::ostringstream out;
        
    int num{1};        
      
    for(std::list<Box*>::const_iterator p=pac.begin(); p!=pac.end(); ++p, num++){
        out<<"Pacco numero: "<<num<<"\n";
        out<<(*p)->toString();
    }

    return out.str();

}


int Container::getTotalWeight(){
    int somma{0};
    
    for(std::list<Box*>::const_iterator p=pac.begin(); p!=pac.end(); ++p){
        somma+=(*p)->getWeight();
    }

    return somma;
}

int Container::getTotalValue(){
    int somma{0};

    
    for(std::list<Box*>::const_iterator p=pac.begin(); p!=pac.end(); ++p){
      
        somma+=(*p)->getValue();
    }

    return somma;

}

std::string Container::ToString(){
    std::ostringstream out; 

    out<<"Container id: "<<getIdCont()<<", Proveniente da: "<<getState()<<", Corriere: "<<getCarrier()
    <<";\nNel container sono contenuti: "<<getNumPacks()<<" elementi\n"<<getPackageList()<<"\nPeso totale: "<<getTotalWeight()
    <<"Kg\nValore totale: "<<getTotalValue()<<"€\n";

    return out.str();
}
