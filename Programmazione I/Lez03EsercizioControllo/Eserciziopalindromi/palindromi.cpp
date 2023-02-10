#include <iostream>

using std::cout;
using std::cin;
using std::endl;


int main (){
    unsigned int i=0;
    int num[20];
    int numero;

    //Facico inserire il numero dall'utente
    do{
        cout<<"Inserisci un numero\n";
            cin>>numero;

        if(numero==0)
            cout<<"Hai inserito un numero uguale a zero, inseriscine uno differente\n";
    }while(numero==0);


    
    //Inserisco il numero che ho ricevuto in ingresso all'interno di un array
    while(numero%10!=0){
        //Considero il resto della divisione per 10 in modo da ottenre, ogni volta, prima le unità, poi decine e poi centinaia
        num[i++]=numero%10;
        //Dividento per 10, posso rendere più picolo il numero in modo da ottenre il valore che mi serve 
        //es: 123%10=3 -- 123/10=12.3 siccome è int il numero è uguale a 12--> 12%10=2 e così via fino alla fine delle cifre
        numero /=10;
    }
    
    //Dichiaro una nuova variabile che mi serve per considerare i valori nell'array
    int k{0}; 
    //Uso una variabile booleana per vedere se il numero è palindromo o meno
    //La imposto come valore iniziale a vero, in modo da usarla come condizione del while
    bool palindrom=true; 

    //Tramite il while controllo gli elementi dell'array
    //La condizione: Contiene sia il fatto che il valore k deve controllare la metà degli elementi
    //(devo confrontare ogni volta il primo e l'ultimo, la lunghezza si divide della metà)
    //sia che la variabile boleana è vera
    while(k<i/2 and palindrom){

        //Nell'if pongo appunto come condizione che il primo elemento dell'array che ho "creato" deve essere uguale all'ultimo
        //nota che nell'ultimo ho inserito i-k-1, pechè?
        //es: 1221, la dimensione di i, dal while precedente, non è 3 (parte da 0), ma 4, di conseguenza i-1 mi fa considerare il valore
        //dell'ultimo elemento dell'array, mentre -k mi fa scalare ai valori precedenti!
        if(num[k]!=num[i-k-1]){
            //se la condizione non è verificala, il numero non è palindromo, allora usciamo dal while
            palindrom=false;
        }
        
        k++;
    }

    if(palindrom)
        cout<<"il numero che hai inserito e\' palindromo"<<endl;
    
    else
        cout<<"Il numero che hai inserito non e\' palindromo"<<endl;







}
