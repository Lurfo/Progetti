//Andiamo a definire la l'algoritmo del quicksorto usando un template, così che possiamo andare a considerarlo per qualsiasi elemento!
#include <vector>

using std::vector;

template <typename T>
void quickSort(vector<T>& pub, int l, int r){
    if(l<r){
      
        int q=partition(pub, l, r); //Definisco una partizione dell'elemento

        quickSort(pub, l, q);       //Applico il quickSort alla lista di sinistra e a quella di destra!
        quickSort(pub, q+1, r);
    }
}

//Definisco la funzione partition, usata in quicksort che è quella che svolge tutto il compito!
template <typename T>
int partition(vector<T>& pub, int l, int r){
    //Definizione dell'elemento pivot, consideriamo quello più a sinistra!
    T x=pub[l];

    int i=l-1;
    int j=r+1;

    while(true){
        do{
            j=j-1;
        }while(*x<*pub[j]); //In questo caso posso usare solo l'operatore minore, poichè è l'unico su cui ho eseguito l'overload!
                            //Inoltr, ho che, bisogna necessariamente deferenziare l'operaotre per poter effettuare il confronto in quanto 
                            //Devo sempre considerare l'elemento che viene puntato dal puntatore, se non lo deferenziassi, andrei a considerare gli 
                            //indirizzi!

        do{
            i=i+1;
        }while(*pub[i]<*x);

        //Andiamo quindi af effettuare lo swap degli elementi!
        if(i<j){
            swap(pub, i, j);
        }

        else 
            return j; //Che corrisponde all'elemento che abbiamo definito nella funzione quickSort!
    }

}

//Implementazione della funzione swap che mi occorre per andare 
template <typename T>
void swap(vector<T>& pub, int i, int j){
    T el=pub[i];

    pub[i]=pub[j];
  
    pub[j]=el;


}

