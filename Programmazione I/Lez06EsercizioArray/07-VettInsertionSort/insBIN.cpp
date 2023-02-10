//In questo programma andiamo ad unire due algoritmi molto importanti!!!
//Usiamo l'insertionSort per andare ad ordinare gli elementi che abbiamo all'interno del nostro vettore 
//Usiamo poi la ricerca binaria per andare a cercare se, all'interno del nostro vettore si trova un elemento che vogliamo ricercare!
//Ovviamente per usare la ricerca binaria abbiamo sempre prima bisogno che il nostro vettore sia ordinato!!!
#include <iostream>
#include <vector>

#include <ctime>
#include <cstdlib>

using std::cout;
using std::cin;
using std::vector;
using std::endl;

void riemp(vector<int>&, int&);
void mostro(vector<int>&);

//Dichiarazione della funzione che implemente l'InsertioSort
void ordino(vector<int>&, int&);

//Dichiarazione della funzione che implementa la RICERCA BINARIA
bool ricerca(vector<int>&, int&, int&);

int main(){
    vector<int> vett;
    int num;

    cout<<"Dimmi quanti elementi, randomici da 1 a 100, inserire all'interno del tuo vettore!\n";
        cin>>num;

    cout<<"Vado a riempire il tuo vettore!\n";
        riemp(vett, num);
        
    cout<<"Ti faccio vedere il vettore che hai inserito!\n"; 
        mostro(vett);
    

    //Andiamo ad usare l'insertion sort per andare ad ordinare il nostro vettore!!!
    cout<<"Visto che tutti gli elementi sono in disordine, voglio riordinarli!\n";
        ordino(vett, num);

    cout<<"Dopo averli ordinati il vettore è uguale a:\n";
        mostro(vett);

    //Solo dopo averlo ordinato possiamo andare a vedere se, al suo interno è presente il valore che vogliamo trovare!

    char risp;
    int val{0};

    //Variabile booleana che ci serve per trovare il valore che ricerchiamo
    bool trovato;
    int pos{0};


    //Per trovare l'elemento che noi cerchimo, usiamo un do-while
    do{
        cout<<"Dimmi l'elemento da ricercare\n";
            cin>>val;
        
        cout<<"Verifico se esiste il valore inserito\n";
            //La variabile la andiamo a inizializzare con il valore che la funzione restituisce, come vediamo successivamente
            //Alla funzione diamo anche, per riferimento, il valore pos che indica la posizione in cui si trova il nostro elemento all'interno del
            //nostro vettore!!!
             trovato=ricerca(vett, val, pos);

        if(trovato){
            cout<<"Ho trovto il tuo valore è in posizione: "<<pos+1<<"! \n";
        }

        else{
            cout<<"L'elemento inserito non è stato trovato, riprovare con un altro elemento?[y/n]\n";
                cin>>risp;
        }

    }while(risp=='y' && !trovato);
    //Andiamo ad usare come condizione del do while, sia la risposta che diamo sia se il valore della variabile booleana è falso -quindi l'elemento non
    //è stato trovato!!!

}

//Funzione che ha il compito di rimepire in modo randomico il nostro vettore
void riemp(vector<int>& vetto, int& num){
    srand(static_cast<unsigned int>(time(0)));

    for(int i=0; i<num; i++){
        vetto.push_back(1+rand()%100);
    }

    return;
}


//Funzione il cui compito è quello di mostrare gli elementi all'interno del vettore
void mostro(vector<int>& vett){

    for(auto const& item: vett){
        cout<<item<<", ";
    }

    cout<<endl;

    return;
}



//In questa funzione andiamo usare l'algoritmo INSERTIONSORT per andare ad ordinare il nostro vettore
//Ovviamente dobbiamo ordinare il nostro vettore perchè altrimenti non possiamo più usare il nostro algoritmo di ricerca
void ordino(vector<int>& vetto, int& num){

    //Usiamo il for per andare a scorrere tutti gli elementi che sono presenti nel nostro vettore
    for(int i=0; i<num; i++){
        
        //Andiamo a dichiarare una variabile che ha il compito "salvare" l'elemento del vettore che stiamo considerando
        int key=vetto[i];

        //Andiamo poi a dichiarare un valore che ha il compito di considerare la posizione dell'elemento del vettore
        int j=i;


        //Andiamo quindi a considerare un ciclo di while che ha il compito di scorrere  gli elementi del vettore che vengono prima
        //dell'elemento in posizione i--> usiamo però la variabile j per spostarci negli elementi del vettore
        //ATTENZIONE: abbiamo anche una seconda considizione per poter far funzionare questo while--> Il ciclo contiua a girare 
        //fino a che il valore che ci siamo salvato in posizione i è minore degli elementi che abbiamo prima!!!
        while(j>0 && key<vetto[j-1]){

            //Possiamo quindi spostare l'emento che abbiamo in posizione j, nelle posizioni precedenti, andando poi decrementare il valore di j
            //salvando ogni volta, nella posizione successiva il valore di j precedente, fino a che 
            //1) O il valore di j è diverso da 0
            //2) O il valore di Key è minore del valore presente nel vettore nella posizione j-1
            //Il ciclo prosegue fino a che la condizione del while è rispettata!!!
            vetto[j]=vetto[j-1];
            j--;
        }

        //Quindi andiamo poi a inserire nel nostro vettore, in posizione j, l'elemento che inizialmente abbiamo salvato !!!
        vetto[j]=key;

    }


}


