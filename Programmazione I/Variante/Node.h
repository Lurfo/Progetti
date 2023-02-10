#ifndef NODE_H
#define NODE_H

#include <iostream>

template<typename T> class LinkedList;
template<typename T> class CircleList;

template <typename T>
class Node {
    private:  
        Node<T>* next;
        T elem;
        friend class LinkedList<T>;
        friend class CircleList<T>;
};

#endif