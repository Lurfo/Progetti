#ifndef CIRCULARLYLINKEDLIST__CIRCLELIST_H_
#define CIRCULARLYLINKEDLIST__CIRCLELIST_H_

#include <iostream>
#include "Node.h"
#include "Container.h"
#include <string>
#include <sstream>

template<typename T>
class CircleList {
 private:
  Node<T>* cursor;
  int n;
 public:
  CircleList();              // costruttore
  ~CircleList();             // distruttore
  bool isEmpty();           // true se la lista è vuota
  const T& front() const;   // elemento che segue il cursore
  const T& back() const;    // elemento al cursore
  void advance();           // fai avanzare la posizione del cursore
  void add(const Container&);     // aggiungi dopo il cursore
  void remove();            // rimuovi che segue il cursore
  std::string toString(int);   // stampa come stringa
  T operator[](int i);
  int size();
};

template<typename T>
CircleList<T>::CircleList() : cursor{nullptr}, n{0} {};

template<typename T>
CircleList<T>::~CircleList() {
    while (!isEmpty()) {
        remove();
    }
}

template<typename T>
bool CircleList<T>::isEmpty() {
    return (cursor == nullptr);
}

template<typename T>
const T & CircleList<T>::front() const {
    return cursor->next->elem;
}

template<typename T>
const T & CircleList<T>::back() const {
    return cursor->elem;
}

template<typename T>
void CircleList<T>::advance() {
    cursor = cursor->next;
}

template<typename T>
void CircleList<T>::add(const Container& container) {
    auto* v = new Node<T>;
    v -> elem = container;
    
    if (isEmpty()) {
        // l'unico elemento nella lista è v!
        // quindi il successivo è di nuovo se stesso
        v->next = v;
        cursor = v;
    } else {
        // setto il puntatore next del nuovo elemento
        v->next = cursor->next;
        // inserisco il nuovo elemento nella catena
        cursor->next = v;
    }
    n++;
}

template<typename T>
void CircleList<T>::remove() {
    if (isEmpty()) {
        throw std::runtime_error("Cannot remove element: list is empty!");
    }
    Node<T>* old = cursor->next;   // ad essere rimosso è l'elemento che segue il cursore
    if (old == cursor) {
        // c'è un solo elemento nella lista
        cursor = nullptr;
    } else {
        cursor->next = old->next;
    }
    delete old;
}

template<typename T>
int CircleList<T>::size(){
    return n;
}

template<typename T>
T CircleList<T>::operator[](int i) {
    if (i >= size()) {
        throw std::invalid_argument("Reached end of list!");
    }
    Node<T>* n = cursor;
    for (int j = 0; j < i; ++j) {
        n = n->next;
    }
    return n->elem;
}

template<typename T>
std::string CircleList<T>::toString(int i) {
    if (isEmpty()) {
        throw std::runtime_error("Cannot print: list is empty!");
    }
    std::ostringstream out;
    Node<T>* n = cursor;
    for (int j = 0; j < i; ++j) {
        n = n->next;
    }
    out << n -> box.toString();
    return out.str();
}

#endif //CIRCULARLYLINKEDLIST__CIRCLELIST_H_