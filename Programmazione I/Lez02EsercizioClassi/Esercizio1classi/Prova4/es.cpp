#include <iostream>
#include "es.h"
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(){
    Account persona{"Ezio Greggio", 27};
    float somma{0};
    char rispo;

    cout<<"Ho registrato un account a nome di: "<<persona.getName();
    cout<<"\nCon un bilancio di: "<<persona.getBalance()<<endl;

   do{ cout<<"Che operazione vuoi fare? Aggiungere(a) o Prelevare(p)";
        cin>>rispo;

        if(rispo=='a'){
            cout<<"Dimmi quanti soldi depositare"<<endl;
                cin>>somma;
            persona.addBalance(somma);
        }

        else if(rispo=='p'){

            cout<<"Dimmi quanti soldi prelevare"<<endl;
                cin>>somma;
            persona.subBalance(somma);

        }

        cout<<"Se non devi fare altro puoi dirmi 's' per fermarmi"<<endl;

   
   
   }while(rispo!='s');

   cout<<"Ho registrato: "<<persona.getName();
   cout<<"\nCon un saldo di: "<<persona.getBalance()<<endl;

}
