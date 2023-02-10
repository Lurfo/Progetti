//Posso passare tramite riga di comanodo, dei parametri al mio processo!
#include <stdio.h>
#include <stdlib.h>

//argc indica il numero di stringhe puntate da argv, dunque argv è un puntatore che contiene le stringhe inviate tramite 
//riga di comando!
int main(int argc, char* argv[]){
    printf("Buongiorno, mi hai detto le segueti cose tramite linea di comando:\n"); 

    for(int i=0; i<argc; i++){
        printf("arg[%d]: %s\n", i, argv[i]);
    }

    //Lanciando il programma posso ben vedere che il primo argomento che viene passato, quello che ha valore 0, per intenderci
    //altro non è che il nome dell'eseguibile!

    //Tutti gli altri parametri sono invece quelli che indico dopo aver specificato l'eseguibile!

}