//Vado a specificare un programma in grado di andare ad utilizzare alcune delle funzioni della classe heap (viste in 4) e altre funzioni determinate
//in 3, tra cui buildHeap, per andare a "generare" un algoritmo di ordinamento che si basa proprio sull'utilizzo di un heap!

#include <iostream>
#include <vector>

using std::cout; 
using std::cin; 
using std::endl; 
using std::vector;

//La funzione heapfy è quella che è fondamentale per andare a generare il nostro heap!
template <typename T>
void heapfy(vector<T>&, int, int);

//Devo andare a definire la funzione che trasforma la struttura in un heap!
template<typename T>
void buildHeap(vector<T>&, int);

//La funzione qui è quella che poi va a riordinare gli elementi in ordine!
template <typename T> 
void heapSort(vector<T>&, int);

int main(){
    vector<int> prova;
    int dim{0};
    int num;

    prova.push_back(0);

    do{
        cout<<"Inserisci elemento nel vettore - 0 Per terminare\n";
            cin>>num; 
        
        if(num!=0){
            prova.push_back(num);
            dim++;
        }
    }while(num!=0);

    cout<<"Nel vettore ci sono gli elementi: \n";

    for(int i=1; i<prova.size(); i++){
        cout<<prova[i]<<((i!=prova.size()-1) ? ", " : "\n"); 
    }

    cout<<"vado ad ordinare il vettore!\n";

    buildHeap(prova, dim);

    heapSort(prova, dim);

    

    cout<<"Nel vettore ci sono gli elementi: \n";

    for(int i=1; i<prova.size(); i++){
        cout<<prova[i]<<((i!=prova.size()-1) ? ", " : "\n"); 
    }

}



template <typename T> 
void heapfy(vector<T>& vett, int i, int dim){
    int l=2*i;
    int r=2*i+1;

    int posMax{0}; 

    if(l<=dim and vett[l]>vett[i]){
        posMax=l;
    }

    else{
        posMax=i;
    }

    if(r<=dim and vett[r]>vett[posMax]){
        posMax=r;
    }

    if(posMax!=i){

        int salvo=vett[i]; 
        vett[i]=vett[posMax];
        vett[posMax]=salvo;

        heapfy(vett, posMax, dim);
    }
}

template <typename T>
void buildHeap(vector<T>& vett, int dim){
    
    for(int i=dim/2; i>=1; i--){
        heapfy(vett, i, dim);
    }
}

//Questa è la nuova funzione che no fa altro che andare a sistemare in ordine gli elementi, ponendo quelli maggiori alla fine
//usando la prorpietà dell'heap!
//In particolare il corpo di questa funzione è molto simile a quella che ho definito per estrarre il valore maggiore!
template <typename T>
void heapSort(vector<T>& vett, int dim){
    int salvo;
    for(int i=dim; i>1; i--){
        salvo=vett[1];
        vett[1]=vett[dim];
        vett[dim]=salvo;
        dim--; 
        heapfy(vett, 1, dim);
    }
}


