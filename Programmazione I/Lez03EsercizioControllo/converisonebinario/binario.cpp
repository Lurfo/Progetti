//Programma per la converisione dei numeri in binario
#include <iostream>

using std::cout;
using std::cin;
using std::endl; 

//Costruisco la funzione per trasformare il numero che ho inserito in binario
void conversionebin(int numero, int bin[]){
      int g=0;
    //Stiamo utilizzando la traslazione dell'intervallo per poter rappresentare i numeri negativi
    //l'intervallo tra 128 a 255 rappresenta i numeri tra -128(corrispondente al numero 128) a -1(corrispondente al numero 255)
    if(numero<0){
        numero+=256;
    }

    //Tramite la divisione posso trasformare il numero in binario
    while(g<8){
       bin[g++]=numero%2;
       numero/=2;
    }
    
    return;
}


int main(){
    int numero; 
    int bin[8];
    int i{0};

    //Vado ad inizializzare il valore dell'array con tutti zeri!
    while(i<8){
        bin[i]=0;
        i++;

    }

    //Vado a chiedere all'utente di inserire il numero da convertire in binario!
    //Inserisco anche la struttura di controllo che ha il compito di individuare se il numero che è stato inserito
    //Si trova nell'intervallo di rappresentazione che è uguale a 0/256
    do{
    cout<<"Inserisci un numero tra -128 e 127\n";
        cin>>numero;

        if(numero<-128 or numero>127){
            cout<<"Il numero che hai inserito non e\' valido, inseriscine un'altro\n";
        }
    }while(numero<-128 or numero>127);

    //Chiamo la funzione per la conversione de numero
    cout<<"Converto il numero in binario\n";
      conversionebin(numero, bin);

    //Mostro il numero in binario!
    cout<<"Il numeri che hai inserito, converito è uguale a: \n";
  
    int k{7};
    while(k>=0){
        cout<<bin[k];
        k--;
    }  
    cout<<endl;

}

