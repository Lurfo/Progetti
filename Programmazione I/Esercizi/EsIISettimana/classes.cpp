#include "classes.h"
#include <iostream>
#include <sstream> 

//ELEMENTI DELLA CLASSE PROGRAMMER
//Costruttore della classe 
//Imposto dei valori base per questa classe, in modo che ogni elementi venga modificato successivamente
Programmer::Programmer(): id{" "}, paga_h{0}, progetti{}{}

//Costruttore con argomenti
//Per quanto riguarda la lista uso sempre il costruttore di default, vado ad aggiungere gli elementi in un secondo momento
Programmer::Programmer(std::string& idProgrammatore, int paga): id{idProgrammatore}, paga_h{paga}, progetti{}{}


//Specfica delle funzioni set 
void Programmer::setId(const std::string& stringa){
    id=stringa;
}


void Programmer::setPaga(int paga){
    paga_h=paga;
}

//Specifica delle funzioni get dell'id e della paga oraria
std::string Programmer::getId() const{
    return id;
}

int Programmer::getPaga() const{
    return paga_h;
}

//Specifica delle funzioni che vanno a gestire lo stipendio che deve ricevere il programmatore 
int Programmer::getStipendio() const{
    return stipendio_totale;
}

void Programmer::setStipendio(int s){
    stipendio_totale=s;
}

//Specifica delle funzini che fanno riferimento alla lista dei progetti del programmatore 
void Programmer::addProject(Project& elemento){
    //In questo caso, passo come riferimento alla funzione l'elemento che voglio aggiungere alla lista
    //Poichè però la lista è composta da dei puntatori ad elemento, vado a inserire l'indirizzo di memoria di quell'oggetto
    //L'indirizzo di memoria che vado ad iserire è quello degli elementi che sono contenuti nei vettori!
    progetti.push_front(&elemento);
}




std::string Programmer::showProject(){

    std::ostringstream out;

    std::list<Project*>::const_iterator p=progetti.begin();

    if(progetti.empty()){
        out<<"Per ora non ci sono progetti di cui si occupa il programmatore!\n";
    }

    else{
        for(; p!=progetti.end(); ++p){
            out<<"--------------------------\n";
            out<<(*p)->toString()<<"\n";
            out<<"Ore di lavoro per questo progetto: "<<hour((*p))<<"\n";
        }
    }

    return out.str();
}

//DEFINIZIONI DELLE FUNZIONI DELLA MAPPA
//Funzione che inserisce un orario all'interno della mappa!
void Programmer::addHour(Project& progetto, int orario){
    //In questo modo, chiamando la funzione, vado ad inserire all'intr
    tabellaOrariaPerSingoloProgetto[&progetto]=orario;
}

//Funzione che ottiene le ore lavorative per un determinato profetto!
int Programmer::hour(Project* elemento){
    //Basta restituire l'elemento che è presente all'interno della mappa!
    return tabellaOrariaPerSingoloProgetto[elemento];
}

//Tale funzione restituisce il totale di tutte le ore di lavoro del programmatore!
int Programmer::totalHourOfWork(){
    //Definisco una variabile somma
    int somma{0}; 

    //Definisco un iterator
    for(std::list<Project*>::const_iterator p=progetti.begin(); p!=progetti.end(); ++p){
        somma+=tabellaOrariaPerSingoloProgetto[(*p)];
    }

    return somma;
}



//Specifica della funzione che restituisce tutti gli elementi che sono contenuti nella classe, compresi i dati dei programmatori
std::string Programmer::toString(){
    std::ostringstream out; 
   
    out<<"Programmatore: "<<getId()<<"\n";
    out<<"Paga oraria: "<<getPaga()<<"€\n";
    out<<"Totale di progetti di cui si occupa: "<<progetti.size()<<"\n";
    

    return out.str();
}

//Definizione della funzione che va ad azzerare le ore che il programmatore impiega ad ogni progetto!
void Programmer::azzero(){
    //Vado a definire un ciclo for per andare a vedere gli elementi che sono contenuti nella mappa, usando un iterator alla lista delle ore!
    for(std::list<Project*>::iterator p=progetti.begin(); p!=progetti.end(); ++p){
        //Prr eliminare gli elementi che sono contenuti all'interno della tabella, vado ad sfruttare una funzione della stl, che ha il compito di rimuovere gli elementi in base
        //alla chiave, come in questo caso, che le inviamo - Possiamo anche andare ad inviare un iterator della mappa per eliminare quell'elemento!
        tabellaOrariaPerSingoloProgetto.erase((*p));
    }
}


//SPECIFICA DELLE FUNZIONI CHE FANNO PARTE DELLA CLASSE DEI PROGETTI

//Specifica del costruttore di default 
Project::Project(): id{" "}, project_name{" "}, scadenza{}, programmatori{}{}

//Specifica del costruttore che contiene anche altri argomenti!
Project::Project(std::string& idP, std::string& nome, int g, int m, int a): id{idP}, project_name{nome}, scadenza(g, m, a), programmatori{}{}

//Specifica delle funzioni set dei dati membro della clase 
void Project::setIdProject(const std::string& idp){
    id=idp;
} 

void Project::setProjectName(const std::string& nome){
    project_name=nome;
}

//Specifica della funzione che setta la data di scadenza del progetto
void Project::setData(int g, int m, int a){
    //usiamo sempre la funzione della classe data!
    scadenza.setData(g,m,a);
}

//Definizione delle funzioni che restituiscono i valori della classe 
std::string Project::getData(){
    return scadenza.getData();
}


//Funzioni che riguardano La lista dei programmatori 
//Aggiunda di un programmatore 
void Project::addProgrammers(Programmer& prg){
    //In questo modo aggiungo alla lista dei puntatori, il riferimento al programmatore 
    //contenuto nell'array dei programmatori!
    programmatori.push_front(&prg);
}

//Funzione che mostra tutti i programmaotori che sono contenuti nel progetto
std::string Project::getProgrammers(){
    std::ostringstream out; 

    if(programmatori.empty()){
        //Se la lista è vuota, mando questo messaggio!
        out<<"Questo progetto non ha programmatori assegnati\n"; 
    }

    else{
            //Tramite iterator, scorro gli elementi che sono presenti all'interno della lista
            //Prendendo l'id e la paga del programmatore
            for(std::list<Programmer*>::iterator p=programmatori.begin(); p!=programmatori.end(); ++p){
                out<<"Id Programmatore: "<<(*p)->getId()<<"\n"; 
                out<<"Paga Oraria: "<<(*p)->getPaga()<<"\n";
            }
    }

    return out.str();
}

//Funzione che ritorna tutte le specifiche del progetto!
std::string Project::toString(){
    std::ostringstream out; 

    out<<"Id del progetto: "<<id<<"\n"; 
    out<<"Nome del progetto: "<<project_name<<"\n"; 
    out<<"Da consegnare entro: "<<scadenza.getData()<<"\n";

    return out.str();

}
