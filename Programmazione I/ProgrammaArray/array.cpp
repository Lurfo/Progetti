#include <iostream>
#include <iomanip>
#include <stdexcept>
#include "array.h"
using namespace std;
// implementiamo il costruttore di 
Array:: Array (int arraySize)
    : size{(arraySize >0 ? static_cast <size_t> (arraySize) :
        throw invalid_argument { "la dimensione deve essere maggiore di zero"})},
    ptr {new int [size]{}} {} //allochiamo dinamicamente un vettore di interi di dimensione size
// implementamo il costruttore copia 
Array:: Array (const Array& arrayToCopy)
    : size{arrayToCopy.size},ptr {new int [size]}{
        for(size_t i{0}; i<size;i++)
        {
            ptr[i]= arrayToCopy.ptr[i];
        }

    }
// distruttore
Array::~Array()
{
    delete [] ptr;
}
//implementiamo getsize
size_t Array:: getSize() const{
    return size;
}
//implementiamo l overloaded dell assegnazione 
const Array& Array:: operator= (const Array& right){
    if (&right != this){
        if (size != right.size)
        delete[] ptr;
        size=right.size;
        ptr= new int [size];
        //copiamo quello a destra in quello a sinistra 
        for(size_t i{0}; i<size;i++)
        {
            ptr[i]=right.ptr[i];
        }
   
    }
     return *this;
}
// implementiamo l'overloaded dell ==
bool Array::operator == (const Array& right)const {
    if (size!=right.getSize())
        return false;
    for (size_t i{0}; i<size;i++)
    {
        if (ptr[i]!=right.ptr[i])
        return false;
    }
    return true;
}
//overload  della sentinella per valori non costanti
int& Array:: operator[](int subscript)
{
    if (subscript >= size || subscript < 0)
        throw out_of_range {"indice al di fuori "};
    return ptr[subscript];

}
// overload  della sentinella per valori costanti
int Array:: operator[](int subscript) const
{
    if (subscript >= size || subscript < 0)
        throw out_of_range {"indice al di fuori "};
    return ptr[subscript];
}
//overload dell operatore >>
std:: istream& operator >> (std::istream& input, Array& a)
{
    for (size_t i{0}; i<a.size; i++)
    {
        input>> a.ptr[i];
    }
    return input;
}

//overload dell operatpre <<
ostream& operator << (ostream& output, const Array& a)
{
    for (size_t i{0};i< a.size;i++)
    {
        output << a.ptr[i] <<" " ;
    }
    output << std:: endl;
    return output;
}


