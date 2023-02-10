//Definizione della classe 

#include <list>
#include <iostream>


#ifndef LIST_H
#define LIST_H

class prova{

    friend std::ostream& operator<<(std::ostream&, const prova&);

    private: 
        
        std::list<int> elementi;

        int proviamoconIntero;
    
    public:

        prova(); 

        ~prova();

        void addElement(int); 



};



#endif