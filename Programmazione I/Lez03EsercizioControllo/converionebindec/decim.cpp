//Converto un numero da binario a decimale
#include <iostream>

using std::cout;
using std::cin;
using std::endl; 


//Tale funzione ha lo scopo di chiedere all'utente l'inserimento delle cifre del numero in binario partendo da quella meno significativa!
void inserimento(int binarr[]){
    
    int i{0};
   
     while(i<8){
        cin>>binarr[i];
        while(binarr[i]!=1 and binarr[i]!=0){
            cout<<"Il numero che hai inserito non è valido devi inserire o 1 o 0\n";
            cin>>binarr[i];
        }

        i++;
    }

    return;
}


//Funzione che ha lo scopo di convertire il numero da binario a decimale
int conversione(int binarr[]){
    
    int decim{0};
    int i{0};

//Con questo while mi sposto nelle cifre dell'array
//Possiamo partire da 0 poichè binarr[0] è la cifra meno significativa
    while(i<8){
        int potenza{1};
      
        //Con questo ciclo for mi calcolo il valore della potenza di 2 corrispondente a quella cifra del numero binario
        for(int k=0; k!=i; k++){
            if(i>0){
                potenza *=2;
            }

        }

        //Per trovare il valore decimale devo sommare il valore della cifra del numero binarr[i]
        //Con la potenza del 2 che ho trovato precedentemente
         decim+=binarr[i]*potenza;
        
        i++;
    }

    return decim;

}

int main(){
    int binarr[8];

    cout<<"Dimmi un numero in binario cifra per cifra partendo da quella meno significativa\n";

    inserimento(binarr);
    
    cout<<"Il numero che hai inserito è uguale a: \n";

    for(int i=7; i>=0; i--){
        cout<<binarr[i];
    }

    cout<<endl;

    //Chiamo la funzione che la scopo di convertire il numero in binario
    int decimal{conversione(binarr)};

    //Poichè vogliamo rappresentare anche reativi, adoperiamo la traslazione dell'intervallo!
    //Dunque ai numeri che sono maggiori di 127 sottraiamo il valore 256 così otteniamo i valori negativi!
    if(decimal>127){
        decimal-=256;
    }

    cout<<"Il numero che hai inserito in binario, viene convertito in: "<<decimal<<endl;

}