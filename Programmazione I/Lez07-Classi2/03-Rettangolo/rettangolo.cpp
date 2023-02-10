#include "rettangolo.h"
#include <stdexcept>
#include <iomanip>
#include <iostream>

//Facciamo in modo che il costruttore si rifaccia alla funzione che ha il compito di andare a controllare che i punti inseriti siano effettivamente
//Quelli di un rettangolo
Rett::Rett(const Point& a, const Point& b, const Point& c, const Point& d, char per, char riemp){
    setPoint(a, b, c, d);
    setPeriChar(per);
    setFillChar(riemp);

}

 Rett::~Rett(){
     std::cout<<"Ciao ciao rettangolo è stato un piacere vederti!\n";
 }

//Vado A impostare la funzione che ha il compito di definire se i punti che ho inserito possono essere un rettantolo!
void Rett::setPoint(Point a, Point b, Point c, Point d){

    //Ovviamenrte, la funzione prima di impostare 
    if((a.getPointY()==b.getPointY()) && (a.getPointX()==c.getPointX()) && (c.getPointY()==d.getPointY()) && (d.getPointX()==b.getPointX())){
        p1=a;
        p2=b;
        p3=c;
        p4=d;
    }

    else 
        throw std::invalid_argument("In base ai punti che hai inserito, i punti non rappresentano un rettangolo!");

    return;


}


//Andiamo a definire le funzioni che hanno il compito di impostare il carattere con cui si deve: 
//1) Mostrare il perimetro del rettanglo
//2) Riempire il contenuto del rettangolo!

//In questa andiamo ad impostare il carattere necessario per definire il perimetro del rettangolo!
void Rett::setPeriChar(char c){
    peri=c;
}

//In questa andiamo a impostare il carattere per riempire la figura
void Rett::setFillChar(char b){
    fill=b;
}


//Andiamo ad impostare le funzioni che hanno il compito di definire l'altezza e la larghezza del rettangolo!!!!
double Rett::larg() const{
    //Facciamo in modo che la funzione dia come valore di ritorno proprio il valore della larghezza del rettangolo
    
    //ATTENZIONE: Facciamo però in modo che la funzione restituisca non direttamrnte il valore della larghezza, ma il suo valore assoluto!
    //Questo perchè l'utente potrebbe inserire, ad esempio una cordinata x di p2 che sia minore di quella di p1!
    //Andando quindi a svolgere la sottrazione sotto avremo un valore negativo, cosa che noi non vogliamo ottente, motivo per cui scegliamo di 
    //considerare il valore assoluto di questa differenza! 
    //D'altronde la larghezza della figura non cambia!
    return abs(p2.getPointX()-p1.getPointX());
}

//La funzione che restituisce l'altezza è costruita allo stesso modo di come abbiamo fatto quella che definisce la larghezza!!!
//Abbiamo, anche in questo caso usato il valore assoluto in modo da considerare anche il caso in cui il valore p4.y sia minore di p1.y!!!
double Rett::altezza() const{
    return abs(p3.getPointY()-p1.getPointY());
}

//Impostiamo le funzioni che hanno il compito di  definire il perimetro dell rettangolo e dell'area!!!

//Per la funzione che restituisce il perimetro andiamo a sfruttare le due funioni che trovano l'altezza e la larghezza del rettangolo!
double Rett::perimetro() const{
    return (2*(altezza()+larg()));
}

//Anche la funzione dell'area sfrutta le funzioni di altezza e larghezza e ne fa il prodotto!
double Rett::area() const{
    return (altezza()*larg());
}


//Ultima funzione da definire è quella che va a stampare a video il disegno del rettangolo 
void  Rett::disegno() const{

    //Con i due cicli for vado a definire il paino dove devo rappresentare il rettangolo!
    //Con la y parto dal punto massimo, mentre con la x parto dal punto minimo!
    for(double y=25; y>=0; y--){
        for(double x=0.0; x<=25.0; x++){

            //Il primo if serve per stampare le due basi, quella superiore e quella inferiore
            if((y==p3.getPointY() || y==p1.getPointY()) && (x>=p3.getPointX() && x<=p4.getPointX()))
                std::cout<<peri;

            //Il secondo serve per stampare le due altezze
            else if (( x==p3.getPointX() || x==p4.getPointX()) && (y<p3.getPointY() && y>p1.getPointY()))
                std::cout<<peri;


            //Il terzo serve per stampare il contenuto del rettangolo
            else if( (y<p3.getPointY() && y>p1.getPointY()) && (x>p1.getPointX() && x<p2.getPointX()))
                std::cout<<fill;


            //Se nessuna delle precedenti condizioni non è verificata allora andiamo a stampare i punti del piano cartesiano!
            else 
                std::cout<<'.';



        }

        std::cout<<std::endl;

            

    }
}