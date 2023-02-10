//Definizione del driver che gestisce la classe 
#include "box.h"
#include <iostream>
#include <fstream>
#include <iomanip>

using std::cout; 
using std::cin; 
using std::endl; 
using std::fstream; 
using std::ios; 

enum class choice{INS=1, DELETE, UPDATE, STAMP, INIZ, END};

//Definizione della funzione che ha il compito di far fare all'utenza la scelta di quale compito svolgere!
choice makeChoice();

//Funzione che ha il compito di andare a trovare il numero della scatola che devo ricercare
int findBox(const std::string&);

void inizialize(fstream&); 
void insert(fstream&); 
void deleteRecord(fstream&); 
void updateRec(fstream&);
void stampList(fstream&);



int main(){
    //Definizione del file che devo aprire!
    //Lo vado aprire sia in modalità di inserimento che in modalità di lettura!
    fstream magazzino{"hardware.dat", ios::in | ios::out | ios::binary};

    choice scelta; 

    if(!magazzino){
        std::cerr<<"Non riesco ad aprire il file!\n";
    }

    else{

        //come prima cosa vado a controllare se il file che ho inserito è vuoto
        //sposto quindi il puntatore del file alla fine!
        magazzino.seekg(0, ios::end);

        if(magazzino.tellg()==0){
            cout<<"Il file è vuoto!\n"; 
            cout<<"Come prima cosa occorre inizializzare il file!\n";
            //L'inizializzazione è importante, vado ad inserire tanti elementi nuovi, vuoti, all'interno del file!
            //in modo che alle successive chiamate può svolgere il suo lavoro come richiesto!
                inizialize(magazzino);
        }

        //Definiziamo un ciclo while, che in funzione della scelta che effettuaiamo all'inizio ci permette di svolgere le varie funzioni che ci occorrono!
        while((scelta=makeChoice())!=choice::END){

            //Uso lo switch per andare a considerare le differenti opzioni che richiede il programma!
            switch (scelta){
                case choice::INS:{
                    insert(magazzino); 
                    break;
                }

                case choice::DELETE:{
                    deleteRecord(magazzino);
                    break;
                }

                case choice::UPDATE:{
                    updateRec(magazzino); 
                    break;
                }

                case choice::STAMP:{
                    stampList(magazzino);
                    break;
                }

                //Inserico anche una scelta per andare ad eliminare tutti gli elementi che sono conrenuti all'interno del file!
                case choice::INIZ:{
                    inizialize(magazzino);
                    break;
                }

                default: 
                    cout<<"La scelta effettuata non è valida, riprovare!\n";
            }

            //Alla fine del while, utilizzo una funzione della libreria fstream, che ha il compito di andare a riposizionare il puntatore
            //In questo modo alle successive chiamate delle funzioni il file sarà sempre pronto a funzionare!
            magazzino.clear();
            
        }

    }
    
}

choice makeChoice(){
    int num; 
    
    cout<<"-------------------------------------\n";
    cout<<"[1] - Inserimento all'interno della lista\n"; 
    cout<<"[2] - Elimina un elemento dalla lista\n"; 
    cout<<"[3] - Aggiorna un elemento nella lista\n"; 
    cout<<"[4] - Stampa la lista degli elementi presenti\n"; 
    cout<<"[5] - Elimino tutto il contenuto del file!\n";
    cout<<"[6] - Termino il programma\n"; 
        cin>>num; 
    
    cout<<"-------------------------------------\n";
    
    choice scelta{static_cast<choice>(num)};

    return scelta;
}

int findBox(const std::string& msg){
    
    cout<<msg<<"\n";

    int num;
    
    do{
            cin>>num; 
        
        if(num<1 && num>100){
            cout<<"Il numero deve essere compreso tra [1-100]\n"; 
            cout<<"Inserire un nuovo numero\n";
        }

    }while(num<1 or num>100);

    //Poichè nel file vado a salvare gli elementi partendo dalla posizione 0 fino alla posizione 99, devo sempre togliere uno dalla definizione del numero
    return num-1;
}

//Definizione della funzione di inizializzazione
void inizialize(fstream& file){
    //Sposto il puntatore del file all'inizio!
    file.seekp(0, ios::beg); 

    //Definisco un nuovo account box, vuot!
    Box inizio;

    for(int i=0; i<100; i++){
        //Per scrivere i dati all'interno del file, in formato binario, posso andare a sfruttare la funione write 
        //Vado quindi a salvare il valore il valore dell'oggetto vuoto e sposto il puntatore del file, per una dimensione pari a quella della classe Scatola 
        //Motivo per cui tutti gli elementi che vado ad inserire all'interno del file devono avere la medesima dimensione!
        file.write(reinterpret_cast<char*>(&inizio), sizeof(Box));
    }

    cout<<"Ho inizializzati il file!\n";

}


