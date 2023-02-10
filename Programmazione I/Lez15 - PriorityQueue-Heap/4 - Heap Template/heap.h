//Definizione di una classe template di un heap!
//A differenza della classe definita all'intero di 3 questa è una classe più completa
//NOTA: Quella definita in 3, può essere considerata più come una specifica di una classe che, gestendo un array, lo va a riordinare, facendo in modo che 
//rispetti una struttura di tipo heap!
//Al contrario, in questo caso abbiamo una classe "completa" che ha come veriabile membro un array, ma AD OGNI INSERIMENTO L'ARRAY VIENE ORDINATO
//COME UN HEAP, IN QUESTO MODO NON DOBBIAMO ANDARE A DICHIARARE FUNZIONI AGGIUNTIVE, ma tutto il lavoro di "formazione" dell'heap, viene svolto
//dalla funzione di inserimento!
#include <stdexcept>
#include <iostream>


#ifndef HEAP_H
#define HEAP_H
template <typename T>
class Heap{
    private: 
        T* arr; 
        int numElementi; //Salvo il numero degli elementi!
        int posiz;  //Utilizzo questo come una sorta di puntatore che serve per andare ad aggiungere l'elemento!
        
        //Specifica della funione heapfy!
        //Perchè la funzione heapfy se ogni volta il nostro vettore viene inizializzato come un heap? 
        //La funzione heapfy è fondamentale in quanto viene utilizzata dalla funzione che estrae il massimo!
        //una volta che abbiamo estratto il massimo, la struttura dell'heap viene cambiata, dunque dobbiamo andare a vedere se i veri sottoalberi che ho
        //rispettano ancora la proprietà di heap, per tale motivo è necessario sfruttare la funzione heapfy!
        void heapfy(int);

    public: 
        Heap(int =11); 

        ~Heap(); 

        //Questa è la funzione che restituisce l'effettiva dimensione dell'array!
        int sizeArr() const;

        //Questa invece è la funzione che restituisce l'effettivo numeri di elementi presenti nell'array!
        int size() const; 

        bool empty() const; 

        //Definizione delle funzioni che servono per andare a trovare i figli e i genitori!
        //sono utili per trovare i figli e i genitori in funzione della posizione in cui mi trovo!
        int left(int); 
        int right(int);
        int parent(int); 

        //VADO A DEFINIRE LA FUNZIONE CHE HA IL COMPITO DI ANDARE A INSERIRE UN ELEMENTO ALL'INTERNO DELLA STRUTTURA, MANTENDO LA CARATTERISTICA 
        //HEAP DELLA STRUTTURA, è cioè la funzione che compie tutto il lavoro!
        void insertHeap(const T&);

        //LA CLASSE PREVEDE ANCHE DI CONTENERE UNA FUNZIONE CHE RESTITUISCE IL VALORE MASSIMO DELLA STRUTTURA E CHE LO ELIMINA!
        //Per questa funzione dobbiiamo necessariamente definire la funzione heapfy!
        const T heapMaxEstract(); 

        //Altrimenti posso definire un'altra funzione che va semplicemente a restituire il valore massimo!
        const T& top() const;

        void mostro();


};

#include "heap.cpp"

#endif