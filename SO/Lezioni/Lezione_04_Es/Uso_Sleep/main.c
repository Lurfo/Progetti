#include <stdio.h>
#include<stdlib.h>

//Libreria da usare per la funzione sleep!
#include <unistd.h>

int main(){

    printf("Sono una persona molto bella\n"); 

    //Tale funzione sospende temporaneamente il programma fino al limite di tempo specificato
    sleep(90);

    printf("Sono una persona in riposo\n");
}