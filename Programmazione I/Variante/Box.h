#ifndef BOX_H
#define BOX_H
#include <iostream>

class Box{ 
    public:
        Box(const int& id=0, const double& heaviness=0.0, const double& price=0.0, bool perish=true): box_id{id}, weight{heaviness}, 
            value{price}, perishable{perish} {};
        double getWeight() {
            return weight;
        }
        double getValue() {
            return value;
        }
        void setPerishable(bool p){
            perishable = p;
        }
        bool getPerish(){
            return perishable;
        }
        int getId(){
            return box_id;
        }
    private:
        int box_id;
        double weight;
        double value;
        bool perishable;
};

#endif