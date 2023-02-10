//Andiamo ad usare l'algoritmo mergeSort per andare ad ordinare un vettore contenente un determinato numero di elementi!!!
//A differenza del InsertionSort che abbiamo usato nei due esercizi precedenti il mergeSort usa una strategia differente, basata sul concetto di
//"DIVIDE ET IMPERA" , vale cioè a dire che divide il nostro problema in tanti sottoproblemi più semplici da risolvere per poi riuniure le nostre 
//soluzioni!

//Dunque il mergeSort non fa altro che: 
/* 1-Dividere la sequenza iniziale in tante sotto sequenze più semplici da ordinare
   2-Andare a risolvere le singole sequenze, riordinandole
   3-Unire le differenti soluzioni e riformare la lista completa!!!*/

//(Vediamo che questo algoritmo si basa sull'uso ricorsivo di 2 funzioni differenti)
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using std::cout;
using std::endl; 
using std::cin;
using std::vector;

void riempio(vector<int>&, int);
const void mostro(vector<int>&);

//Tale è la dichiarazione delle due funzioni che compongono l'algoritmo del mergeSort
//La prima funzione è quella che va ad effettuare la divisione del nostro vettore in tanti sottovettori!!!
//è quella che si occupa dunque della fase divide e poi, va a richiamare la funzione merge che va riordinare le singole liste
void mergeSort(vector<int>&, int, int);

//La Seconda funzione, "merge", appunto, è quella che va a riordinare le singole liste!!!
void merge(vector<int>&, int, int, int);


int main(){
    vector<int> vet;
    int dim{0};

    cout<<"Dimmi la dimensine del vettore\n";
        cin>>dim;

    riempio(vet, dim);

    cout<<"Ho riempito il vettore, lo mostro\n";
        mostro(vet);

    cout<<"Essendo il vettore ordinato, vado a riordinarlo!\n";
    
    int l=0;
    int r=dim-1;

    mergeSort(vet, l, r);

    cout<<"Alla fine il vettore che ho modificato è uguale a: \n";
        mostro(vet);
}

