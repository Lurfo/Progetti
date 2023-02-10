//In questo file vado e specificare tutte le funzioni del gile .h precedente
#include <iostream>
#include <string>
#include "veicoloc.h"

using std::cout;
using std::cin;
using std::endl;

/*Notiamo che ogni volta che andiamo a dichiarare una funzione dobbiamo sempre aggiungere 
Void:: poichè specificiamo che ci faccimo riferimento a quella precisa funzione 
di quella specifica classe*/

//Specifico il constructor della mia classe inserendo tutti i tipi di dati di cui ho bisogno e la condizione di inserimento dell'anno 
//che deve essere maggiore di zero
 Vehicle::Vehicle(std::string make, std::string fuel,int year, std::string color, std::string engine)
          :  make{make}, fuelType{fuel}, color{color}, engineCap{engine}{
                if(year>0)
                    yearMan=year;
            }


//Dichiaro le funzioni che hanno il compito di impostare i valori della classe!
        void Vehicle::setMake(std::string make1){
             make=make1;
         }

        void Vehicle:: setFuel(std::string fuel){
             fuelType=fuel;
         }

        void Vehicle::setYear(int year){
            while(year<0){
                cout<<"Non puoi inserire un anno negativo!\n";
                    cin>>year;
            }

             yearMan=year;
         }

        void Vehicle::setColor(std::string color1){
                color=color1;
        }

        void Vehicle::setEngine(std::string engine){
            engineCap=engine;
        }
       
//Dichiaro le funzioni che hanno il compito di vedere le variabili
    std::string Vehicle::getMake(){
        return make;
    }

    std::string Vehicle::getFuel(){
        return fuelType;
    }

    std::string Vehicle::getColor(){
        return color;
    }

    std::string Vehicle::getEngine(){
        return engineCap;
    }

    int Vehicle::getYear(){
        return yearMan;
    }
    
//Dichiaro la funzione che deve andare a mostrare a schermo le variabili della classe

    void Vehicle::displayVehicle(){
        cout<<"Marca: "<<getMake();
        cout<<"\nColore: "<<getColor();
        cout<<"\nTipo di caburante: "<<getFuel();
        cout<<"\nAnno di produzione: "<<getYear();
        cout<<"\nCavalli del motore: "<<getEngine()<<endl;
    }


