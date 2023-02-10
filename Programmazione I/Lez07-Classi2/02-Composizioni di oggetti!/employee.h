//Classe che va a definire l'impiegato!
#include <string>

//Siccome all'interno degli oggetti di questa classe dobbiamo andare a definire degli altri oggetti,
//dobbiamo definire, in questa classe, da quale classe provengono gli altri oggetti
//andiamo quindi ad includere, anche la classe date!
#include "date.h"

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

//Nota, in questa classe andiamo usare molto il passaggio per riferimento, poichè abbiamo a che fare con dati che occupano grandi quantità di memoria!


class Emp{
    private: 

        //Nella classe che definisce il nostro impiegato, andiamo ad inserire, il suo nome, il suo cognome, ma anche due oggetti di tipo data
        //essi, sono membri dato, di un altra classe e vanno a definire il compleanno e la data di assunzione del nostro impiegato!
        //Li trattiamo esattamente come un qualsiasi altro dato della nostra classe!
        std::string firstName;
        std::string secName;
        Data hireDate;
        Data birthDay;
    
    public:

        //Abbiamo dichiarato una funzione come friend di questa classe, così facendo, tale funzione, può accedere a tutti i dati membro di questa classe!
        //E ovviamente può anche modificarli!

        //ATTENZIONE, TALE FUNZIONE NON CORRISPONDE AD UNA FUNZIONE MEMBRO DELLA CLASSE, MA è UNA FUNZIONE ESTERNA!
        friend void provaAmico(Emp&);

        //Andiamo a dichiarare una variabile di tipo statico in questa funzoine che ha il compito di definire quanti impiegati abbiamo definito nel
        //nostro programma!   
        //ATTENZIONE: Il tipo di variabile che abbiamo qui sotto dichiarato ESISTE INDIPENDENTEMENTE DALL'OGGETTO CHE ABBIAMO DICHIARATO
        //Questo perchè tale elemento è un membro di classe! e on un oggetto della classe! 
        static int empCount;

        //Ovviamente, si ha che il nostro costruttore dovrà andare ad inizilizzare anche i dati relativi alla nostra data!
         explicit Emp(const std::string&, const std::string&, const Data& hireDate, const Data& birthDay);
        //Abbiamo definito anche il nostro Distruttore!
        ~Emp();

        //Andiamo a definire le nostre funzioni memebro!
        //Come nel caso della data, facciamo in modo che esse, restituiscano un puntatore alla nostra classe, in modo da abilitate il cascading!

        Emp& setFirstName(std::string&);
        Emp& setSecName(std::string&);

        //Usiamo un passaggio tramite riferimento in modo da usare un memberwhise assignement!
        Emp& setHireDate(const Data&);
        Emp& setBirthDate(const Data&);

        //Abbiamo poi la classica funzione per trasportare il tutto su una singola stringa!
        std::string toString();

    




};






#endif