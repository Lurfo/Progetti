
#include "node.h"


#ifndef LISTA_H
#define LISTA_H

template <typename T>
class List{

    public: 
        class Iterator{
            private: 
                
                Node<T>* v; 
                Iterator(Node<T>*);

            public: 
                T& operator*();
                bool operator==(const Iterator&) const;
                bool operator!=(const Iterator&) const;
                Iterator& operator++(); 
                Iterator& operator--(); 

                friend class List<T>;
        };

    private:
        int num; 
        Node<T>* head; 
        Node<T>* trailer;


    public: 
        List(); 
        ~List(); 

        int size() const; 
        bool empty() const; 

        Iterator begin() const; 
        Iterator end() const; 

        void insertFront(const T&); 
        void insertBack(const T&);

        void insert(const Iterator&, T&);

        void eraseBack(); 
        void esareFront(); 

        void erase(); 

};

#include "lista.cpp"




#endif
