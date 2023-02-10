//Specifica delle funzioni che sono presenti nella classe list.h
#include "list.h"

prova::prova():proviamoconIntero{}, elementi{}{}

prova::~prova(){}

void prova::addElement(int element){

    elementi.push_back(element);

}