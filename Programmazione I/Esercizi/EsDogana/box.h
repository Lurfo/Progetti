//Specifica della classe Box, da inserire all'interno della lista 
#include <string>
#include <sstream>
#include <iostream>
#ifndef BOX_H
#define BOX_H

class Box{

    private: 
        std::string box_id;
        int weight; 
        int value; 
        bool perishable;

    public: 
        Box(const std::string& =" ", const int =0, const int =0, const bool =false);

        void setId(const std::string&);
        void setWeight(const int); 
        void setValue(const int); 
        void setPerish(const bool);

        std::string getId() const;
        int getWeight() const;
        int getValue() const; 
        bool perish() const;

        virtual std::string toString();
};
#endif