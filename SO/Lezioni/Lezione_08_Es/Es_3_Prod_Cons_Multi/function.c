#include <time.h>
#include <stdlib.h>

#include "function.h"

float generoFloat(int sx, int dx){
    //Ottengo un valore float, che si trova all'interno di un intervallo
    //Nota, siccome ho  che sx e dx sono degli interi, ho la necessità di fare un casting
    float x = (float)(rand()+sx)/(float)(RAND_MAX/dx);

    return x;
}