//Andiamo a scriver la classe data che sarà poi inclusa all'interno della classe che contiene i dati dei lavoratori!
#include <string>

//Andiamo sempre ad inserire il nostro controllo per evitare di andare a includere più volte la stessa classe!
#ifndef DATE_H
#define DATE_H


class Data{

    private: 
        unsigned int day;
        unsigned int month;
        unsigned int year;

        //Voglio nascondere l'implementazione per il controllo dell'esattezza della data!
        //Funzione che serve per controllare se la data inserita è corretta, rispetto al mese e all'anno!
        unsigned int  checkDay(int) const;

    public:

        //Andiamo a dichiarare anche un contenggio per la nostra data!
        static int count;

        //Costruttore della nostra classe, inizializzata con valori di defaul a 01/01/1900
        explicit Data(int =1, int =1, int =1900);
        //Distruttore della nostra classe che ci fa vedere quando il nostro oggetto viene eliminato!
        ~Data();

        //Funzione che ci permette di andare a mostrare a schermo la nostra data restituendo una stringa!
        std::string toString() const;

        //Andiamo a creare delle funzioni che hanno il compito di definire il giorno, il mese e l'anno!
        //In modo che ogni singola funzione può andare ad eseguire un controllo su ogni dato che andiamo ad inserire!
        //In questo modo possiamo anche fare inserire dei cambiamenti all'utente qual'ora ce ne fosse bisogno!

        //Come vediamo, le funzioni che qui abbimo, sono di tipo data, se infatti controlliamo la loro implementazione, esse restituiscono un puntatore
        //tale puntatore "this" è quello che viene definito implicitamente alla classe e serve proprio per andare ad accedere ad ogni memebro di questa classe
        //evitando di creare errori o confusione nel nome!
        //Come mai è conveniente adottare questo tipo di scelta? 
        //In questo modo, possiamo andare ad attivare il meccanismo di cascata, possiamo cioè implementare differenti funzioni sulla stessa riga di comando!
        //Possiamo cioè scrivere dat.setDay().set(Month).setYear(), che rappresenta, appunto, il meccanismo a cascata!
        Data& setDay(int);
        Data& setMonth(int);
        Data& setYear(int);








};







#endif