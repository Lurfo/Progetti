#include <iostream>
#include <fstream>
#include <iomanip>
#include <queue>
#include <string>
#include <cstdlib>
#include "container.h"
#include "Box.h"
using std::queue;
using std::ifstream;
using std::ios;
using std::cout;


int main()
{
    queue<Container> coda;
    ifstream inContainersFile("client.txt",ios::in);
    
    if(!inContainersFile)
    {
        std::cerr <<"File could not be opened! "<<std::endl;
        exit(EXIT_FAILURE);
    }


    int id_container;
    std::string state_orig;
    std::string id_carrier;
    int n_box;
    int box_id;
    double weigh;
    int value;
    int perishable;
    inContainersFile.seekg(0,ios::beg);

    while(inContainersFile>>id_container >> state_orig>> id_carrier>>n_box)
    {   
        
        Container container(id_container, state_orig, id_carrier, n_box,box_id,weigh,value,perishable);
        coda.push(container);
        coda.pop();
        cout<<"Stampa coda di container: "<<"\n";
        cout<<container.toString()<<std::endl;
        for(int i=0;i<n_box;i++)
        {   cout<<"Pacco numero "<<i<<"\n";
            inContainersFile>>box_id >> weigh>> value>>perishable;
            container.addBox(Box(box_id,weigh,value,perishable));
            cout<<Box(box_id,weigh,value,perishable).toString()<<std::endl;
            
        }
    
        coda.push(container);
        if(coda.size()-1)
        {
        container.clearance(coda, container);
        }
        cout<<"La dimensione della lista di giacenza è uguale a: "<<container.dimBoxGiacenza()<<"\n";
        coda.push(container);
        container.clearance_excess(id_container);
        
    }
    
    inContainersFile.close();


}

