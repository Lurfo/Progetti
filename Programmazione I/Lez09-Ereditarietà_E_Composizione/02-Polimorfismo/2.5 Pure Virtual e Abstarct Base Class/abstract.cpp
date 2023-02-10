//Andiamo  a vedere un particlare tipo di fuzioni virtual, chiamate "PURE VIRTUAL FUNCTION"
#include <iostream>
 using std::cout;
 using std::cin;
 using std::endl;

 class Shape{
     public:

    //Tale è la definizione di un funzione PURE VIRTUAL
    //Essa è una funzioe che non può essere utile alla classe base e che DEVE NECESSARIAMENTE ESSERE SPECIFICATA DALLE CLASSI DERIVATE 
    //E' una funzione prettamente generica che deve poi essere specificata successivamente!
     virtual double area() const =0;
 };

 //La classe "shape", così come viene definita sopra è una "Pure virtual Class", nel senso che è una classe che contiene delle funioni Pure Virtual!
 //Particolarità delle classi pure virtual è che esse non possono essere istanziate!
 //(Instanziarle crea un errore di compilazione!)

 class Rectangle : public Shape{
     private: 
     
        double altezza;
        double lung;
        
    public: 

        Rectangle(double h=0.0, double l=0.0): altezza{h}, lung{l}{}

        //Questa è la specifica della funzione pure virtual che invece troviamo nella classe astratta definita sopra!
     virtual double area() const{return altezza*lung;}
 };

 int main(){

     //Se non vado ad eliminare l'elemento che ho dichiarato sotto allora il mio programma genera sempre un errore di compilazione poichè la classe 
     //s è una funzione pure virtual!
    // Shape s;
 
    Rectangle r{10.2, 5.77};

    cout<<"L'area del rettangolo è uguale a: "<<r.area()<<" m^2\n";


 }