//Specifica del driver 
#include "palestra.h"
#include <iostream>

using std::cout; 
using std::cin; 
using std::endl; 
using std::fstream; 
using std::ios;
using std::string;
using std::list;

enum class choice{ADD=1, VEDI, CAMBIO, END};

choice failascelta(); 

//Inizializzo il file binario!
void inizializo(fstream&);

//Salva gli elementi dalla lista al file
void salvataggio(fstream&, Palestra&);
//Carica gli elementi dal  file alla lista!
void caricamento(fstream&, Palestra&);

//Funzione che aggiunge elementi all'interno della lista!
void addElemento(Palestra&); 

void vediClienti(Palestra&);

void modifica(Palestra&);

int main(){

    //Dichiarazione del file con il nome della palestra
    fstream nome{"nome.txt", ios::in | ios::out}; 

    //Definizione della classe palestra
    Palestra palestra;


    string name; 


    if(!nome){
        std::cerr<<"Non riesco ad aprire il file\n"; 
        exit(EXIT_FAILURE);
    }


    nome.seekg(0, ios::end); 


    if(nome.tellg()==0){

        cout<<"Non ci sono nomi per la tua palestra, dimmene uno!\n"; 

        cin>>name;

        //Inserisco il nome all'interno della lista
        palestra.setName(name);

        //Inserisco poi il nome nel file!
        nome.seekp(0); 
        nome.clear(); 

        nome<<name;

    }

    else{

        nome.seekp(0); 
        nome.clear(); 

        nome>>name;

        palestra.setName(name);

        cout<<"Benvenuto a: "<<palestra.getName()<<"\n";

    }


    //Definisco il file in cui inserisco i nomi di coloro che partecipano alla palestra!
    fstream insieme{"clients.dat", ios::in | ios::out | ios::binary}; 


    if(!insieme){
        std::cerr<<"Non riesco ad aprire il file\n"; 
        exit(EXIT_FAILURE);
    }

    //Controllo del numero di elementi del file!
    insieme.seekg(0, ios::end);

    //Se il file è vuoto, vado a inizializzarlo!
    if(insieme.tellg()==0){

        cout<<"Inizializzo il file!\n"; 
        inizializo(insieme);
    }

    else{
        
        caricamento(insieme, palestra);

        
    }

    cout<<"Hai: "<<palestra.size()<<" iscritti!\n";

    choice scelta;

    while((scelta=failascelta())!=choice::END){
      
        switch(scelta){

        case choice::ADD:{
            addElemento(palestra);
            
            break;
        }
           
        
        case choice::VEDI:{

            vediClienti(palestra);
            
            break;
        }


        case choice::CAMBIO:{
            modifica(palestra);
            break;
        }

        
        
        default:
            std::cerr<<"Non ho capito la scelta che devi fare!\n";
            break;
        }
    }

    //Dopo aver effettuato tutti i conti, salvo gli elementi che sono contenuti all'interno della lista, nel file

    salvataggio(insieme, palestra);


}


choice failascelta(){
    int num; 

    cout<<"-----------------------------------\n"; 
    cout<<"[1] - Inserisci cliente nella lista!\n";
    cout<<"[2] - Vedi gli elementi che sono contenuti nella lista!\n";
    cout<<"[3] - Cambia gli elementi che sono contenuti nella list!\n"; 
    cout<<"[4] - Termino il programma!\n";
        cin>>num; 
    cout<<"-----------------------------------\n";

    choice scelta; 

    scelta=(static_cast<choice>(num));

    return scelta; 
}



void inizializo(fstream& insieme){
    cliente clien;

    for(int i=0; i<100; i++){
        insieme.write(reinterpret_cast<char*>(&clien), sizeof(cliente));
    }
}


void salvataggio(fstream& insieme, Palestra& palestra){
    
    cliente cl;

    

    for(list<cliente>::iterator p=palestra.client.begin(); p!=palestra.client.end(); ++p){
        cl=(*p);

        insieme.seekp(cl.getCode()*sizeof(cliente));

        insieme.write(reinterpret_cast<char*>(&cl), sizeof(cliente));
    }
    

}


void caricamento(fstream& insieme, Palestra& palestra){
    cout<<"Vado a caricare gli elementi all'interno della lista della palestra!\n"; 

    insieme.seekg(0); 

    cliente cl;

    for(int i=0; i<100; i++){
        
        insieme.read(reinterpret_cast<char*>(&cl), sizeof(cliente)); 

        if(cl.getCode()!=0){
            palestra.aggiungiElemento(cl);
        }

    }

}


void addElemento(Palestra& palestra){
    cout<<"Inseriamo un nuovo elementi all'interno della lista palestra!\n";

    cliente cl; 
    
     int  code; 
     string name; 
     string cognome; 

     int g,m,a;

     cout<<"Dimmi il numero del cliente\n"; 
        cin>>code; 

    if(palestra.trovato(code)){
        cout<<"Esiste già un elemento con questo codice!\n"; 
        return;
    }

    else{

        cout<<"Dimmi il nome:\n"; 
            cin>>name; 
        
        cout<<"Dimmi il cognome:\n"; 
            cin>>cognome; 
        
        cout<<"Dimmi giorno, mese e anno di scadenza\n";
            cin>>g >>m >>a;
        
        cl.setName(name); 
        cl.setSecond(cognome); 
        cl.setCode(code); 
        cl.setData(g,m,a);

        palestra.aggiungiElemento(cl);

    }
    

}
void vediClienti(Palestra& pa){

    cout<<"Sono nella visione\n";
 
    list<cliente>::iterator p=pa.client.begin();

    for(p; p!=pa.client.end(); ++p){
        cout<<"++++++++++++++++++++++++++++++++++\n";
        cout<<"Codice cliente: "<<(*p).getCode()<<"\n"; 
        cout<<(*p).getName()<<" "<<(*p).getSecond()<<"\n"; 
        cout<<"Scadenza abbonamento: "<<(*p).getData()<<"\n";
    }
    

}

void modifica(Palestra&){}