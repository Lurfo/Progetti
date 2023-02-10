#include "list.h"
#include<cstdlib>
#include <ctime>

using std::cout; 
using std::cin; 
using std::endl; 
using std::ostream;

std::ostream& operator<<(std::ostream&, const prova&);

int main(){

    prova definizione;

    srand(static_cast<int>(time(0)));

    for(int i=0; i<10; i++){
        definizione.addElement((rand()%100)+1);
    }

    cout<<"Ti mostro gli elementi!\n"; 

    cout<<definizione;

}

std::ostream& operator<<(std::ostream& out, const  prova& vediemento){

    std::list<int>::const_iterator p=vediemento.elementi.begin();    

    for(p; p!=vediemento.elementi.end(); ++p){
        out<<*p<<"\n";
    }

    return out;


}