//Vado a scrivere la classe che mi permette di poter creare il gioco del tris
//essa quindi deve contenere tutti i dati riguardanti la partita:
//-Stato della partita 
//-mosse effettuare e posizione delle pedine

//Deve stampare a video il tabellone gioco con le caselle occupate 
//Deve permettere al giocatore di effettuare una mossa!
#include <array>

#ifndef TRIS_H
#define TRIS_H

class Tris{

    private: 
        //Andiamo a dichiarare la tabella con cui dobbiamo giocare come un array 3x3!
        //Ovviamente questo array deve contenere solo dei valori char - corrispondenti alle due pedine di gioco!
        std::array<std::array<char, 3>,3> tab;

        //Per definire lo stato in cui ci troviamo dobbiamo andare a utilizzare la classe enum, che contiene 3 possibili situazioni differenti!
        enum Status{DRAW, WIN, CONTINUE};

    //Abbiamo concluso le variabili membro della classe!

    public: 

        //Andiamo a definire il costruttore di default
        Tris();
        //Ovviamente si devinisce anche il distruttore!
        ~Tris();

        //Vado ad impostare la funzione che ha il compito di stampare tutta la tabella!
        void vedo() const;

        //Imposto la funzione che ha il compito di effettuare la mossa!
        void makeMove();
        //Accanto a questa abbiamo bisogno di utilizzare due funioni:
        bool validateMove(int, int) const;//Questa ha il compito di verificare che la mossa desiderata può essere effettivamente svolta
        bool xoMove(char);//Questa è la funzione che ha il compito di scegliere chi deve effettuare la mossa!

        Status gameSet();//Questa funzione ha il compito di definire in che situazione della partita ci troviamo!

};


#endif
