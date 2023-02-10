
#include <vector>
#include <stdexcept>
using std::vector;


#ifndef HEAP_H
#define HEAP_H
template <typename T> class PriorityQueue;

template <typename T>
class Heap{
    friend class PriorityQueue<T>;

    private:
        //Definisco come contenitore per i miei elementi un vettore e non un array, in questo modo posso andare ad incrementaro dinamicamente! 
        vector<T> vet; 
        int siz; 

        //Definizione della funzione heapfy!
        void heapfy(int);
        //Contiene 2 elementi, uno che rappresenta la variabile da cui partire, uno che rappresenta la dimensione del vettore!
        //usiamo una variabile che rapp
    
    public: 

        Heap(); 

        int size() const; 
        bool empty() const; 

        int left(int); 
        int right(int);
        int parent(int);

        void insertHeap(const T&); 

        const T exctratMax();

        const T& top() const; 

};

#include "heap.cpp"



#endif