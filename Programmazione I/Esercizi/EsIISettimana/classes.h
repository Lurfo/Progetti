//Definizione della classe programmer
#include <string>
#include <list>
#include <map>
#include "data.h"

#ifndef CLASSES_H
#define CLASSES_H

class Programmer; 
class Project;

class Programmer{
   
    public: 
        //Id del programatore
        std::string id; 

        //Paga in base oraria
        int paga_h;

        //In questa variabile salvo lo stipendio che deve ricevere il programmatore in base alle ore di lavoro!
        int stipendio_totale;

        //Definizione della lista dei progetti a cui lavora il programmatore 
        std::list<Project*> progetti; 

        //Vado a definire all'interno della classe programmer la mappa che contiene, per ogni elemento della lista, l'orario di lavoro totale
        //vedo che la key di ricerca, il primo elementi è un puntatore al progetto, mentre l'elemento da ricercare è proprio l'orario!
        std::map<Project*, int> tabellaOrariaPerSingoloProgetto;


    public: 
        //Specifica del costruttore
        Programmer(); //Costruttore di default

        //Specifica del costruttore con argomenti
        Programmer(std::string&, int);

        //Funzioni set dei parametri della classe
        void setId(const std::string&); 
        void setPaga(int); 

        //Specifica delle funzioni che restituiscono gli elementi che sono presenti nella classe 
        int getPaga() const; 
        std::string getId() const; 

        //Definizione delle funzioni che impostano e prelevano il pagamento totale 
        int getStipendio() const; 

        void setStipendio(int);

        //Specifica della funzione che aggiunge un elemento alla lista dei progetti
        void addProject(Project&);

        int getProjectNum() const; 
        
        //Stampa a video i progetti che sono definiti dal programmatore!
        std::string showProject(); 

        //DEFINIZIONE DELLE FUNZIONI DELLA MAPPA 

        //Funzione che inserisce il valore delle ore di lavoro in funzione del progett
        void addHour(Project&, int);

        //Funzione che restituisce il valore delle ore del progetto 
        int hour(Project*);

        //Funione che restituisce la somma totale delle ore di lavoro per ogni progetto!
        int totalHourOfWork();

        std::string toString(); //Stampa a video tutti gli elementi che sono contenuti all'interno della classe, compresi i progetti a cui lavora il programmatore

        //Specifica della funzione che ha il compito di andare ad azzerare le ore di lavoro che il programmatore ha svolto su un progetto
        void azzero();
};



class Project{

    private:
        std::string id; 
        std::string project_name;
      
        Data scadenza;

        std::list<Programmer*> programmatori;

    public: 
        Project(); //Costruttore di default per la classe!
        //Specifica del costruttore che contiene degli elementi
        Project(std::string&, std::string&, int, int, int);

        //Specifica delle funzioni set e get delle 3 variabili membro
        void setIdProject(const std::string&); 
        void setProjectName(const std::string&); 

        //La funzione di set della data ad utilizzare la funzione già presente all'interno dell'oggetto data!
        void setData(int, int, int);

        //Specifica delle funzioni get
        std::string getIdProject() const; 
        std::string getProjectName() const; 

        //Per restituire la data posso usare una funzione che restituisce la stringa 
        std::string getData(); 

        //Faccio in modo anche di ricevere i singoli elementi della data!
        int getDay() const; 
        int getMonth() const; 
        int getYear() const; 

        //Funzione che aggiunge un elementi alla lista dei programmatori!
        void addProgrammers(Programmer&);

        //Funzione che ritorna gli elementi che sono contenuti all'interno della lista
        std::string getProgrammers(); 

        //Funzione che restituisce tutto il contenuto della classe
        std::string toString();
};


#endif