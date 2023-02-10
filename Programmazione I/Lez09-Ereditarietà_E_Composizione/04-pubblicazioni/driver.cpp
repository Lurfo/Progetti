#include "book.h"
#include "convegno.h"
#include "riviste.h"
#include <vector>
#include <fstream>
#include <iostream>

#include "quicksort.h"//Poichè le funzioni che abbiamo definito le funzioni per il quickSort  sono dei template, devono essere necessariamente inserite
//all'interno di questo file, poichè devono necessariamente essere compilati tutti assieme!


using std::ofstream;
using std::cout;
using std::cin;
using std::vector;
int Book::numLibri{0};
int Riviste::numRiviste{0};
int Convegno::numConvegno{0};
 

int main(){
    
    //Definizione delle publicazioni necessarie alla bibliografia 
    Book libro1{"Giro del mond", 2020, "Mondadori", "3iubrtiu2jifn"};
    Book libro2{"Farfalle colorate", 2030, "Einaudi", "DIJ30G040-2395"};
    Riviste rivista1{"Andando a spasso", 2234, "Fobes", 34, 8989, 898989};
    Convegno primo{"Come gestire ", 101010, "Londra", 123};
    Convegno secondo{"L'insalata", 2016, "Roma", 34 };
    
    //Genero un vettore di puntatori a pubblicazioni, come definito dalla speficia, in cui vado ad inserire le publicaizoni!
    vector<Publication*> bib;

    //Inserisco gli elementi all'interno del vettore!
    bib.push_back(&libro1);
    bib.push_back(&libro2);
    bib.push_back(&rivista1);
    bib.push_back(&primo);
    bib.push_back(&secondo);

    cout<<"Mostro gi elementi che sono contenuti all'interno del vettore!\n\n";
    for(int i=0; i<bib.size(); i++){
        cout<<bib[i]->toString()<<"\n";
        cout<<"---------------------------\n";
    }

    //Devo andare ad ordinare gli elementi del vettore, per farlo vado ad usare, sul vettore delle publicazioni il quicksort!
    //Definisco il quicksorto in separata sede!

    cout<<"Ordino gli elementi della bibliografia!\n\n";
    quickSort(bib, 0, bib.size()-1);

    cout<<"Ti mostro gli elementi ordinati!\n";
    for(int i=0; i<bib.size(); i++){
        cout<<bib[i]->toString()<<"\n";
        cout<<"---------------------------\n";
    }

    cout<<"Salvo gli elementi all'interno di un file!\n";

    ofstream file{"Bibliografia.txt", std::ios::out};

    for(int i=0; i<bib.size(); i++){
        file<<bib[i]->toString()<<"\n";
        file<<"---------------------------\n";
    }


}
