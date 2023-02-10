//Creiamo una versione del programma precedente con una funzione esterna
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

//Aggiungo la funzione che mi inserisce le cifre del numero che ho inserito all'interno dell'array
//Nota che mi restituisce in uscita il valore del riempimento dell'array
int inserimento(int numero, int array[]){
    int i=0; 

    while(numero!=0){
        array[i++]=numero%10;
        numero/=10;
    }

    return i;
}


//La funzione mi verifica se il numero che io ho inserito è palidromo o meno e mi restituisce in uscita la variabike booleana
bool verificapalindr(int lung, int array[]){
    int k=0;
    bool palindr=true;
   
    while(k<lung/2 and palindr){
       
        if(array[k]!=array[lung-1-k]){
            palindr=false;
        }

        k++;
    }

    return palindr;

}

int main(){
    int numero;
    int array[10];

    cout<<"Inserisci un numero\n";
    cin>>numero;

    while(cin.fail() or numero<=0){
        cin.clear();
        cin.ignore(100,'\n');
        
        cout<<"Il numero che hai inserito non è valido inseriscine uno differente\n";
        cin>>numero;
    }

   int lung{inserimento(numero, array)};

   cout<<"Ho completato l'inserimento dei dati\n";

   bool palindr=verificapalindr(lung, array);

   if(palindr){
       cout<<"Il numero che hai inserito è palindromo"<<endl;
   }

   else{
       cout<<"Il numero che hai inserito non è palindromo"<<endl;
   }
}