void riempio(vector<int>& vet, int dim){

    srand(static_cast<unsigned int>(time(0)));

    for(int i=0; i<dim; i++){
        vet.push_back(1+rand()%100);
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

//Vado a specificare come si compone la funzione 
void mergeSort(vector<int>& vet, int l , int r){

    //Andiamo a dichiarare una nuova variabile
    int q;

    //Il corpo dell'if viene eseguito solo se l'indice di destra è maggiore di quello di sinistra!!!
    //Questo è ovvio poichè se abbiamo una lista formata solo da 1 elemento, questa è già ordinata!
    if(l<r){
        //La variabile q che abbiamo definito sopra, non fa altro che considerare il punto medio del nostro vettore e dei successivi vettori
        //delle chiamate ricorsive!!!
        q=(l+r)/2;

        //Andiamo a vedere come funziona la parte ricorsiva

        //Eseguiamo ancora una volta la funzione merge su 2 differenti vettori:
        /* La prima viene eseguita sulla prima metà
           La seconda, invece viene eseguita sulla seconda metà

           A loro volta, queste metà del vettore originario vengono divise in altre metà, fino ad avere liste formate solo da 1 elemento!
        
        */
       //Tali funzioni servono dunque per andare ad ordinare le liste separate
        mergeSort(vet, l, q);
        mergeSort(vet, q+1, r);

        //Questa è invece la funzione che ha il compito di andare a combinare le singole liste ordinate, in modo da ritornare alla lista iniziale!!!
        //La funzoine merge è quella che, in questo algoritmo ha la maggiore importanza per andare a "fondere" -merge, appunto- le liste ordinate
        merge(vet, l, r, q);

    }

}


//Tramite questa funzione vado a ricombinare le liste ordinate che abbiamo trovato!!!
void merge(vector<int>& vet, int l, int r, int q){
  
    //Importanti sono questi tre indici!
    int i,j,k;
    
    //La fuzione merge è come se avesse una sorta di memoria, rappresentato da questo vettore vet2, il quale però non viene allocato ogni chiamata
    //Infatti essendo di tipo static, non varia ed ogni volta che la funzione viene chiamata, allora vet2 viene richiamato così come lo aveva lasciato
    //precedentemente!
    //In questo vettore la funzione merge va ad inserire la fusione delle liste ordinate che abbiamo!!!
    static vector<int> vet2(vet.size());

    //i serve per scorrere la prima lista
    i=l;

    //k serve per scorrere la memoria della funzione merge, quindi rappresentata da vet2
    k=l;

    //j serve per scorrere la seconda lista
    j=q+1;


    //Vedo che tutto il lavoro della funzione merge viene svolto prevalentemente da questo while!!!

    //Troviamo qui un primi ciclo while, che ha come condizione di verificare che:
    /* Il valore di i è minore del valore della varibile che corrisponde al valore mid dato dalla funzoine mergesort 
       e il valore di j è minore della posizione dell'ultimo elemento del vettore!!!    
    */
   //in la condizione di questo while è vera fino a che stiamo scorrendo la lista di sinistra (rappresentata dalla condizione i<=q)
   //e la lista di destra (rappresentata dalla condizione j<=r)

    while(i<=q && j<=r){

        //Andiamo a vedere quale termine dobbiamo prelevare per salvarlo nella nostra memoria!
        //Il while permette di rimepire la lista vet2, ordinandola, scorrendo prima gli elementi della lista di sinistra e quelli della lista di destra!

        //Se vediamo che il valore della lista di sinistra è minore di quello della lista di destra eseguiamo questo if
        if(vet[i]<vet[j]){
           
           //Andiamo quindi a salvare nella memoria di merge questo valore della lista di sinistra 
            vet2[k]=vet[i];

            //Facciamo poi scorrere gli indici in modo che, al prossimo ciclo while, passiamo ad un valore successivo
            k++;
            i++;

        }

        //Questo else viene eseguito se vediamo che il valore della lista di destra è minore di quello della lista di sinistra!!!
        else{

            //Salviamo quindi questo valore nella memoria di merge
            vet2[k]=vet[j];

            //incrementiamo le variabili e andiamo avanti!
            k++;
            j++;
        }

        //Ovviamente notiamo che, in base all'elemento che inserisco nella lista vet2, andiamo ad incrementare l'indice di quella lista: 
        //Se inserico vet[i], incremento i;
        //Se inserico vet[j], incremento j;
        //In modo tale da confrontare ogni valore delle due liste ed individuare quale inserire prima e quale dopo!


        //Questo giochetto di controllo e di salvataggio viene effettuato fino a che non vediamo che abbiamo concluso una delle sue liste!!!
    }

    //Anche i due while che troviamo qui sotto sono molto importanti!!!
    //Ovviamente può accadere che una delle condizione del while di cui sopra non è più rispettata poichè il while ha esaurito il suo compito!
    //Possono però essere ancora presenti degli elementi o all'interno della lista di destra o all'interno della lista di sinistra!!!
    //i due while che vediamo qui servono proprio per andare a copiare questi ultimi elementi!
    
    //Questo while avviene se la seconda condizione del while (j<=r) fallisce, serve per ricopiare nella lista vet2, i valori restanti della lista di sinistra!
    //che però sono già ordinati, altrimenti il primo while li avrebbe ordinati direttamente!!!
    while(i<=q){
        vet2[k]=vet[i];

        k++;
        i++;
    }

    //Questo while avviene se la prima condizione del while sopra (i<=q) fallisce, in questo caso ricopia gli elementi che ancora sono contenuti
    //nella lista di destra all'interno della lista vet2!!!
    while(j<=r){
        vet2[k]=vet[j];
        k++;
        j++;
    }


    //Questo ciclo for serve semplicemente per ricopiare gli elementi dalla "memoria" della funzione merge al nostro vettore
    //elementi che sono già ordinati!!!
    for(i=l; i<k; i++){
        vet[i]=vet2[i];
    }

}


