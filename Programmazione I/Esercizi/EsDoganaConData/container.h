//Specifica della classe conteiner!
//Devo considerare che all'interno del container, devo andare ad inserire una lista che va a 
//raggruppare i singoli pacchi che sono contenuti in esso!
#include <list>
#include <queue>
#include "box.h"

#ifndef CONTAINER_H
#define CONTAINER_H

class Container{

    friend void clear(std::queue<Container*>&, std::list<Box*>&);

    private: 
        std::string container_id; 
        std::string state_origin; 
        std::string id_carrier;

    public:
        //Al posto della lista andiamo ad inserira una coda a priorità in cui sono contenuti i pacchi!
        std::priority_queue<Box*> pac1;
        std::list<Box*> pac;

    public:
        //Definizione del costruttore della classe 
        Container(const std::string& =" ", const std::string& =" Non definito", const std::string& ="Non Disponibile");

        Container& operator=(const Container&);

        void setIdCont(const std::string&);
        void setState(const std::string&);
        void setCarrier(const std::string&);

        void addPackage(const std::string&, int, int, int); 

        

        //Funzioni che riguardano i dati del conatainer
        std::string getIdCont() const; 
        std::string getState() const;
        std::string getCarrier() const; 

        //Funzioni che riguardano i dati dei pacchi in esso contenuti
        
        int getNumPacks() const;
        
        std::string getPackId(int) const; 
        int getPackW(int) const; 
        int getPackV(int) const; 
        int getPackP(int) const;

        std::string getPackageList() const;

        int getTotalWeight();
        int getTotalValue();

        std::string ToString();

};




#endif