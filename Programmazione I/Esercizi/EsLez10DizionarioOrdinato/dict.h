//definizione della classe dizionario
#include <string>

#ifndef DICT_H
#define DICT_H

class Diz{
  
    private: 

        std::string ing; 
        std::string ita;

    public: 

        Diz(const std::string& inglese=" ", const std::string& italian=" "): ing{inglese}, ita{italian}{}


        void setIng(const std::string& parola){
            ing=parola;
        }

        std::string getIng() const{
            return ing;
        }

        void setIta(const std::string& parola){
            ita=parola;
        }

        std::string getIta() const{
            return ita;
        }

        Diz& operator=(const Diz& second){
           
            ing=second.ing; 
            ita=second.ita;

            return *this;
        }

        bool operator<(const Diz& second){
            //Definisco, come operazione all'interno del minore, il confronto tra le due stringhe dei valori in inglese!
            //tale operatore è necessario per andare a svolgere le operazioni di confronto con l'utilizzo dell'algoritmo di ordinamento!
            return ing<second.ing;
        }

        //Definizione dell'operatore di confronto!
        //Utile per sfuttarla nella funzione di inserimento!
        bool operator==(const Diz& second){
            return ((ing==second.ing) && (ita==second.ita));
        }


};




#endif