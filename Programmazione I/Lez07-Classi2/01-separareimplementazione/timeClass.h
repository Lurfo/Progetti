//Andiamo a creare una classe che ha il compito di memorizzare i dati relativi all'orario che gli viene fornito dell'utente!
//Per questo tipo di classe, sfruttiamo un implementazione separata delle funzioni!
//Nel seguente file vengono solo dichiarate le variabili e le funzioni che compongono la classe!
#include <string>


//Questa è una direttiva molto importante all'interno della classe che viene svolta direttamente dal pre-processore, come tutte le direttive che sono
//precedetute da #!
//In queto caso, tale comando avvisa al pre-processore, che queal'ora questo file non sia stato già incluso, può includerlo, altrimenti non viene incluso 
//nuovamente. Tale direttiva, serve proprio per evitare che un file, in questo caso quello che definisce tale classe, venga incluso più volte!
//Ovviamente questo non è il caso in cui può accadere, abbiamo pochi file, ma in un programma che sfrutta molti file .h è qualcosa che può accadere!
#ifndef TIME_H
#define TIME_H

class Time {

private: 
    unsigned int hour;
    unsigned int minut;
    unsigned int sec;

public: 
    //Questo è il nostro costruttore, che andiamo ad usare per definire i valori iniziali della nostra classe!
    //NOTA:Nonostante prenda in ingresso 3 argomenti, li andiamo a dichiarare come explicit, questo perchè, possiamo sceliere anche di inserirne solo uno di essi!
    explicit Time(int =0, int =0, int =0);

    //Oltre ad un construttore, possiamo anche generare un distruttore, esso ha il compito di andare ad eliminare dalla memoria gli oggetti che non sono più utilizzati
    //Quindi un distruttore viene chiamato ogni qualvolta che un elemento oggetto della classe finisce il suo scopo!
    //Se non viene esplicitamente dichiarato, il compilatore chiama un distruttore di default!

    //COME MAI SONO IMPORTANTI? 
    //Sono specialmente utili quando dobbiamo usare una gestione dinamica della memoria! ci permettono infatti di liberare le zone di memoria 
    //che non devono più essere utilizzate!
    
    //In particolare un distruttore è una funione che può non avere argomenti e anche non avere nessun valore di ritorno!

    //In particolare, il distruttore viene definito in questo modo, andando ad anteporre prima del nome della funzione(che ovviamente
    //deve essere uguale al nome della classe), una tile(alt+0126)!
    ~Time();

    //Funzione che ha il compito di inserire i valori dell'orario
    void setTime(int, int, int);
    
    //Queste sono due funzioni che restituiscono una stringa e che hanno il compito di mostrare l'orario, una volta in formato 0-24
    //l'altra in formato 0-12 AM/PM
    std::string toUniversal() const;
    std::string toStandard() const;
};







#endif