//Specifica della funzione di inserimento di un elemento!
void insert(fstream& file){

    //Definisco un oggetto di tipo box!
    //Ci serve per inserire i dati che dobbiamo mettere nel file!
    Box nuovo;

    cout<<"Inserimento di un elemento all'interno della lista\n";

    std::string nomeProdotto;
    int quantit;
    double prezzo;

    //Come prima cosa trovo il valore del codice, mi serve per andare a verificare se il valore descritto nella posizione, è occupato o meno!
    int numero=findBox("Inserisci il codice iniziale della scatola!");

    //sposto il puntatore per trovare l'elemento che si trova al numero che ho cercato!
    file.seekg(numero*sizeof(Box), ios::beg);
    //Con la funzione read, vado a leggere il contenuto nel file che si trova in quella posizione!
    file.read(reinterpret_cast<char*>(&nuovo), sizeof(Box));

    //In questo caso se l'elemento che ho definito ha come codice 0, allora vuol dire che la posizione è vuota, dunque posso inserire l'elemento!
    if(nuovo.getCode()==0){

        cout<<"Dimmi il nome del prodotto\n"; 
            cin>>std::setw(15)>>nomeProdotto; 
        
        cout<<"Inserisci la quantità di prodotti\n"; 
            cin>>quantit; 

        cout<<"Dimmi il prezzo del prodotto\n"; 
            cin>>prezzo; 

        //cambio quindi i valori della classe box! 
        nuovo.setCode(numero+1); 
        nuovo.setName(nomeProdotto); 
        nuovo.setQuant(quantit); 
        nuovo.setPrice(prezzo);

        //sposto quindi il puntetore di inserimento alla posizione designata dal  numero!
        file.seekp(numero*sizeof(Box));
        //Uso quindi la funzione write per andare ad inserire l'elemento nel file
        file.write(reinterpret_cast<char*>(&nuovo), sizeof(Box));


    }

    else{
        std::cerr<<"La posizione che hai specificato è già occupata da un elmento\n";
    }
    

} 

void deleteRecord(fstream& file){

    Box elimino;

    cout<<"Vado ad eliminare un record!\n"; 

    int numero=findBox("Dimmi il codice che vuoi eliminare dal file");

    //Come al solito vado a cercare se l'elemento che ho definito è già vuoto o meno
    file.seekg(numero*sizeof(Box));
    //Uso la funzione read!
    file.read(reinterpret_cast<char*>(&elimino), sizeof(Box));

    if(elimino.getCode()!=0){
        cout<<"Elimino il valore che mi hai dato\n";

        //La cosa semplice da fare è sostituire il record presente con uno che è inizializzato comevuoto!
        
        //Creao quindi il valore vuoto
        Box vuoto; 

        file.seekp(numero*sizeof(Box)); 
        file.write(reinterpret_cast<char*>(&vuoto), sizeof(Box));

    }

    else{
        std::cerr<<"Guarda che il record è già vuoto\n";
    }
    


}

void updateRec(fstream& file){
    
    Box modificabile;

    std::string name; 
    int q; 
    double p;

    int numero=findBox("Dimmi il numero del record che vuoi modificare\n");

    file.seekg(numero*sizeof(Box)); 
    file.read(reinterpret_cast<char*>(&modificabile), sizeof(Box));

    if(modificabile.getCode()!=0){
        cout<<"Dimmi il nome:\n"; 
            cin>>std::setw(15)>>name; 
        
        cout<<"Dimmi la quantità\n"; 
            cin>>q; 
        
        cout<<"Dimmi il prezzo\n"; 
            cin>>p; 
        
        modificabile.setName(name); 
        modificabile.setQuant(q);
        modificabile.setPrice(p);

        //Sposto il puntatore di inserimento
        file.seekp(numero*sizeof(Box)); 
        file.write(reinterpret_cast<char*>(&modificabile), sizeof(Box));
    }

    else{
        std::cerr<<"Il valore del numero che hai inserito corrisponde ad un record vuoto!\n";
    }
    

}

void stampList(fstream& file){
    Box vedo; 

    file.seekg(0); 

    while(!file.eof()){

        file.read(reinterpret_cast<char*>(&vedo), sizeof(Box));

        if(vedo.getCode()!=0){
        cout<<"Prodotto numero: "<<vedo.getCode()<<"\n";
        cout<<"Nome: "<<vedo.getName()<<"\n"; 
        cout<<"Quantità: "<<vedo.getQuant()<<"\n"; 
        cout<<"Prezzo: "<<vedo.getPrice()<<"\n";
        }
    }

}
