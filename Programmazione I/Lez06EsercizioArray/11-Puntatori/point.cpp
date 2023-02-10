//Si analizzano come sono fatti i puntatori!
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

//In generale i puntatori vegono utilizzati, come strumento per poter passare tramite riferimento un valore ad una funzione esterna, ma in modo
//particolare sono anche molto utili se vengono utilizzati per andare a gestire dei tipi di strutture dati dinamiche!
//Ad esempio, tramite un puntatore è possibile andare a visualizzare gli elementi che compongono un built-in array!!!

//Il puntatore è un elemento importante perchè-->CONTIENE L'INDIRIZZO DI MEMORIA DI UN ELEMENTO! Dunque può essere utile per due cose:

// 1-Farci conoscere l'indirizzo di memoria in cui andiamo ad allocare il valore
//   (motivo per cui è molto utile per andare a gestire elementi dinamici!-->Esso infatti ci permette di gestire, come meglio crediamo le allocazioni)

// 2-Possiamo usarlo anche per andare a conoscere quello che è il reale valore dell'elemento che stiamo puntando! 
//   (stiamo cioè usando un tipo di riferimento chiamato RIFERIMENTO INDIRETTO AL VALORE! Definita anche come "DEFERENZIAZIONE")

//Nota: il riferimento diretto è quando usiamo direttamente quella variabile per esprimere il suo valore!


//Dichiariamo il prototipo di una funzione che ha come argomento un puntatore!
void cubo(int*);

int main(){

    //In generale questo è il modo in cui viene dichiarato un puntatore, usando l'*, che in questo caso non sottintende l'operazione di moltiplicazione
    //ma sta ad indicare che anche quell'elemento che abbiamo dichiarato è un puntatore!
    
    //In questo caso diciamo che la variabile ptr è un puntatore ad un intero!!!
   
    //ATTENZIONE CI POSSONO ESSERE DIFFERENTI TIPI DI PUNTATORI! 
    // -Allo stesso modo possiamo andare a dichiarare differenti tipi di puntatori, ad esempio:
    // char*, indica un puntatore a char;
    // double*, indica un puntatore a double;
    //Ma ci possono essere molti altri tipi di puntatori ad altre tipologie di strutture dati!
    int *ptr{nullptr};

    //Prima di essere utsato, un puntatore deve essere inizilizzato, in modo che esso non punti ad un generico indirizzo!
    //Per farlo lo inizializziamo al valore "nullptr", in modo che esso abbia un valore pari a 0!
    //cioè non punta a nessun indirizzo di memoria!

    //ATTENZIONE: Possiamo inizializzare il nostro puntatore anche al valore 0, MA A NESSUN ALTRO INTERO, ALMENO PRIMA DI AVERLO CONVERTITO IN UN 
    //TIPO PUNTATORE, mentre 0 poissiamo assegnarlo direttamente
    //(Prova, sostituendo un generico numero intero, si genere un errore di compilazione, mentre mettendo il valore di 0 viene "accettato")

    //In genere usiamo comunque nullptr per inizializzarlo!
    //L'inizializzanzione è utile per evitare che esso punti ad altre zone di memoria che risultano inaccessibili, causando errori di compilazione!

    int num{0};

    cout<<"Dimmi il valore che vuoi per il tuo numero!\n";
        cin>>num;

    cout<<"Puntatore prima di essere inizializzato: "<<ptr;

    //Andiamo quindi ad inserire nel puntatore l'indirizzo di memoria della variabile che contiene il nostro numero!
    //Per farlo usiamo l'operatore UNARIO &, che se inserito alla sinistra di qualsiasi elemento ci permette di accedere all'indirizzo di memoria di
    //una qualsiasi variabile che andiamo a dichiarare!

    cout<<"\nTi mostro l'indirizzo dove risiede la variabile num: "<<&num;

    ptr=&num;
    //Dopo questa operazione il puntatore contiene l'indirizzo di memoria del valore num che abbiamo scelto!
    cout<<"\nL'indirizzo contenuto nel puntatore è: "<<ptr<<endl;

    //Questo è il classico tipo di rifetimento al valore che abbiamo scelto
    cout<<"\nRiferimento diretto al valore scelto: "<<num;

    //Questo è invece il tipo di rifetimento definito come DEFERENZIAZIONE, che abbiamo usando l'operatore "*"!
    //usando l'* facciamo in modo di accedere al valore che il nostro puntatore punta!
    cout<<"\nRiferimento indiretto al valore: "<<*ptr<<endl;

    //ATTNETIONE, ovviamente il puntatore risiede ad un indirizzo di memoria differenze rispetto al valore che noi abbiamo definito!
    cout<<"Dove risiede il puntatore? Qui: "<<&ptr<<"\n";

    //Tramite l'operatore di deferenziazione e il puntatore posso anche andare a modificare il valore a cui il puntatore punta!
    cout<<"Modifichiamo il valore usando la Deferenziazione: \n";
        cin>>*ptr;

    cout<<"Il valore della variabile iniziale ora è: "<<num<<"\n";
    //Usiamo sempre la deferenziazione per mostrare il valore puntato dal puntatore!
    cout<<"Mente il valore puntato dal puntatore è: "<<*ptr<<"\n";    
    //Questo è possibile proprio grazie alla grande funzionalità del puntatore!!!









    //USIAMO UN PUNTATORE PER SFRUTTARE IL PASSAGGIO PER RIFERIMENTO TRAMITE PUNTATORE!

    cout<<"Passiamo il valore alla funzione che esegue il cubo del nostro numero, tramite rifetimento per puntatore\n";

        //Per effettuare questo tipo di passaggio abbiamo che la funzione che abbiamo dichiarato sopra, ha come argomento un puntatore 
        //Dunque nella chiamata a funzione non facciamo altro che PASSARLE UN INDIRIZZO DI MEMORIA
        cubo(&num);

    //Ovviamente usando questo tipo di passaggio tramite riferimento, il valore della variabile contenuto in "num" viene modificato!
    cout<<"Ti mostro il valore della nuova variabile: "<<num<<"\n";
    cout<<"Ti mostro il valore puntato dal vettore: "<<*ptr;

    cout<<endl;
    

}

//Questa è la funzione che realizza il cubo del nostro numero!
//come vediamo, ha come argomento il nostro puntatore che contiene l'indirizzo di memoria che gli abbiamo passato!!!
//Perchè è utile questo tipo di rifetiento? 
//Perchè la nostra funzione, non va a salvare il valore del numero che gli abbiamo passato, ma va a salvare solamente il puntatore!!!
//possiamo dunque risparmiare spazio in memoria
void cubo(int *punto){

    //Per effetturare il cubo del nostro numero, usiamo sempre la deferenziazione!
    //Il modo più semplice in cui la funzione può accedere al valore puntato dal suo puntatore!
    *punto= *punto * *punto * *punto;

    //In questo caso la nostra funzione non fa altro che: 
    // 1-Deferenziare tutti i valori
    // 2-Moltiplicarli tra di loro!

}