//Definizione del programma che va ad inserire gli elementi all'interno di un file e nel record!
#include "dict.h"
#include <iostream>
#include <fstream>
#include <vector>

using std::cout; 
using std::cin; 
using std::endl; 
using std::fstream;
using std::ios;
using std::vector; 
using std::string;

enum class choice{SEAR=1, ADD, VEDO, ORIDNO, END};

//Specifica della funzione che serve per andare a fare la scelta della funzione da chiamare!
choice makechoice();

//Funzioni che devo implementare per gestire gli elementi che ho nel file
//Poichè io ho tutti gli elementi che sono inseriti all'interno del file, posso andare a passare alle funzioni, il vettore tramite riferimento, in questo caso gestisco il tutto molto
//meglio!
void ricerca(vector<Diz>&);
void add(vector<Diz>&, const string& =" "); 
void vedere(vector<Diz>&);

//Definizione di una funzione utile per l'ordinamento!
void ordinamento(vector<Diz>&);


int main(){
    //Definizione del file in cui inserire gli elementi!
    //Deve essere aperto sia in modalità di inserimento che in modalità di lettura!
    fstream dizionario{"dizionario.txt", ios::in | ios::out};

    vector<Diz> insieme;

    Diz parola;

    //Definizioni delle stringhe che devono essere utilizzare dal while per inserire le parole contenute nel dizionario!
    string inglese; 
    string italiano;

    //Definisco una variabile di scelta!
    choice scelta;


    if(!dizionario){
        std::cerr<<"Mi dispiace, non riesco ad aprire il file!\n";
        exit(EXIT_FAILURE);
    }

    //Vado ad inserire gli elementi presenti nel file all'interno del vettore
    while(!dizionario.eof() && (dizionario >>inglese >>italiano)){
        //Inserisco questi elementi all'interno della classe che ho definito
        parola.setIng(inglese); 
        parola.setIta(italiano);

        //Faccio la copia della classe all'interno del vettore!
        insieme.push_back(parola);
    }

    cout<<"Hai attualmente: "<<insieme.size()<<" parole allocate!\n";

    //Il ciclo while continua fino a quando vado a definire la mia scelta!
    while((scelta=makechoice())!=choice::END){
        switch (scelta){

        case choice::SEAR:{
            ricerca(insieme);
            break;
        }
        
        case choice::ADD:{
            add(insieme);
            break;
        }

        case choice::VEDO:{
            vedere(insieme);
            break;
        }

        case choice::ORIDNO:{
            ordinamento(insieme);
            break;
        }
        
        default:
            std::cerr<<"Non ho capito la richiesta, riprova\n";
            break;
        }
    }

    //Dopo aver completato tutte le funzioni di cui avevamo bisogno, devo andare a reinserire tutti gli elementi dal vettore nel file!

    //Sposto il puntatore all'inizio!
    dizionario.clear();
    dizionario.seekp(0, ios::beg);
    
    //Con un ciclo for ado a sorrere tuttu gli elementi che sono all'interno del vettore!
    for(int i=0; i<insieme.size(); i++){
        //Definisco che la classe è uguale a quella contenuta
        parola=insieme[i];
        
        //Inserisco gli elementi del vettore nel file!
        dizionario<<parola.getIng()<<" "<<parola.getIta()<<endl;

    }
}


choice makechoice(){
    int num;

    cout<<"-----------------------------------------------------\n";
    cout<<"[1] - Ricerca di un elemento nel dizionario!\n"; 
    cout<<"[2] - Inserimento di un elemento nel dizionario\n"; 
    cout<<"[3] - Vedi gli elementi che sono presenti nel dizionario\n"; 
    cout<<"[4] - Ordina gli elementi del vettore\n"; 
    cout<<"[5] - Termino il programma\n"; 
        cin>>num; 
    cout<<"-----------------------------------------------------\n";

    //Faccio un cast per andare a definire il valore della scelta uso un casting per definire la variabile choice
    choice scelta{static_cast<choice>(num)}; 

    return scelta;
}



//Definizione della funzione di ricerca
void ricerca(vector<Diz>& insieme){
  
    string chiave; 

    char risp;

    bool trovato=false;

    int i=0;

 
    if(insieme.size()==0){
        std::cerr<<"Non ci sono ancora elementi nel vettore, si prega di inserire almeno un record!\n"; 
        return;
    }


    cout<<"Dimmi la parola che vuoi tradurre\n"; 
        cin>>chiave;

    while(i<insieme.size()){
      
        if(insieme[i].getIng()==chiave){
            trovato=true;
            break;
        }

        i++;

    }

    if(trovato){
        cout<<"Significa: "<<insieme[i].getIta()<<"\n";
    }

    else{

        cout<<"Non so cosa vuol dire\n"; 
        cout<<"Inserire il significato? [y/n]\n"; 
            cin>>risp; 
        
        while(risp!='y' and risp!='n' and risp!='Y' and risp!='N'){
            cout<<"Specifica una risposta valida!\n"; 
                cin>>risp;
        }

        if(risp=='y'){ 
            add(insieme, chiave);
        }

        else{
            cout<<"Ritorno al menù\n";
        }
        

    }


}

void add(vector<Diz>& insieme, const string& chiave){

    string parola = chiave; 

    string significato;

    if(parola==" "){
        cout<<"Dimmi la parola che vuoi inserire!\n"; 
            cin>>parola;
    }

    cout<<"Dimmi il significato\n"; 
        cin>>significato;

    cout<<"Salvo il significato all'interno del vettore!\n"; 
    
    Diz record(parola, significato);

    insieme.push_back(record);

}

void vedere(vector<Diz>& insieme){

    if(insieme.size()==0){
        std::cerr<<"Non ci sono elementi salvati, si prega di inserirne al meno uno\n";
        return;
    }

    for(int i=0; i<insieme.size(); i++){
        cout<<insieme[i].getIng()<<"->"<<insieme[i].getIta()<<"\n";
    }

}

void ordinamento(vector<Diz>& insieme){
    cout<<"Ordino gli elementi del vettore!\n";

    //In questo caso vado a utilizzare, come algoritmo di ordinamento un insertionSort!


    for(int i=0; i<insieme.size(); i++){
        
        //Definisco la chiave da considerare
        Diz key=insieme[i];

        //Definisco una variabile che mantiene la posizione massima a cui sono arrivato
        int j=i;

        while(j>0 and key<insieme[j-1]){

            insieme[j]=insieme[j-1]; 
            j--;

        }

        insieme[j]=key;
    }

}
