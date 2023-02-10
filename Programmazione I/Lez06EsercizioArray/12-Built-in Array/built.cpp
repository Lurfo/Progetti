//Analizzo quelli che sono definiti come "BUILT-IN ARRAY", sono una struttura dati molto particolari ma che hanno una grande importante 
//essi, inoltre sono strettamente collegati con i puntatori
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

//Dichiariamo due funzioni che ci servono per gestire il nostro vettore, in questo caso usiamo sempre il passaggio per rifetimento!!!
//vedi sotto per altre informazioni
void riempimento(int [], const int);
void vedo(const int [], const int);

int main(){
    //In generale questo è il modo che utilizziamo per andare a definire il nostro built-in array, vediamo che:
    // 1-Tra le parentesi quadre abbiamo dichiarato il numero di elementi che l'array contiene
    // 2-Tra le parentesi graffe abbiamo poi inizializzato i valori contenuti!

    //Ci sono però anche molti modi per definire un array:
    // 1-Possiamo ad esempio definirlo array[]{1,2,3,...}-->In questo caso inizializziamo gli elementi e implicitamente viene definito il numero di 
    //   elementi che esso contiene!
   
    // 2-Possiamo anche definirlo array[12]-->Abbiamo solo dichiarato il numero di elementi, senza inizializzarli!!!

    int array[5]{1,2,3,4,5};
    //NOTA: Se dichiariamo un'array specificando il numero di elementi, se ne andiamo ad inserire un altro, si genera un errore di compilazione 


    //ATTENZIONE: Questo tipo di array è molto differente rispetto alla classe array che abbimo deginito in 01 ecc...
    //perchè questa "costruzione" non fa altro che RISERVARE UN CERTO NUMERO DI REGISTRI DI MEMORIA (in base al numero contenuto tra le []),
    //PER ANDARE POI A INSERIRE IN QUESTI SLOT I VALORI CHE ABBIAMO SCELTO!

    cout<<"Ti mostro i valori che sono contenuti nell'array: \n";


    //Come si vede, possiamo accedere ai vari valori contenuti nell'array usando sempre le parentesi [], così come si era fatto anche per 
    //la classe vettori e la classe array
    for(int i=0; i<5; i++){
        cout<<array[i]<<", ";
    }

    cout<<endl;


    //COME MAI I BUILT-IN sono collegati ai vettori? 
    //Vediamo che, per specificare l'indirizzo di memoria del primo valore contenuto nell'array basta semplicemente specificare il suo nome!
    //Nel caso di questo programma:
    //-Il nome "array" può essere paragonato ad un puntatore che contiene l'indirizzo di memoria al primo elemento dell'array(&array[0])

    cout<<"Cosa succede se ti mostro la variabile 'array' senza specificare la posizione?\n";
    cout<<"Te la mostro: "<<array<<endl;
    cout<<"Ti mostro l'indirizzo di memoria del primo elemento: "<<&array[0]<<endl;

    //Vediamo che i valori che ci vengono mostrati, sono uguali! Dunque il nome "array" VIENE IMPLICITAMENTE CONVERTITO NEL PUNTATORE AL PRIMO ELEMENTO!


    //COME PASSARE IL NOSTRO ARRAY AD UNA FUNZIONE!
    //Poichè, come visto, il nome del nostro array altro non è che un puntatore al primo elemento, possiamo passare quello alla funzione!
  
    //RICORDA: con questo tipo di array, non possiamo usare la funzione "size()" è d'obbligo, quindi, passare alla funzione anche la dimensione!

    cout<<"Sfruttando una funzione, andiamo a modificare i valori dell'array\n";

        //Come detto, alla funzione che ha il compito di rimepire il nostro array, non facciamo altro che inviare solo il nome del nostro array 
        //Implicitamente non stiamo facendo altro che mandargli l'indirizzo di memoria del nostro primo elemento dell'array!
        riempimento(array, 5);

    cout<<"Usando un'altra funzione, ti mostro il contenuto dell'array modificato!\n";

        //La chiamata a funzione è simile a quella precedente!
        vedo(array, 5);
    
    cout<<endl;


    //Dunque, se il valore che noi passiamo alla funzione altro non è che un indirizzo di memoria, possiamo anche usare un puntatore per scorrere
    //il nostro array!!!

    //Andiamo a dichiarare il nostro vettore che punta al primo valore del nostro array!
    cout<<"Ti mostro il contenuto del vettore usando il post-incremento e un puntatore!\n";
    int *ptr{array}; 

    cout<<"Ti mostro il contenuto del vettore, usando un puntatore!\n";

    cout<<"Valore del puntatore prima di mostrare i vettori: "<<ptr<<"\n";
    cout<<"valore del primo elemento dell'array: "<<array<<"\n";

    for(int i=0; i<5; i++){
        //In questo caso non stiamo facendo altro che dereferenziare il valore a cui il nostro puntatore puntatore!
        cout<<*ptr<<", ";

        //ATTENZIONE, IN QUESTO CASO STIAMO USANDO L'ARITMETICA DEI PUNTATORI!
        //Quando usiamo il post-incremento, sappiamo che l'elemento viene incrementato di 1
        //Non è un cosa che però avviene con l'aritmetica dei puntatori, quando andiamo a sommare un valore al puntatore, questo viene moltiplicato per
        //la grandezza dell'oggetto puntato dal puntatore
        ptr++;
        //Es: ptr è un puntatore ad int, in questo caso la dimensione dell'int è uguale a 4 byte!
        //quando andiamo ad incrementare il puntatore non facciamo semplicemente ptr=ptr+1
        //Ma diventa ptr=ptr+1*4!!!, in questo modo il puntatore si sposta al prossimo indirizzo di memoria che contiene il prossimo elemento!
    }

    cout<<endl;

    //Utilizzando questo metodo andiamo però a modificare il valore del puntatore, che non è più quello originario, in questo caso corrisponde
    //all'indirizzo dell'ultimo elemento dell'array!!!
    cout<<"Valore del puntatore dopo aver mostrato i vettori: "<<ptr<<"\n";
    cout<<"Valore dell'indirizzo dell'ultimo elemento del vettore: "<<&array[5]<<"\n";

    //POSSIAMO USARE UN ALTRO MODO PER NON ANDARE A MODIFICARE IL PUNTATORE!

    //Inizializziamo un altro puntatore al primo valore dell'array!

    cout<<"Vediamo cosa sucede con l'offset\n";
    int *ptr2{array};

    cout<<"Ti mostro l'idirizzo contenuto nel puntatore: "<<ptr2<<"\n";
    cout<<"L'indirizzo del primo elemento è: "<<array<<"\n";

    //Come vediamo per mostrare i valori, usiami un altro tipo di deferenziazione, facciamo riferimento all'offset!
    //ogni volta, andiamo a sommare al puntatore un valore per andare a determinare gli indirizzi di memoria successivi al primo!
    //Ovviamente, come accade per il post-incremento, prima di sommare il valore questo viene moltiplicato per la dimensione dell'elemento a cui punta!

    for(int i=0; i<5; i++){
      
        cout<<*(ptr2+i)<<", ";
    }

    cout<<endl;

    //Come si vede eseguendo il programma, usando l'offset, andiamo a mostrare tutti i valori che sono presenti nella struttura 
    //Senza però andare a modificare il valore contenuto nel puntatore, che resta uguale al valore a cui lo abbiamo inizializzato!
    //Un po' come accadeva con l'indirizzamento based indexed dell'assembly

    cout<<"L'indirizzo puntato dal puntatore dopo aver mostrato i valori è: "<<ptr2<<"\n";
    cout<<"Indirizzo del primo elemento dell'array: "<<array<<"\n";
    cout<<"L'indirizzo dell'ultimo elemento dell'array è: "<<&array[5]<<"\n";
    cout<<"vedi che l'indirizzo del puntatore, coincide ancora con il primo elemento!\n";

    //NOTA: l'offset può anche essere utilizzato sfruttando lo stesso nome dell'array!

    cout<<"Usiamo l'offset usando il nome dell'array!\n";

    for(int i=0; i<5; i++){
        cout<<*(array+i)<<", ";

    }

    cout<<endl;

    //Ovviamente questo accade perchè, come detto, il nome "array" è esso stesso un puntatore al primo  elemento della struttura

    //Ma dunque è ragionevole usare anche le [] usando un'array esterno!

    cout<<"Usiamo un puntatore esterno (ptr3) per andare a mostrare gli elementi del vettore usando le []!\n";
    int *ptr3{array};

    for(int i=0; i<5; i++){
        cout<<ptr3[i]<<", ";
    }
    
    cout<<endl;

    //Possiamo anche andare ad effetturare operazioni aritmetiche tra puntatori!!!
    //Utile, ad esempio, per conoscere a che distanza sono posti due elementi all'interno della memoria

    cout<<"Ti mostro la distanza tra il ptimo elemento del vettore e l'ultimo\n";

    //Vado ad usare due vettori che ho già usato in precedenza, ossia ptr(contiene l'ultimo elemento) e ptr3 che contiene il primo elemento

    long int pos{ptr-ptr3};

    cout<<"La distanza tra il primo e l'ultimo elemento è: "<<pos<<"\n";

}


//In questo modo andiamo a dichiarare, nell'argomento della funzione, che essa prende in ingresso un array!
//Questo tipo di costruzione è equivalente a: riempimento(int* ptr, dim), dove appunto ptr è un puntatore al primo elemento!
//Oltre all'array abbiamo sempre in ingresso la dimensione del nostro array!
void riempimento(int prova[], const int dim){

    cout<<"Dimmi i valori da inserire!"<<endl;

    //Come già ribadito sopra, possiamo andare ad accedere ad ogni valore del nostro vettore usando le []!
    for(int i=0; i<dim; i++){
        cin>>prova[i];
    }

    return;

}

void vedo(const int prova[], const int dim){

    for(int i=0; i<dim; i++){
        cout<<prova[i]<<", ";
    }

    cout<<endl;

}