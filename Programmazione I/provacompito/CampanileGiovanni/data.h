//Creo la classa Data 
#include <string>


#ifndef DATA_H
#define DATA_H


class Data{

    //Andiamo a definire l'overload dell'operatore che permette di mostrare a video la dats che abbiamo
    //In particolare, l'overload di alcuni operatori viene effettutuato in modo tale da poterci permettere di definire in che modo andare a definire
    //La posizione degli operandi!
    //NOTA:Vedi il caso dell'addizione!

    friend std::ostream& operator<<(std::ostream&, const Data&);
    

    //Come detto sopra, per la somma dobbiamo andare a definire due funzioni differenti in base alla posizione dei due addendi:
    //1-Il primo caso infatti considera quando svolgiamo d+7
    //2-Il secondo caso vale quando abbiamo 7+d
    //La specifica sarà sempre definita all'interno del driver
    friend Data operator+(const Data&, int);
    friend Data operator+(int, const Data&);


    private: 

        //Tre tipi di valori di interi che servono per definire la data
    
        unsigned int day;
        unsigned int month;
        unsigned int year;

        //Dichiaro come private le funzioni che hanno il compito di impostare i dati
        //Voglio nascondere in che modo i dati vengono implementati
        void setDay(int);
        void setMonth(int);
        void setYear(int);

        //Contiene il numero di giorni per ogni mese
        const int dayPerMonth[13]{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};


        //Funzione che definisce l'incremento della data
        void increment();

        //Funzione che definisce il decremento della data
        void decrement();
        
    public: 

        //Costrutto con elementi di default
        //Impostiamo una nuova data di dafault in modo che venga definito un valore per i pacchi che non hanno data di scadenza "standard!"
        Data(int =31, int =12, int=2121);
        //Definisco il costruttore
        ~Data();

        //Funzione che va ad impostare la data
        void setData(int, int, int);

        //Funzione che ha lo scopo di prelevare la data
        std::string getData();

        //vado a ridefinire l'operatore < rispetto ad una data
        bool operator<(const Data& );

        //vado a definire la funzione che corrisponde al pre-incremento!
        Data& operator++();

        //Definisco il post-incremento
        //Nota: il parametro in necessario ad essere utilizzato in questo caso non viene specificato
        //è richiesco solo per andare a differire l'operatore pre-fisso a quello post-fisso
        Data operator++(int);

        //Definisce l'operazione di somma rispetto con un intero!
        //NOTA: Parliamo dell'operatore di somma +=! Che va a modificare l'oggetto!
        Data& operator+=(int); 

        //definizione dell'operatore !=
        bool operator!=(const Data&);

        //Definizione dell'operatore >
        bool operator>(const Data&);


        //Definizione dell'operatore di pre-decremento!
        Data& operator--();

        //Definizione dell'operatore di post-decremeto!
        Data operator--(int);

        //Definizione dell'operatore -=
        Data& operator-=(int);

        //Avendo definito l'operatore -=, come fatto anche con la somma, possiamo andare dichiarare la sottrazione di una data con un intero!
        //Usando sempre le funzioni friend, che sono quelle più convenienti da utilizzare!

        //Definizione dell'operatore uguale!
        Data& operator=(const Data&);
        



};

#endif