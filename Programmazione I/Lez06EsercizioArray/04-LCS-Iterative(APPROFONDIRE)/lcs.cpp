#include <iostream>
#include <array>
#include <string>

using std::array;
using std::string;
using std::cout;
using std::cin;
using std::endl;

template <typename T>
const T& max(const T& x, const T& y){
    return (x>y) ? x:y;
}

int lcs(const string& s, const string& t, int m, int n,  array<array<int, 8>, 9>& tab ){
    
    //Anche se in questo caso abbiamo una tabella in cui andare ad inserire il valore delle coppie, il procedimeto resta molto simile alla versione ricorsiva!

    //Essendo una versione iterativa dell'algoritmo, uso due cicli innestati per andare a scorrere, con uno le righe, mentre con l'altro le colonne!
    for(int j=1; j<=m; j++){
        for(int i=1; i<=n; i++){
            
            //Controllo se i valori che ho definto sono uguali!
            if(s[j-1]==t[i-1]){
                //Se sono uguali, incremento di uno la posizione in cui mi trovo, considerando il valore che si trova subito alla mia sinistra, in quanto il valore che mi sono tenuto
                //per la lcs, me lo riporto in tutta la tabella!
                tab[j][i]=tab[j][i-1]+1;
            }

            else{
                //Nel caso in cui gli elementi non sono uguali, devo infatti andare a considerare una cosa, cioè, devo andare a riportare il valore massimo tra la casella che ho sopra
                //la posizione in cui mi trovo
                //E il valore che mi trovo subito alla mia sinistra!
                tab[j][i]=max(tab[j][i-1], tab[j-1][i]);
                //In questo modo mi riporto poi il valore della lcs che ho trovato fino a quel momento in tutta la tabella, fino al punto finale!
            }
           
        

        }
    }

    //Posso quindi restituire il valre che ho determinato in base alla lunghezza delle 2 stringhe all'interno della tabella, andando quindi a restituire il valore della lcs!
    return tab[8][7];

}

void inizialize( array<array<int, 8>, 9>& tab){
    
    for(int i=0; i<8; i++){

        for(int k=0; k<9; k++){

        tab[k][i]=0;
        }

    }
    
    
    
    return;

}

void mostra(array<array<int, 8>, 9>& tab){

    for(auto const& raws: tab){
        for(auto const& col:raws){
            cout<<col<<", ";
        }
        cout<<endl;
    }
}

int main(){
    string s{"ATACCAGA"};
    string t{"CTCCTAG"};

    //Come prima cosa definisco una tabella che ha come righe il numero di caratteri della prima sequenza + 1 e come colonne, il numero di caratteri della seconda sequenza + 1!
    array<array<int, 8>, 9> tab;

    int m=s.length();
    int n=t.length();

    cout<<"Inizializzo la prima riga e la prima colonna della matrice ad uno!"<<endl;
        //Come prima cosa bisogna andare ad inzializzare la prima riga e la prima colonna a zero!
        inizialize(tab);

    cout<<"Ti mostro il contenuto della tabella che abbiamo creato!\n"<<endl;

    mostra(tab);

    
    //Andiamo quindi a chiamare la funzione che ci permette di andare a calcolare la sequenza comune più lunga tra le due stringhe!
   cout<<lcs(s, t, m, n, tab)<<endl;

   //Rispetto quindi al caso in cui utilizziamo la versione ricorsiva della lcs, questa versione iterativa, che viene impiegata usando una tabella in cui andare ad inserire il valore 
   //della lcs non solo è molto semplice da implementare, ma risulta essere anche molto più vantaggiosa! Poichè permette di risolvere il valore della lcs usando una complessità 
   //computazionale dell'ordine di n^2, che risulta comunque essere molto elevata, ma rispetto alla versione ricorsiva, dove a causa del Subproblem Overlapping (Vale cioè a dire
   //che alcuni sottoproblemi, venivano analizzati più volte, proprio come accade nel caso di fibonacci! E non posso fare nulla per impedirlo!), la complessità computazionale
   //poteva anche arrivare ad un andamento esponenziale, si riesce di molto ad ammortizzare il costo

    //La complessità computazionale è dovuta al fatto che io sto utilizzando un doppio ciclo innestato che va a scorrere gli elementi delle righe e gli elementi delle colonne!
    //Dunque devo moltiplicare il costo dei singoli cicli tra loro e ottengo una complessità quadratica! (Vantaggiosa rispetto alla crescita esponenziale che avremo nel caso iterativo!)
  
   cout<<"La tabella finale è uguale a:\n";
    
     mostra(tab);

    cout<<endl;

    
}