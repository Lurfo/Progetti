//Vado a definire la classe priorityqueue che sfrutta un heap!
#include "heap.h"

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H
template <typename T>
class PriorityQueue{
    private:
        Heap<T> alb; 

    public: 
        PriorityQueue(); 

        int size() const; 
        bool empty() const; 

        void Enqueue(const T&); 
        const T Dequeue();

        const T& top();

        void vedo();

};

#include "priorityQueue.cpp"

#endif