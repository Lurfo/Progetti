//Definizion della classe node che va a definire il singolo elemento della lista circolare 
//Usando sempre dei template!

#ifndef NODE_H
#define NODE_H

//Specifica della classe friend 
template <typename T> class CList;

template <typename T> 
class Node{

    //Specifica degli elementi che compongono il nodo
    private:
        //L'elemento vero e proprio
        T elemento;

        //Il puntatore al prossimo elemento!
        Node<T>* next;


    friend class CList<T>;
};


#endif