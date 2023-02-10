#include <iostream>

//Andiamo a includere questo header in modo da poter usare la libreria con tutti le funzioni per i vettori!
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;


//In tutte le funzioni stiamo usando un tipo di indirizzamento per riferimento, in modo che, non dobbiamo ogni volta, per ogni funzione, andare
//a riallocare in memoria un nuovo vettore--> molto utile usare questo tipo di riferimento a causa della natura di un vettore:
                                            //potendo permettere un'allocazione dinamica, abbiamo che l'allocazione in memoria di un vettore 
                                            //richiede uno "spazio" molto più grande!!!-->usare un passaggio per riferimento, possiamo risparmiarci
                                            //di allocare in memoria, ad ogni chiamata di funzione, un nuovo vettore!!!
void riemp(vector<int>&, int);
void mostro(const vector<int>&);

int  main(){
    //Andiamo a dichiarare un vettore
    //Questo primo è il numero di valori che il nostro vettore deve avere per poter definire la quantità di elementi!
    int num;
  
    //In questo modo  andiamo a dichiarare che stiamo considerando un vettore con tutti tipi int e il suo nome -appunto vetto- 
    //in questo caso abbiamo creato un vetto generico senza elementi
    vector<int> vetto;

    
    //Avevamo anche molte altre possibilità es:
    /* 1)  vector<int> vetto(num, 10)-->Vetto che ha un numero di elementi pari a num, inizilizzati a 10
       2) vector<int> vetto{3,4,5}--> Vettore che ha un numero di elemeti pari a 3 tutti inizializzati a questi valori!
       3) Dichiariamo una variabile int n=3-->vector<int>vettio(n)-->Abbiamo un vettore inizializzato con i 3 elementi*/


    //Chiedo all'utente di inserire il numero di elementi che si vogliono inserire all'interno del vettore!
    cout<<"Dimmi il numero di elementi che vuoi all'interno del vettore!\n";
        cin>>num;

    //Richiamo la funzione di riempimento: Ovviamente a tale funzione devo anche "inviare" anche il numero di elementi che voglio inserire
    //all'interno del mio vettore!
    cout<<"Andiamo a riempire il nostro vettore!\n";
        riemp(vetto, num);


    //Per visualizzare il nostro vettore, non è necessario passare il valore di elementi contenuto nell'array
    //Possiamo anche utilizzare la tecnica RANGE BASED per visualizzare gli elementi contenuti nell'array
    cout<<"Ti faccio vedere gli elemtni che sono stati inseriti nel vettore\n";
        mostro(vetto);

    cout<<endl;


}

void riemp(vector<int>& vetto, int num){

    // Andiamo quindi a creare una nuova variabile che ci serve per inserire gli elementi all'interno del vettore!
    int val;


    //Questo ciclo for ci serve per andare ad inserire gli elementi all'interno del nostro vettore!!!
    //Vediamo che bisogna comunque tenere conto del numero di elementi che abbiamo scelto di inserire nel suo interno!
    for(int i=0; i<num; i++){

            //Il primo passo è quello di salvare il valore che vogliamo inserire all'interno di una variable "provvisoria"
            cin>>val;

                //Per inserserire poi il valore all'interno del nostro vettore usiamo questa funzione particolare chiamata 
                //".push_back()", che come argomento ha proprio il valore contenuto nella nostra variabile provvisoria!!!
                vetto.push_back(val);

    }
}

void mostro(const vector<int>& vetto){


    //Nella funzione che ha il compito di mostrare gli elementi contenuti nell'array, possiamo usare un semplice ciclo for che usa il tipo di 
    //indirizzamento RANGE BASED, in modo che, non dobbiamo passare ulteriori argomenti alla funzione, ma possiamo semplicemente inviare 
    //il nostro array!!!
    for(auto const& item: vetto){
        cout<<item<<", ";
    }
}