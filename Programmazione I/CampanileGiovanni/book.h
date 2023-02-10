//Specificia della classe book

#include <string>
#include <vector>



#ifndef BOOK_H
#define BOOK_H

class Book{

    


    private: 
        //Codice identificativo del libro
        std::string book_id;

        //Definisco l'insieme di autori come un vettore di stringhe;
        std::vector<std::string> authors;

        //Titolo
        std::string title; 

        //Definizione dell'anno di pubblicazione!
        int year;

        //Posizione del libro all'interno della libreria
        std::string position; 

        //Prezzo del libro!
        float value;

    public: 
        //Costruttore con argomenti di default!
        Book(const std::string& =" ", const std::string& =" ", int = 1900, const std::string& =" ", double=0.0);

        //Distruttore 
        ~Book(){}

        //Specifica delle funzioni get e set per ogni variabile che abbiamo definito rispetto al libro, in questo modo possiamo gestite ogn dato membro presente nella classe!
        void setBook_id(const std::string&);
        std::string getBook_id() const; 

        void setAuthor(const std::string&);
        std::string getAuthor() const; 

        void setTitle(const std::string&); 
        std::string getTitle() const;

        void setYear(int); 
        int getYear() const;

        void setPosition(const std::string&);
        std::string getPosition() const; 

        void setValue(float); 
        float getValue() const;

        //Eseguo l'overloading degli operatori di cui ho bisogno per andare a ordinare il vettore che contiene i libri!
        
        //operatore minore!
        bool operator<(const Book&);

        //operatore maggiore
        bool operator>(const Book&);

        //Definizione dell'assegnazione di = 
        Book& operator=(const Book&);
    
};


#endif 