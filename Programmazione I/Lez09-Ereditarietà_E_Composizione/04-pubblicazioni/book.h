//Definzione della nuova classe che ha racchiude la categoria dei libri!
#include "publication.h"

#ifndef BOOK_H
#define BOOK_H

//Definisco la classe Book, come classe derivata di publication!
class Book: public Publication{
    //Dobbiamo ovviamente andare ad aggiungere la casa editrice e il codice del libro
    private: 
        string editor;
        string ISBN;
        

    public: 
    
    //Elemento che contiene il numero di elementi che salvo all'interno di questa classe!
    static int numLibri;
    //Static in modo che posso andare ad eliminarlo ogni volta!


        //Costruttore della classe!
        Book(const string&, int, const string&, const string&);
        virtual ~Book();

        //Funzioni set
        void setEditor(string&);
        void setISBN(string&);

        //Funzioni get
        string getEditor();
        string getISBN();

        //Override della funzione che mostra la stringa
       virtual string toString() override;


};





#endif