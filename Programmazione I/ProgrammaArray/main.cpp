#include <iostream>
#include <stdexcept> /* per la sentinella errore */
#include "array.h"
using namespace std;
int main()
{
    Array integers1{7};
    Array integers2;

    // stampiamo la dimiensione di inytegrs1 e del suo contenuto 
    std:: cout << "La dimensione dell'array integres1 è: " << integers1.getSize()<< std:: endl
    << "l'array dopo l'inizializzazione è: "  << integers1 << std:: endl;
    std:: cout << "La dimensione dell'array integres2 è: " << integers2.getSize()<< std:: endl
    << "l'array dopo l'inizializzazione è: "  << integers2 << std:: endl;
    std:: cout << "Inserisci 17 interi: " << std:: endl;

    // overloaded  >> per gli array 
    std:: cin >> integers1 >> integers2 ;
    std:: cout << "dopo l'insetrimento gli array contengono: \n" 
    << "integers1: " << integers1 
    << "\n integres2: " << integers2 << std:: endl;

    // usiamo l'overloaded dell operatore !=
    std:: cout << "vediamo se integres1 != integers2 " << std:: endl;
    if (integers1 != integers2)
        std:: cout << "i due array sono diversi" << std:: endl;
    // invochiamo il costruttore copia 
    Array integers3 {integers1};
    std:: cout << "La dimensione dell'array integres3 è: " << integers3.getSize()<< std:: endl
    << "l'array dopo l'inizializzazione è: "  << integers3 << std:: endl;
    // facciamo la stessa cosa utilizzando l overload di =
    std:: cout << "assegnamo integres1 a integers2 " << std:: endl;
    integers1=integers2;
    std:: cout << " integers1 è " << integers1 <<" mentre integers2 resta " << integers2;
    // usiamo l overload di == 
    if (integers1 == integers2)
        std:: cout<< "integers1 è uguale a integers2 " << std:: endl;
    std:: cout << "integers1[5] è:  " << integers1 [5] << std:: endl;
    // riutilizziamo l'overload di [] per metterci un altro valore 
    integers1 [5]=1000;
    std:: cout << "integers1 ora è: " << integers1 << std:: endl;
    // implementiamo la sentinella di out of range 
    try{

        std::cout << "tentiamo di assegnare 1000 a integers1[15]" << std:: endl;
        integers1[15]=1000;
    }
    catch (out_of_range & ex){ 
        std:: cout << "è avvenuta una eccezione: " << ex.what() << std:: endl;
    }

}
