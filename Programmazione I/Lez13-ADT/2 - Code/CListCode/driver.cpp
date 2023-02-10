//Specifica del driver che utilizzo per andare a utilizzare la lista!
#include "coda.h"

using std::cout;
using std::cin; 
using std::endl; 

int  main(){
    Coda<int> cd; 

    cout<<"Inserisco gli elementi all'interno della coda!\n";

    int element; 

    do{
        cout<<"Dimmi il numero - [0 - Per terminare]\n";
            cin>>element;

        if(element!=0){
            cd.enqueue(element);
        }

    }while (element!=0);

    cout<<"Nella coda ci sono: "<<cd.size()<<" elementi\n";

    cout<<"L'elemento in testa è: "<<cd.front()<<"\n";

    cout<<"Posso eliminare il primo elemento\n";
    cd.dequeue(); 

    cout<<"Il primo elemento ora è: "<<cd.front()<<"\n";

    cout<<"Elimino tutti gli elementi della lista!\n";

    while(!cd.empty()){ 
        cout<<"Ci sono: "<<cd.size()<<" elementi\n";
        cout<<"Il primo elementi è: "<<cd.front()<<"\n";
        cd.dequeue(); 
    } 

    if(cd.empty()){
        cout<<"La lista ora è completamente vuota!\n";
    }
    

}