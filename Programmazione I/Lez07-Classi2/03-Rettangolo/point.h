//Vado a creare la classe che descrive i punti del nostro rettangolo!

#ifndef POINT_H
#define POINT_H

class Point{

    public:

        //Abbiamo definito il costruttore per la nostra classe
        explicit Point(double =0.0, double =0.0);
        //Definiamo anche il distruttore per la nostra classe
        ~Point();

        //Queste sono le funzioni che servono per prelevare e per inserire i dati all'interno della nostra classe!
        void setPointX(double);
        void setPointY(double);
        double getPointX() const;
        double getPointY() const;

    private:

        //Dobbiamo ricordare che i valori dei punti x e y devono essere compresi tra 0 e 25
        double x;
        double y;





};





#endif