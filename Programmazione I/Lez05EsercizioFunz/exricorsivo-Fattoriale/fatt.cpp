#include <iostream>

using std::cout;
using std::cin;
using std::endl;

//Andiamo quindi a definire una funzione ricorsiva per calcolare il fattoriale di un numero qualsiasi!
//Usare una funzione ricorsiva può essere molto vantaggioso per svolgere alcuni compiti importanti!
//l'uso di funzioni ricorsive è importante anche in molti tipoogie di algoritmi, come quelli necessari alla ricerca di elementi all'interno di array!

//Dichiariamo quindi il prototipo della funzione!
unsigned long factorial(unsigned long);

int main(){
    unsigned long num;

    cout<<"Dimmi un numero che ti calcolo il fattoriale!\n";
    cin>>num;

    cout<<"Il valore del fattoriale del numero è: "<<factorial(num)<<endl;

}


//Andiamo a dichiarare la nostra funzione per calcolare il fattoriale
//ATTENZIONE: Importante in questa situaizone è sempre definire 2 casi fondamentali:

//1)IL CASO BASE: Importante per definire il primo caso della nostra definizione ricorsiva
//(nel caso del fattoriale, il caso base è quando il numero che inseriamo è uguale a 1 o 0, in entrambi i casi infatti il valore è sempre uguale ad 1)

//2)IL CASO RICORSIVO: Serve per dividre il nostro problema in problemi più piccoli in modo da renderli molto più facili da risolvere! 
//(nel caso del fattoriale, il caso ricorsivo è n*(n-1))

unsigned long factorial(unsigned long num){
    //Qui vediamo, il caso base, in entrambe le situazioni, si ha che la funzione restituisce il valore 1!
    if(num==1 or num<=0){
        return 1;
    }

    //Qui abbiamo il caso ricorsivo e, come vediamo, il problema viene diviso in problemi sempre più semplici!
    //Ogni volta, nel caso del fattoriale, andiamo a chiamare la stessa funzione su un valore sempre più piccolo, fino ad arrivare al caso base!
   
    //IL CASO BASE È MOLTO IMPORTANTE!!! Esso infatti ci permette di evitare l'INFINITE RECURSION!!!-->Se non consideriamo un caso base, si ha che
    //il caso ricorsivo continua fino all'infinito!!! Grazie al caso base, invece si ha che, arrivato ad un certo valore, la funzione ricorsiva
    //si blocca perchè è giunto al caso base!!!
    /*Es sul caso fattoriale: 
        5!--->5*4!--->4*3!--->3*2!--->2*1!--->1!!! Siamo arrivati al caso base!!!
        Vediamo i valori restituiti:
        1(Restituisce 1)--->
        --->2*1!(2!=2*1==Restituisce 2)--->
        --->3*2!(3!=3*2==Restituisce 6)--->
        --->4*3!(4!=4*6==Restituisce 24)--->
        --->5*4!(5!=5*24==Restituisce 120)!!!   
        */

    else{

        //Quello che qui stiamo facendo è chiamato DIRECT RECURSION perchè una funzione chiama ricorsivamente se stessa ogni volta!!!
        //ATTENZIONE: Esiste anche la INIDIRECT RECURSION, abbiamo una ricorsività differente: Una funzione non richiama se stessa in modo ricorsivo,
        //ma continua a chiamare sempre altre funzioni per poi tornare alla funzione originale
        return num*factorial(num-1);
    }
}

