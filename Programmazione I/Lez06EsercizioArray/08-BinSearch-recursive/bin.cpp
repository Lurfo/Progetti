//Vado ad implementare il sistema di ricerca binaria in modo ricorsivo!!!
#include <iostream>

#include <ctime>
#include <cstdlib>

#include <vector>

using std::cout;
using std::endl; 
using std::cin;
using std::vector;

void riemp(vector<int>&, int&);
void vedo(vector<int>&);
void ordino(vector<int>&);

//Questa è la funzione che va ad implementare la ricerca binaria in modalità ricorsiva, come vediamo abbimo bisogno di molti più indici!!!
bool trovo(vector<int>&, int, int, int, int&);

int main(){
    vector<int> vetto;
    int num;

    cout<<"riempio il vetto con un numero casuale di elementi casuali!!!\n";

    srand(static_cast<unsigned int>(time(0)));

    num=1+rand()%10;
    riemp(vetto, num);

    cout<<"Ho riempito il vettore!!!\n"; 

    cout<<"Ordino il vettore, in ordine crescente!\n";

    ordino(vetto);


    bool trovato;
    int val{0};
    int pos{0};
    char risp;
    int left{0};
    int right{num-1};

    do{
        cout<<"Dimmi l'elemento da trovare!\n";
        cin>>val; 

        trovato=trovo(vetto, left, right, val, pos);

        if(trovato){
            cout<<"Il valore che hai inserito si trova in pos:  "<<pos+1<<"! \n";
        }

        else{
            cout<<"Il valore che hai inserito non è presente nel vettore!!!\n";
            cout<<"Riprovare?[y/n]\n";
            cin>>risp;
        }

    } while(risp=='y' && !trovato);

    cout<<"Ora posso mostrarti il vettore!\n";
        vedo(vetto);



}


void riemp(vector<int>& vetto, int& dim){

    srand(static_cast<unsigned int>(time(0)));

    for(int i=0; i<dim; i++){
        vetto.push_back(1+rand()%100);
    }

    return;
}


void vedo(vector<int>& vetto){

    for(auto const& item:vetto){
        cout<<item<<", ";
    }

    cout<<endl;

    return;
}


void ordino(vector<int>& vetto){

    int num=vetto.size();

    for(int i=0; i<num; i++){
        int key=vetto[i];
        int j=i;

        while(j>0 && key<vetto[j-1]){
            vetto[j]=vetto[j-1];
            j--;
        }

        vetto[j]=key;
    }

    return; 


}

//La funzione è scelta sempre per essere una funzione booleana!!!
//come vediamo, tra gli argomenti della funzione, oltre al vettore e al valore che dobbiamo trovare, abbiamo anche dovuto inserire i 2 indici!!!
//Essendo infatti un implementazione ricorsiva, ad ogni chiamanta la funzione deve sapere in che posizione dell'array sono arrivati i nostri "segnalatori"

bool trovo(vector<int>& vetto, int left, int right, int val, int& pos){

    //Andiamo sempre a definire il punto medio del nostro vettore!!!
    int mid=(left+right)/2;


    //Abbiamo una prima condizione, la nostra funzione prosegue solo se, la posizione segnala dal segnaposto di destra è maggiore o uguale a quella
    //del segnaposto di sinistra!!!
    //Se infatti si ha che il segnaposto di sinistra supera quello di destra allora vuol dire che il nostro valore non è presente nel vettore!!!
    if(right>=left){
        
    //La condizione iniziale è simile a quella della funzione iterativa!
    if(vetto[mid]==val){
        pos=mid;
        return true;
    }

    //Anche la seconda condizione è simile alla versione iterativa
    else if(val>vetto[mid]){
        //Se la condizione è verificata andiamo a spostare il segnaposto di sinistra subito dopo la metà del nostro primo vettore!!!
        left=mid+1;

        //Qui abbiamo la grande differenza, andiamo a richiamare una seconda funzione che, non lavora più sul vettore completo, ma in questo caso, lavora
        //sulla seconda metà del nostro vettore!!!, e poi restituiamo il valore che questa  ottiene!!!
        return trovo(vetto, left, right, val, pos);
    }

    //Condizione simile a quella iterativa!
    else if(val<vetto[mid]){
        //Spostiamo il segnaposto di destra subito prima del valore centrale del nostro vettore!!!
        right=mid-1;

        //Richiamo una funzione che lavora sulla prima metà del nostro vettore se la condizione è verificata!
        //E restituiamo il valore che questa trova!!!
       return trovo(vetto, left, right, val, pos);
    }

    }


    //Se la prima condizione dell'if non viene rispettata, anche nelle altre funzioni iterative, abbiamo che uno dei due segnaposti ha superato l'altro
    //quindi il valore non è stato trovato!!!
    return false;

}

//NOTA BENE: In questo caso è stata implementata una forma ricorsiva della funzione di ricerca binaria, è possibile anche andare a definire una versione iterativa, usando come condizione del while 
//il fatto che il segnaposto di sinistra sia minore del segnaposto di destra!