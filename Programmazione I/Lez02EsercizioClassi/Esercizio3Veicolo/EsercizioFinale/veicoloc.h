//Classe che descrive il veicolo
//In questo file faccio solo una dichiarazione delle funzioni 
#include <string>




class Vehicle{

    //Dichiaro qui tutte le variabili che sono riservate
    private: 

        std::string make;
        std::string fuelType;
        int yearMan {NULL};
        std::string color;
        std::string engineCap;
    
    public:

        //Dichiaro qui tutte le funzioni di cui è composta la classe    
        Vehicle(std::string make, std::string fuel, int year, std::string color, std::string engine);
        void setMake(std::string make);
        void setFuel(std::string fuel);
        void setYear(int year);
        void setColor(std::string color);
        void setEngine(std::string engine);
        std::string getMake();
        std::string getFuel();
        std::string getColor();
        std::string getEngine();
        int getYear();

        //aggiungo la funzione che consente di mostrate tutto il contenuto della classe
        void displayVehicle();

        
        


};