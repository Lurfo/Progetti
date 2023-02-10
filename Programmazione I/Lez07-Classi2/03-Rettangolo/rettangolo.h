//Andiamo quindi a dichiarare la funzione che ha il compito di rappresentare il nostro rettangolo
//Poichè il rettangolo contiene degli oggetti di tipo point, allora dobbiamo necessariamente includere la classe point.h
//Così facendo abbiamo quindi inserito la classevh
#include "point.h"

#ifndef RETTANGOLO_H
#define RETTANGOLO_H

class Rett{

    friend const void vedo(Rett&);

    //Ovviamente andiamo ad inserire le variabili membro della classe, essi sono tutti quanti degli oggetti di tipo point
    private:
        Point p1;
        Point p2;
        Point p3;
        Point p4;
        char fill; 
        char peri;

    public:

        //Vado a dichiarare il costruttore per il nostro rettangolo!
       explicit Rett(const Point& =Point(0.0, 0.0), const Point& =Point(1.0, 0.0), const Point& =Point(0.0, 1.0), const Point& =Point(1.0, 1.0), char ='*', char ='-');


       //Definisco anche il distruttore per il mio rettangolo!
       ~Rett(); 
       //Vado a impostare la funzione che ha il compito di impostare i punti, qual'ora fossero differenti da quelli di default o vogliono essere modificati!
       void setPoint(Point, Point, Point, Point);

       //Vado a impostare le funzioni che hanno il compito di andare a impostare il carattere che deve definire il perimetro
       void setPeriChar(char);
       void setFillChar(char);

       //Vado a dichiare le funzioni che hano il compito di definire la lunghezza e l'altezza del rettangolo!
       double altezza() const;
       double larg() const;

       //Vado a definire le funzioni che hanno il compito di trovare l'area e il perimetro del rettangolo!
       double perimetro() const; 
       double area() const;

       //Imposto la funzione che ha il compito di disegnare il settangolo!
       void disegno() const;



        



};





#endif