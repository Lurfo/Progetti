#include <iostream>
#include <array>

using std::cout;
using std::cin;
using std::endl;
using std::array;

int main(){
    //In generale usiamo questa definizione const size_t per definire una variabile che dichiara o la dimensione dell'array,
    //oppure viene usato per indicare una posizione all'interno dell'array
   const size_t dim{1};

    //Indichiamo l'array da usare (al posto delle parentesi quadre), in questo modo usando le specifiche array e il tutto contenuto nelle 
    //definizioni '< >' che indica il tipo di array e il numero di elementi che contiene 
    array<int, dim> prova{};

    //Abbiamo usato un tipo di riferimento differente per gli array, permesso proprio dalla funzione indicata nell'header <array>!!!
    //in questo caso il ciclo for, non ha bisogno di alcun counter, è in grado, automaticamente, di fermarsi quando l'array ha raggiunto il suo 
    //ultimo valore!!!
    for(int item: prova){
        cout<<item;
    }

    cout<<endl;

    

    for(int& items: prova){
        ++items;
    }

    for(size_t i={0}; i<prova.size(); i++){
        cout<<prova[i];
    }

    cout<<endl;

}