/* Oltre il merge, analizzato in 09, uno dei più importanti di algoritmi di ordinamento più utilizzati è il quick sort!!!
    è anche tra gli algoritmi di orinamento che è più studiato tra tutti proprio per cercarne di capire al meglio il funzionamento
    Come mai è così conveniente? questo tipo di ordinamento è conveniente perchè ha un caso medio che ha una complessità simile a nlogn 
    è quindi di molto inferiore rispetto a quella del merge! --> tuttavia nella situazione più complessa, quando cioè l'array si trova in ordine 
    decrescente, questi ha una complessità pari a n^2, diventa quindi molto più complesso, ma conviene sempre utilizzarlo, sono rari i casi in cui
    abbiamo un vettore ordinato in modo decrecente! */

//Tale tipo di algoritmo si basa su due funzioni fondamentali (di cui una è quella che svolte tutto il lavoro, è cioè la chiave dell'algoritmo) +
//una funzione che ha il semplice compito di effettuare uno swap!
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using std::vector;
using std::cout;
using std::cin;
using std::endl;

void riempio(vector<int>&, int);
const void mostro(vector<int>&);

//La prima funzione che qui compare è quickSort, essa ha il semplice compito di andare a dividere il vettore in due sotto-vettori, andandoli poi ad
//ordinare progressivamente e separatamente!
void quickSort(vector<int>&, int, int);

//QUESTA È LA FUNZIONE FONDAMENTALE DELL'ALGORITMO, essa infatti è quella che va a compiere la maggior parte del lavoro!
//La funzione partition è infatti quella che va a ordinare gli elementi del vettore usando come riferimento un elemento chiamato pivot!
//NON ANDIAMO QUINDI A CONSIDERARE IL PUNTO MEDIO DEL NOSTRO VETTORE!
//Essa è di tipo int, poichè dobbiamo poi restiuire un valore!
int partition(vector<int>&, int, int);

//La funzione swap serve a partition per andare a invertire dei valori!
void swap(vector<int>&, int, int);

int main(){
   
    vector<int> vetto;
    int dim; 
    
    cout<<"Dimmi la dimensione del nostro vettore!\n";
        cin>>dim;
    
    riempio(vetto, dim);

    cout<<"Il vettore generato è:\n";

    mostro(vetto);

    cout<<"Essendo disordinato, vado a riordinarlo!\n";

    //Dobbiamo sempre dichiarare i nostri segnaposto che considerano la posizione del primo e dell'ultimo elemento del vettore!
    int l=0;
    int r=dim-1;

    quickSort(vetto, l, r);

    cout<<"Il vettore ordinato è uguale a: \n";

    mostro(vetto);

    
}

void riempio(vector<int>& vet, int dim){

    srand(static_cast<unsigned int>(time(0)));

    for(int i=0; i<dim; i++){
        vet.push_back(1+rand()%1000);
    }

    return;

}


const void mostro(vector<int>& vet){

    for(auto const& item: vet){
        cout<<item<<"; ";
    }

    cout<<endl;

    return;
}


void quickSort(vector<int>& vetto, int l, int r){

    //Come anche nel caso del merge andiamo a svolgere questa funzione solo se il valore del segnaposto di sinistra è minore di quello di destra!
    //vuol dire che non si sono ancora superati e dunque dobbiamo proseguire con l'ordinamento!
    if(l<r){

        //La variabile che qui andiamo a salvare è la variabile che ricaviamo dalla funzione partition, motivo per cui essa era di tipo int!
        //corrisponde al valore della posizione dell'elemento pivot che scegliamo durante lo svolgimento di partition!
        int q=partition(vetto, l, r);

        //Come anche nel caso del merge qui andiamo a ordinare separatamente i due sotto-array che otteniamo dall'esecuzione della funzione!
        //Quello di sinistra va da l a q!
        //Quello di destra va da q+1 a r!
        quickSort(vetto, l, q);
        quickSort(vetto, q+1, r);

    }
    
}

int partition(vector<int>& vetto, int l, int r){
    //Dichiariamo il nostro elemento pivot, quello che ci serve per andare ordinare la nostra lista!
    //In generale andiamo a prendere il primo elemento della lista!
    //L'elemento pivot è importante, perchè: 
    //-Alla sua sinistra spostiamo tutti gli elemetni che sono minori;
    //-Alla sua destra spostiamo tutti gli elementi che sono maggiori!
    int x=vetto[l];


    //Andiamo a dichiarare due variabili che ci servono per scorrere gli elementi della lista!
    int i=l-1; //Variabile che parte subito prima del primo valore del nostro vettore
    int j=r+1; //Variabile che parte subito dopo l'ultimo valore del vettore 

    //Per andare a scorrere gli elementi del nostro vettore consideriamo un ciclo while che si interrompe solo quando deve restituire la posizione
    //dell'elemeto pivot!
    while(true){

        //Con questo primo ciclo do-while andiamo a cercare, da destra, il primo elementi che sia minore del pivot!
        do{
            //Sndiamo a decrementare il valore della j in modo da poter scorrere il vettore!!!
            j=j-1;
        }while(vetto[j]>x); //Se non abbiamo elementi che sono minori del pivot, il ciclo si interrompe quando la posizione di j è uguale a quella
                            //del pivot!
        

        //Usiamo un altro do-while per andare a trovare il primo elemento, da sinistra, che è maggiore del pivot!
        do{
            i=i+1;
        }while(vetto[i]<x);

        //A questo punto se il vettore non è stato scandito completamente e abbiamo, vuole dire che abbiamo trovato i velori che cercavamo, dunque
        //li andiamo a scambiare di posizione!

        //La condizione dell'if sottolinea prorio che, nel nostro while, abbiamo trovato i valori che cercavamo, quindi i due indici non si sono 
        //incontrati!
        if(i<j){
            swap(vetto, i, j);
        }

        //Se, invece, i due valori si sono incontrati, cioè abbiamo cercato tutto il vettore senza alcun risultato adiamo a restituire il valore di j
        //che indica la posizione dell'elemento pivot, che serve per andare a dividere la lista in due sottoliste!!!
        else
            return j;


    }
}

void swap(vector<int>& vetto, int x, int y){
    int temp=vetto[x];

    vetto[x]=vetto[y];

    vetto[y]=temp;


}


