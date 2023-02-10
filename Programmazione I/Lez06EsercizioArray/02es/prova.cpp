#include <iostream>
#include <array>

using std::cout;
using std::cin;
using std::endl;
using std::array;

//Dichiariamo la nostra variabile come const in modo che la funzione non può modificarla!
void mostra ( const array<int, 12>&pisello);


//A differenza della funzione che abbiamo scritto precedentemente questa non ha il valore costante perchè dobbiamo avere la possibilità di 
//modificare i valori del nostro insieme!!!
void riemp(array<int, 12>& pisellino);

void operation(array<int, 12>& prova1, array<int, 12>& prova2);


void sommamento(array<int, 12>& prova1, array<int, 12>prova2);


int main(){
    
    const size_t dim{12};
    //Potendo le parentesi in questmo modo tutti gli ementi dell'array vengono inizializzati a 0!
    array <int, dim> prova1{};

    cout<<"Ti mostro il contenuto dell'array\n";
    
    //Facciamo un passaggio per riferimento alla nostra funzione
        mostra(prova1);

    cout<<"Andiamo ad inserire degli elementi all'interno del nostro array\n";

    //Anche nella funzione riemp usiamo un passaggio per riferimento!
        riemp(prova1);

        mostra(prova1);

    //Andiamo a dichiarare un nuovo array 

    array<int, 12>prova2{};

    cout<<"Riempiamo il secondo array\n";
        riemp(prova2);

    cout<<"Ti mostro il secondo\n";

        mostra(prova2);

    
    //Possiamo provare ad effettuare operazioni sugli arrya!!!
    cout<<"Vediamo di effettuare alcune operazioni sugli array!\n";

        operation(prova1, prova2);

    cout<<"Andiamo ad effettuare la somma tra i gli elementi dei due vettori!!\n";

        sommamento(prova1,prova2);


    cout<<"Ti mostro il primo dopo la somma che abbiamo fatto!\n";
    
        mostra(prova1);

        


}

//Dichiariamo la nostra variabile come const in modo che la funzione non può modificarla!
void mostra ( const array<int, 12>&pisello){

    //Usiamo il range based per mostrare gli ementi che sono contenuti all'interno di un array 
    for(int prova: pisello) {
        cout<<prova<<", ";
    }

    cout<<endl;

    //La parte sotto è stata aggiunta come esempio, se andiamo a togliere il commento, notiamo che il compilatore ci darà errore poichè stiamo 
    //tentando di modificare un valore che abbiamo dichiarato come costante!
/*
    for(size_t i=0; i<12; i++){
        pisello[i]++;
    }    

    for(int prova: pisello) {
            cout<<prova<<", ";
        }

    cout<<endl;*/

    return;
    
}

void riemp(array<int, 12>& pisellino){

    //Usiamo il range based per andare ad inserire gli elementi all'interno dell'array!
    //Il range based è molto utile perchè il c++ gestisce automaticamente il ciclo for, il tipo di incremento è fatto tutto 'automaticamente' 
    //inoltre, il c++ è anche in grado di comprendere in modo autonomo il numero massimo di elementi che ci sono all'interno dell'array

    for(int& item: pisellino){
        cout<<"Inserisci l'elemento"<<endl;
        cin>>item;
    }

      
      
        return;

}

void operation(array<int, 12>& prova1, array<int, 12>& prova2){

    //Anche sugli array abbiamo la possibilità di poter usare le operazioni quali quelle che vediamo qui sotto!!!
    
    if(prova1==prova2)
        cout<<"Sono uguali\n";
    

    else if(prova1<prova2)
        cout<<"il primo è minore del secondo!\n";
    

    else if(prova1>prova1)
        cout<<"il secondo è minore del primo\n";

    

    else 
        cout<<"Sono differenti!\n";

    return;
}

void sommamento(array<int, 12>& prova1, array<int, 12>prova2){
    
    char risp;
    size_t i{0};

    cout<<"Mediante l'operazione di somma andiamo a procedere con la sovrascrizione dei dati del primo array\n";
    cout<<"Procedere?[y/n]\n";
        cin>>risp;


    if(risp=='y'){
        for(int& item: prova1){
            item+=prova2[i++];
        }
    }

    else{
        return;
    }

    return;

}
