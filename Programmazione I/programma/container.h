#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <list>
#include <vector>
#include "Box.h"
using std::string;
using std::list;
using std::cout;
using std::vector;
using std::queue; 
int sogliavalue=5;
class Container: public Box
{
    public:
    Container(int idco, string so, string idcr, int nbox, double b_i, double wgh, int val, int prsh) : id_container{idco} ,state_orig{so}, id_carrier{idcr} , n_box{nbox} , Box(b_i,wgh,val,prsh)
    {
        //empty body
    }
    
    
    virtual string toString ()
    {
        std::ostringstream out;
        
        out<<"id_container:\n";
        out<<id_container<<"\n";
        out<<"state_orig:\n";
        out<<state_orig<<"\n";
        out<<"id_carrier:\n";
        out<<id_carrier<<"\n";
        out<<"n_box: "<<"\n";
        for(list<int>::const_iterator iterator= n_box.begin(); iterator !=n_box.end(); ++iterator)
        {
            out <<*iterator<<"\n";
        }
       out<<"----------------"<<std::endl;
        
        return out.str();
    }

    void addBox(Box B)
    {
        boxlist.push_front(B);
    }

    double total_weight() 
    {
        double sumweigh=0;

      for(list<Box>::const_iterator iterator= boxlist.begin(); iterator !=boxlist.end(); ++iterator)
        {
            sumweigh+= iterator-> weigh;
        }

        return sumweigh;
    }
    int total_value()  
    {
        int sumvalue=0;

      for(list<Box>::const_iterator iterator= boxlist.begin(); iterator !=boxlist.end(); ++iterator)
        {
            sumvalue+= iterator-> value;
        }

        return sumvalue;
    }

    void addBoxGiacenza(Box B)
    {
        BoxGiacenza.push_front(&B);
    }

    void pacchiGiacenza()
    {   
        for(list<Box>::iterator iterator= boxlist.begin(); iterator !=boxlist.end(); ++iterator)
        {
            if(iterator->getPerishable()==1)
            {   
                Box* prova= new Box((*iterator).box_id, (*iterator).weigh, (*iterator).value, (*iterator).getPerishable());

                BoxGiacenza.push_front(prova);
            }
        }
        for(list<Box*>::iterator iterator= BoxGiacenza.begin(); iterator!= BoxGiacenza.end(); ++iterator)
        {
            cout<<"Lista pacchi in giacenza: "<<"\n";
            cout<<"Numero container del pacco in giacenza: "<<id_container<<"\n";
            cout<<(*iterator)->toString()<<"\n";
        }

        cout<<"Lascio la funzione giacenza, ci sono: "<<BoxGiacenza.size()<<" elementi\n";
    }

    void clearance(queue<Container> coda, Container container)
{
    cout<<"Il peso totale e': "<<container.total_weight()<<"\n";
    cout<<"Il valore totale e': "<<container.total_value()<<"\n";
    if(container.total_value()>sogliavalue)
    {
        container.pacchiGiacenza();
    }
}
    void clearance_excess(int id_container)
    {

        std::cout<<"Nella funzione clearance\n";
        cout<<"dimensione giacenza! "<<BoxGiacenza.size()<<std::endl;
        for(list<Box*>::iterator iterator= BoxGiacenza.begin(); iterator!= BoxGiacenza.end(); ++iterator)
        {
            cout<<"Eliminazione dalla lista giacenza. . . "<<"\n";
            if(id_container=2341)
            {
                BoxGiacenza.erase(iterator);
            }
            cout<<"Size of Box in Giacenza: "<<BoxGiacenza.size()<<"\n";
        }
    }

    int dimBoxGiacenza(){
        return BoxGiacenza.size();
    }




    private:
    int id_container;
    string state_orig;
    string id_carrier;
    list<int> n_box;
    list<Box> boxlist;
    list<Box*> BoxGiacenza;


};

#endif