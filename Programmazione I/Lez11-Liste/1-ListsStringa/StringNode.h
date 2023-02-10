//Vado a definire la classe che ha il compito di rappresentare il nodo della lista di stringhe!
#include <string>
using std::string;


#ifndef STRINGNODE_H
#define STRINGNODE_H

class Node{
    private: 
    //Come detto il nodo è importante che abbia solo due elementi!
    string element; //Il singolo elemento
    Node* next;     //Il puntatore al prossimo elemento della lista! (Ovviamente deve essere un puntatore di tipo Node!)

    //A questo punto non abbiamo bisogno di altre funzioni in quanto questa classe ha il solo scopo di rappresentare il singolo blocchetto della lista

    //Dobbiamo però dichiarare che la classe che poi rappresenta la vera e propria lista, deve essere amica di questa classe in modo da poter modificare
    //i dati privati di quest'ultima! (Quindi andare ad inserire gli elementi all'interno della lista)

    friend class StringList;



};



#endif