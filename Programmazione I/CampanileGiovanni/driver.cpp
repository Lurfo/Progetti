#include <iostream>
#include "data.h"
#include "book.h"
#include "prestiti.h"
#include "list.h"

using std::cout;
using std::cin; 
using std::endl; 
using std::string; 
using std::vector; 

enum class choice{BORROW=1, VALUE, RETURN, END};


void ordinoLibri(vector<Book>&);

//Faccio fare all'utente una scelta dei libri da andare ad inserire!
choice failascelta();

void borrow(List<Prestato>&, Book&);
int valueExpired(List<Prestato>&, Data&);
void returnBook(List<Prestato>&, Data&);

int main(){
    //Inserisco la data odierna!

    Data oggi;
    int g;
    int m; 
    int a;

    cout<<"Benvenuto nel programma che ti permette di gestire la tua biblioteca, inserire la data odienra per continuare! [gg/mm/aaaa]\n";
        cin>>g >>m >>a;

    //Definizione del vettore che contiene i libri!
    vector<Book> libri;

    Book libro; 

    //Variabili necessarie per andare ad inizializzare i valori dell'oggetto Book
    string id; 
    string titolo; 
    string posizione;
    string autore; 
    int anno; 
    float costo; 

    //Per richiesta inserimento!
    char risp;

        cout<<"Inizio inserimento\n";

    //Uso un ciclo do while in modo che mi permette di gestire, in base alla richiesta dell'utente di continuare ad inserire o meno altri titoli all'interno della libreria
    //Ne faccio inserire però almeno uno!
    cin.ignore();
    cin.clear();
    do{
        cout<<"Id del libro!\n";
        //Funzione getline, che mi permette di andare a leggere tutta le stringa di inserimento, anche se contenete degli spazi! 
            cin>>id; 
        
        libro.setBook_id(id); 

        cout<<"Titolo del libro\n"; 
            cin>>titolo;
        
        libro.setTitle(titolo); 
    
        cout<<"Anno di pubblicazione\n"; 
            cin>>anno; 
        
        libro.setYear(anno); 

        cout<<"Inserimento degli autori!\n"; 
        
        //Poichè un libro può avere uno o più autori, uso un ciclo while per andare ad inserire un autore all'interno del libro!
        do{
            cout<<"Inserisci il nome dell'autore!\n"; 
                cin>>autore;
            
            libro.setAuthor(autore);

            cout<<"Inserire un altro autore?\n"; 
                cin>>risp;

        }while(risp!='n');

        cout<<"Dimmi il costo del libro\n"; 
            cin>>costo; 
        
        libro.setValue(costo); 

        cout<<"Dimmi dove si trova il libro!\n"; 
            cin>>posizione;
        
        libro.setPosition(posizione);

        cout<<"Salvo il libro\n";

        libri.push_back(libro);

        cout<<"Inserire un altro libro?\n", 
            cin>>risp;
        
    }while(risp!='n');

    //Vado ad ordinare il vettore di libri!
    ordinoLibri(libri);

    //Definizione della lista che contiene gli elementi che sono stati dati in prestito
    List<Prestato> prestiti; 

    choice scelta; 

    //Dopo aver inserito i libri faccio fare una scelta all'utente in base all'azione che vuole svolgere|
    while((scelta=failascelta())!=choice::END){
        switch(scelta){
      
        case choice::BORROW:{
           
            cout<<"Vediamo quali elementi sono stati presi in prestito!\n"; 

            char risp; 
            
            for(int i=0; i<libri.size(); i++){
                cout<<"Libro: "<<libri[i].getTitle()<<"\n"; 

                cout<<"Preso in prestito? [y/n]\n"; 
                    cin>>risp;
                
                if(risp=='y'){
                    borrow(prestiti, libri[i]);
                }

            }
            break;
        }

        case choice::VALUE:{
            int numero = valueExpired(prestiti, oggi);
            cout<<"Ci sono: "<<numero<<" libri con scadenza esaurita!\n";
            break;
        }

        case choice::RETURN:{
            returnBook(prestiti, oggi);
            break;
        }

        
        default:
            std::cerr<<"Non ho capito la scelta che hai effettuato!\n";
            break;
        }


    }


    
}


void ordinoLibri(vector<Book>& libri){
    cout<<"Procedo con l'ordinamento dei libri\n"; 

    for(int i=0; i<libri.size(); ++i){
       
        Book key=libri[i];

        int j=i; 

        while(j>0 and key<libri[j-1]){
            libri[j]=libri[j-1];
            j--;
        }

        libri[j]=key;
        
    }
}


choice failascelta(){
    int num; 
    
    cout<<"-------------------------------------\n"; 
    cout<<"[1] - Inserici Libro in prestito\n"; 
    cout<<"[2] - Vedi quanti libri hanno oltrepassato la data di scadenza del prestito\n"; 
    cout<<"[3] - Restituisci un libro e controlla multa\n"; 
    cout<<"[4] - Termina il programma\n"; 
        cin>>num; 
    cout<<"--------------------------------------\n"; 

    choice scelta=(static_cast<choice>(num)); 

    return scelta;
}

void borrow(List<Prestato>& prestiti, Book& prestato){
    //Inserimento all'intern della lista dei prestiti in modo ordinato

    Data p; 
    int g, m, a;

    cout<<"Dimmi la data del prestito [gg/mm/aaaa]\n"; 
        cin>>g >>m >>a; 

    //Definisco un oggetto di tipo prestato

    Prestato elemento;

    elemento.setPrestito(g, m, a);
    elemento.setLibro(prestato);


    //Controllo se nella lista ci sono elementi!
    if(prestiti.empty()){
        //Se è vuota vado ad inserire l'elemento all'interno della
        prestiti.insertFront(elemento); 

    }

    //Se non è vuota eseguo un controllo su dove posizionare il libro!
    else{
        //Scorro la lista degli elementi!
        for(List<Prestato>::Iterator p =prestiti.begin(); p!=prestiti.end(); p++){
            if((*p).scadenza()<elemento.scadenza()){
                //In questo caso faccio l'inserimento all'interno della lista!
                prestiti.insert(p, elemento);
            }
        }
    }


}
int valueExpired(List<Prestato>& elemento, Data& oggi){
    //Controllo il numero di elementi che sono scaduti!

    int num;

    for(List<Prestato>::Iterator p=elemento.begin(); p!=elemento.end(); ++p){
        if((*p).scadenza()<oggi){
            num++;
        }


    }

    return num;
}
void returnBook(List<Prestato>& elemento, Data& oggi ){
    cout<<"Restituisco un libro!\n"; 

    string titolo;

    bool trovato=false;

    cout<<"Dimmi il titolo del libro\n"; 
        getline(cin, titolo);

    for(List<Prestato>::Iterator p=elemento.begin(); p!=elemento.end(); ++p){
        if((*p).getTitolo()==titolo){
            trovato=true;
            cout<<"elemento trovato\n"; 
                if((*p).calcoloMulta(oggi)==0){
                    cout<<"Il libro è stato restituito in tempo!\n";
                    elemento.erase(p);
                    break;
                }

                else{
                    cout<<"C'è una multa per consegna in ritardo!\n"; 
                    cout<<(*p).calcoloMulta(oggi)<<"$\n";
                    elemento.erase(p);
                    break;
                }
        }
    }

    if(!trovato){
        std::cerr<<"Non sono riuscito a trovare l'elemento di cui avevi bisogno!\n";
    }
    

}