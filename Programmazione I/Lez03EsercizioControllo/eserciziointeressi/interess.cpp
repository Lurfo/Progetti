#include <iostream>
//Uso una nuona libreria di funzioni chiamata cmath, ci permette di usare una funzione per l'elevazione a potenza, utile in questo caso
//usata per la funzione pow, ma essa usa anche molte altre funzioni matematiche come il seno e coseno!
#include <cmath>

//Uso la libreria iomanip in modo da poter impostare la precisione cone la quale il programma mi deve mostrare i double
//utie per le funzioni fixed e setprecision
#include <iomanip>

using std::cout;
using std::cin; 
using std::endl;
using std::setw;
using std::fixed;
using std::setprecision;
//La funzione per il calcolo del tasso di interesse è uguale a bil=(1+interesse)^anno*bilancioIniz

//Dichiaro la funzione che ci serve per calcolare il tasso di interesse
void calcolo(double bilancio, double tasso, int anni);

int main(){

    //Discutiamo su questa precisazione
    //Fixed serve per specificare che il valore deve essere sempre espresso con la virgola
    //setprecision invece indica quante cifre decimali il nostr numero deve avere, nel nostro caso 4
    //Questi due valori sono "sticky" nel senso che, anche scrivendoli all'inizio del mio programma, essi vanno ad influenzare tutti 
    //i valori successivi che abbiamo, fino a che non vengono modificati
    cout<<fixed<<setprecision(4);
  
    double bilancioInz{0};
    double tasso{0};
    int anni{0};

    cout<<"Inserisci il bilanzio iniziale del tuo conto\n";
        cin>>bilancioInz;

    cout<<"Inserisci tasso di interesse\n";
        cin>>tasso;

    cout<<"Inserisci per quanti anni vuoi tenere i risparmi al sicuro\n";
        cin>>anni;
    
    calcolo(bilancioInz, tasso, anni);

}

void calcolo(double bilancio, double tasso, int anni){
    cout<<"Ti mostro il tasso di interesse dei tuoi risparmi in base alle informazioni che mi hai detto\n";

    for(int i=0; i<anni; ++i){
        double capitale{bilancio*pow(1+tasso,i+1)};

         //Abbiamo usato la funzione pow, questa è in grado di elevare il valore "1+tasso" al valore "anni"
        cout<<"Anno: "<<i+1<<", Capitale: "<<capitale;
        cout<<endl;
    }

    return;
}