//Vado a specificare le funzioni della classe list che ho definto, così da poterla utilizare
#include "StringList.h"
#include <stdexcept>
#include <iostream>

//Specifica del costruttore, esso deve inizializzare una lista vuota!
StringList::StringList(): header{nullptr}, lung{0}  {}//Lo andiamo ad inizializzare al valore nullptr

//Specifica del distruttore!
StringList::~StringList(){
    //Il distruttore deve rimuovere ogni fronte fino a che non viene eliminata tutta la lista!
    while(!empty()){
        removeFront();
    }
}


//Specifica della funzione che aggiunge un nuovo elemento!
void StringList::addFront(const string& elemento){

    Node* nuovo=new Node;   //Creo un nuovo nodo da aggiungere alla lista

    nuovo->element=elemento;    //Inserisco il dato all'interno della list
    nuovo->next=header;         //Vado a impostare il puntatore al vecchio header

    header=nuovo;   //Imposto come nuovo header l'elemento nuovo che ho inserito!

    lung++;

}


//Funzione che rimuove un elemento dalla testa della lista!
void StringList::removeFront(){
    
    //Controllo che la lista non sia vuota!
    if(empty()){
        throw std::runtime_error{"La lista che sto considerando è vuota!"};
    }

    else{
        Node* old=header;   //Salviamo il valore puntato dal vecchio header così da poterlo dopo eliminare
        header=header->next;    //impostiamo l'header a puntare all'elemento successivo!
        delete old;         //Eliminiamo il valore puntato dal vecchio header!
    }   

    lung--;

}


//Funzione che preleva il dato dalla testa della lista!
const string& StringList::front() const{
    return header->element;
}

//Funzione che controlla se la lista è vuota
bool StringList::empty(){
    return header==nullptr; //Se la lista è vuota, come visto il valore che punta l'header è sempre nullo!
}


const string& StringList::operator[](int i){
    //Definizione dei due puntatori necessari per andare a scorrere gli elementi della lista 
    Node* element1{nullptr}; //Inizializziamo uno dei 2 a puntatore nullo sarà quello che contiene l'elemento che dobbiamo prelevare
    Node* newhead{header};  //L'altro è quello che usiamo per andarci a spostare rispetto ad ogni elemento! Per questo inizializzato al valore del puntatore iniziale

    //Facciamo un controllo del valore a cui vogliamo accedere !
    if(i>size() && i<0){
        std::cerr<<"Non puoi accedere a questa locazione di memoria!\n";
    }

    //Se il valore che gli stiamo passando è uguale al valore che esprime la grandezza della lista allora vuol dire che 
    //vogliamo prendere il valore del fronte! Cioè il primo valore della lista!
    else if(i==size()-1){
        front();
    }

    //Altrimenti dobbiamo andare a cercare l'elemento che ci occorre!
    else{

        //Usiamo il for per cercare l'elemento!
        //Partiamo sempre dal fronte della lista!
        for(int k=size()-1; k>i; k--){
            //A mano a mano usiamo i due puntatori che abbiamo definito sopra per spostarci tra i vari nodi che abbiamo definito!
            element1=newhead->next;
            //Spostiamo quindi il puntaotre newhead per definite ogni volta un "segnaposto" al nodo in modo da spostarci tra i vari elementi!
            newhead=element1;
        }

        //Al termine del ciclo for siamo arrivati all'elemento che ci occorre, quindi posso restituire il valore che ho puntato!
        return element1->element;
    }

}