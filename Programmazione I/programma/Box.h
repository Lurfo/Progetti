#ifndef BOX_H
#define BOX_H
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <list>
using std::string;
using std::vector;
using std::cout; 
using std::list;

   class Box{
    friend class Container;
    public:
   
    Box(int b_i=0, double wgh=0, int val=0, int prsh=0) : box_id{b_i} , weigh{wgh} , value{val} , perishable{prsh}
    {
        //empty body
    }

    virtual string toString()
    {
        std::ostringstream out;
        out<<"Box del container: "<<"\n";
        out<<"box_id: "<<"\n";
        out<<box_id<<"\n";
        out<<"weigh: "<<"\n";
        out<<weigh<<"\n";
        out<<"value: "<<"\n";
        out<<value<<"\n";
        out<<"perishable: "<<"\n";
        out<<perishable<<"\n";
        return out.str();
    }

        int getPerishable() const 
        {
            return perishable;
        }

        private:
        int box_id;
        double weigh;
        int value;
        int perishable;
        list<Box> boxlist;
    };

#endif