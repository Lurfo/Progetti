//Vado ad inserire all'interno del file Dat molti elementi vuoti, vado cioè ad inizializzare il file!
#include "accounts.h"
#include <fstream>
#include <iostream>

using std::fstream;
using std::ios;

int main(){
    fstream filevuoto("prova.dat", ios::out | ios::binary);

    Account vuoto; 
    filevuoto.seekp(0);

    for(int i=0; i<100; i++){
        filevuoto.write(reinterpret_cast<char*>(&vuoto), sizeof(Account));
    }
}