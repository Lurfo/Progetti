//Genero una classe abstract che ha il compito di definire tutti i parametri base di ogni impiegato!
#include <string>


#ifndef EMPLOYEES_H
#define EMPLOYEES_H
//Classe Base Abstract!
class Employees{

    private:

    //Dati necessari per andare ad identificare tutti gli elemeti di ogni lavoratore!
    std::string name;
    std::string cognome;
    std::string SSN; //Equivalente del codice fiscale;

    public:
        //Costruttore 
        Employees();
        Employees(const std::string&, const std::string&, const std::string&);

        //ATTENZIONE
        //Poichè stiamo considerando delle funzioni che hanno dei membri virtual, importante è andare anche a definire dei distruttori Virtual!
        //In questo modo non incorriamo in eventuali errori quando andiamo a chiamare dei distruttori in merito ad alcuni oggetti!
        virtual ~Employees()=default; //Facciamo in modo che il compilatori generi il distruttore virtuale di default

        void setName(const std::string&);
        void setCognome(const std::string&);
        void setSSN(const std::string&);
        std::string getName();
        std::string getCognome();
        std::string getSSN();

        //Vado a definire tutte le funzioni virtual che devo andare a riscrivere con le classi derivate!
        virtual double guadagni()=0; //Funzione pure Virtual!
        virtual std::string toString();

        //Definizione della funzione che calcola il bonus che il dipendente riceve!
        virtual double bonus()=0;




};


#endif