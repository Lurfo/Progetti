//Un esempio di iterator è quello che è contenuto all'interno della classe vector della stl!
#include <iostream>
#include <vector>

using std::cin; 
using std::cout;
using std::endl;
using std::vector;

int main(){
    vector<int> vetto; 

    cout<<"Inserisci elementi nel vettore!\n";

    int num; 

    do{
        cout<<"Dimmi numero - 0 Per terminare\n";
            cin>>num; 
        
        if(num!=0){
            vetto.push_back(num); 
        }
    }while(num!=0);

    //Dichiaro un iterator per il vettore
    vector<int>::iterator p; //In questo modo definisco un iteratore per la classe di vettori!

    //Ovviamente devo inizializzarlo, per farlo lo inizializzo al primo elemento contenuto nel vettore!
    //Ci torna utile la funzione begin che è contenuta nella classe vector!
    p=vetto.begin();

    cout<<"L'iteratore è all'elemento: "<<*p<<"\n";

    cout<<"Ti mostro tutti gli elementi contenuti nel vettore usando l'iteratore!\n"; 

    for(p; p!=vetto.end(); p++){
        cout<<*p<<((p!=vetto.end()-1)? ", " : " ");
    }


    cout<<endl;

    //In alcuni casi è anche possibile andare a modificare un elemeneto grazie agli iterator, tuttavia è possibile che, in determinate situazioni
    //si voglia  impedire agli iterator di modificare i valori che sono contenuti all'interno di essi, quindi è possibile utilizzare un iteratore
    //costante! Che quindi non permette di modificare gli elementi!
    
}