#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include <iostream>
#include "CircleList.h"
#include "Container.h"

template <typename E>
class LinkedQueue{
    public:
        LinkedQueue();
        int size() const;
        bool empty() const;
        const E& front();
        void enqueue(const Container&);
        void dequeue();
        E operator[](int i);
    private:
        CircleList<E> C;
        int n;
};

#endif

template <typename E>
LinkedQueue<E>::LinkedQueue()
    : C(), n{0}{
}

template <typename E>
int LinkedQueue<E>::size() const{return n; }

template <typename E>
bool LinkedQueue<E>::empty() const{return n==0; }

template <typename E>
const E& LinkedQueue<E>::front(){
    if(empty()) throw std::runtime_error("front of empty queue");
    return C.front();
}

template <typename E>
void LinkedQueue<E>::enqueue(const Container& container){
    C.add(container);
    C.advance();
    n++;
}

template <typename E>
void LinkedQueue<E>::dequeue(){
    if(empty()) throw std::runtime_error("dequeue of empty queue");
    C.remove();
    n--; 
}

template <typename E>
E LinkedQueue<E>::operator[](int i) {
    return C[i];
}