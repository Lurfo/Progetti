//Definizione di tutte le funzioni membro della classe 
#include "book.h"
#include <sstream>
#include <iostream>


Book::Book(const std::string& id, const std::string& titolo, int anno, const std::string& posizione, double costo): 
book_id{id}, title{titolo}, position{posizione}{
    //Vado ad inserire l'anno di pubblicazione e il prezzo usando le funzioni membr in modo da effettuare un controllo
    setYear(anno); 
    setValue(costo);

}


//Definizione della funzione di inserimento dell'id 
void Book::setBook_id(const std::string& elemento){
    book_id=elemento;
}

//Funzione del prelivevo dell'id
std::string Book::getBook_id() const{
    return book_id;
}

//Funzione che inserisce gli elementi da inserire nel vettore!
void  Book::setAuthor(const std::string& elemento){
    //Uso la funzione del vettore push_back per inserire l'elemento
    authors.push_back(elemento);
}

//Funzione che restituisce tutti gli elementi che sono contenuti nel vettore!
std::string Book::getAuthor() const{
    //Uso un oggetto di tipo ostringstream per inserire tutti le stringhe che sono contenute nel vettore
    //Per poi restituire una singola stringa!
    std::ostringstream out; 

    out<<"Autori:\n";

    //Vedo gli elementi del vettore!
    for(int i=0; i<authors.size(); i++){
        out<<authors[i]<<((i!=authors.size()-1) ? ", " : "\n");
    }

    //Per ritornare una stringa uso una funzione dell'oggetto out che ho definito!
    return out.str();
}

void Book::setTitle(const std::string& elemento){
    title=elemento;
}

std::string Book::getTitle() const{
    return title;
}


void Book::setYear(int anno){
    if(anno<1200){
        std::cerr<<"Non posso andare a salvare l'anno di pubblicazione\n";
    }

    else{
        year=anno;

    }

}

int Book::getYear() const{
    return year;
}

void Book::setPosition(const std::string& posizione){
    position=posizione;
}

std::string Book::getPosition() const{
    return position;
}

void Book::setValue(float costo){
    if(costo<0){
        std::cerr<<"Non puoi salvare un valore negativo!\n"; 
    }
    else{
        value=costo;
    }
}

float Book::getValue() const{
    return value;
}


//NOTA: L'ordinamento viene fatto per ordine di autori, se gli autori sono uguali, ordino per anno!
bool Book::operator<(const Book& elemento){
    
    //Controllo prima che i due autori non sia uguali!
    //Uso l'operatore di confronto tra i due vettori!
    if(authors==elemento.authors){
        //Se sono uguali, confronto con anno
        return year<elemento.year;
    }

    else{
        //Anche in questo caso procedo con l'uso dell'operatore di overload della classe vector!
        return authors<elemento.authors;
    }
}

bool Book::operator>(const Book& elemento){
    //Funzione simile a quella dichiarata sopra!
    
    if(authors==elemento.authors){
        
        return year>elemento.year;
    }

    else{
        return authors>elemento.authors;
    }
}

Book& Book::operator=(const Book& sec){
    book_id=sec.book_id;
    authors=sec.authors;

    title=sec.title;

    year=sec.year; 

    position=sec.position; 

    value=sec.value;
    return *this;
}