//Questa è la funzione che ci serve per trovare il valore all'interno del nostro vettore, usando come algoritmo di ricerca
//la ricerca binaria!!!
//Si è scelto di usare come tipo della funzione il bool in modo da usare il valore restituito per far continuare o meno il ciclo while che
//è contenuto nel main, come si è visto, facendo restituire un valore false o un valore true -solo se il numero che ci occore è stato trovato!!!


//In tale funzione andiamo ad usare l'algoritmo di RICERCA BINARIA!!!-->Binaria perchè sfrutta due "segna-posti" che ci aiutano a scorrere l'array
bool ricerca(vector<int>& vetto, int& val, int& pos){

    //Si dichiara le dimenzione del vettore usando l'apposita funzione di libreria
    int dim=vetto.size();

    //Andiamo a dichiara i due segnaposti che ci occorrono:
    /* 1)Left è quello che segna il primo valore contenuto nel vettore --> inizializzato alla posizione 0
       2)Right è quelllo che segna l'ultimo valore contenuto nel vettore --> inizializzato all'ultima posizionr del vettore, uguale proprio a dim-1
     */
    int left=0;
    int right=dim-1;


    //Ciclo for che fa scorrere il vettore ordinato
    for(int i=0; i<dim; i++){

        //Dichiariamo una varabile che, segna il valore centrale del vettore, DURANTE IL PRIMO CILO!!!
        int mid{(left+right)/2};
        //DURANTE LA SECONDA RIPETIZIONE, Si crea un nuova variabile mid, differente dalla precedente, questa indica
        //o la metà della prima parte o la metà della seconda parte, a seconda di quali condizioni sono state rispettate durante il primo ciclo!!!
        
        //Tale procedimento si ripete fino a che o alla posizione "mid" corrisponde il valore che noi vogliamo trovare oppure non si ha che
        //uno dei due segnaposti superi l'altro, ad esempio abbiamo che il valor del segnaposto di sinistra supera quello di destra!!!-->
        //--> in questo caso ovviamente vuole dire che il ciclo for ha raggiunto la dimensione totale dell'array e si ferma



        //Questa è la condizione banale, se il valore al centro del vettore corrisponde al valore che ci occorre, allora lo abbiamo trovato!!!
        if(vetto[mid]==val){
            pos=mid;

            //Quanto il valore di "vetto[mid]" è uguale a quello del valore che noi cerchiamo, allora restituiamo come valore "true"!!!
            //il ciclo do-while nel main si interrompe!!!
            return true;
        }

        //Troviamo qui le altre condizioni 
       
        //Nella prima condizione vediamo se il valore che cerchiamo è maggiore dell'elemento in posizione "mid" del nostro vettore
        else if(vetto[mid]<val){
            //Se ciò è verificato, andiamo a spostare il segnaposto di sinistra subito dopo la posizione mid!!!
            //Andiamo a ripetere il ciclo for considerando SOLO LA SECONDA PARTE DEL VETTORE!!!
            left=mid+1;
        }

        //Ovviamente se le due condizini precedenti falliscono passiamo a questa-->
        //Questa condizione indica il caso in cui si ha che il valore che noi cerchiamo è minore del valore in posizione "mid"
        //vale a dire: vettore[mid]>val!!!
        else 

            //Se prima abbiamo spostato il segnaposto di destra subito dopo la posizione mid, in questo caso
            //Spostiamo il segnaposto di destra subito prima della posizione mid!!!
            //Andiamo a ripetere il ciclo for andando a considerare SOLO LA PRIMA PARTE DEL VETTORE!!!
            right=mid-1;

        //NOTA: Capiamo quindi come mai dobbiamo prima ordinare il nostro vettore, altirmenti non ha senso effettuare le operazioni del tipo
        //vetto[mid]>/<val!!!
    }


    //Se nessuna delle condizioni elencate sopra viene soddisfatta allora si ha che la funzione restituisce come valore "false"
    //Il ciclo do-while nel main continua su richiesta dell'utente!!!
    return false;
}





