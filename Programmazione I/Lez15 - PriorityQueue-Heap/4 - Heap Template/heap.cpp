//VADO A SPECIFICARE TUTTE LE FUNZIONI DELLA CLASSE HEAP!

//In questo caso inizializzo la posizione dell'elemento a 0, poichè dopo con la funzione che aggiunge un elemento, vado ad incrementare il valore!
template <typename T>
Heap<T>::Heap(int siz): numElementi{siz-1}, posiz{0}, arr{new T[siz]}{
    //Inserisco degli 0 nell'array!
    for(int i=0; i<siz; i++){
        arr[i]=0;
    }
}

//Specifica del distruttore!
template <typename T>
Heap<T>::~Heap(){
    delete arr; 
}

//La funzione size, ritorna il numero di elementi contenuto all'interno dell'array! (tranne il numero 0!)
template <typename T>
int Heap<T>::sizeArr() const{
    return numElementi;
}

//Tale funzione serve invece per verificare l'effettivo numeri di elementi che ho inserito!
template <typename T>
int Heap<T>::size() const{
      
        return posiz;
    
}

template <typename T>
bool Heap<T>::empty() const{
    return posiz==1;
}

template <typename T>
int Heap<T>::left(int i){
    return 2*i; 
}

template <typename T>
int Heap<T>::right(int i){
    return 2*i+1;
}

template <typename T>
int Heap<T>::parent(int i){
    return i/2;
}

//SPECIFICA DELLA FUNZIONE HEAPFY!
template <typename T>
void Heap<T>::heapfy(int i){
    //Mi salvo la posizione del figlio sinistro e di quello destro!
    int l=left(i); 
    int r=right(i); 

    int posMax{0};

    //Vado a rintracciare il massimo valore tra il padre e i suoi 2 figli!
    if(l<=size() and arr[l]>arr[i]){
        posMax=l;
    }

    else{
        posMax=i;
    }

    if(r<=size() and arr[r]>arr[posMax]){
        posMax=r;
    }

    //Se ovviamente la posizione del massimo è uguale a quella del padre, è inutile proseguire poichè ho che la proprietà di heap viene rispettata
    if(posMax!=i){

       //Se la posizione che ho trovato è differente da quella del padre vuol dire che la proprietà di heap non viene rispettata, devo invertire il padre 
       //con uno dei suoi figli!
        int salvo=arr[i];

        arr[i]=arr[posMax];

        arr[posMax]=salvo;

        //Eseguo poi la funzione heapfy in modo che verifico se nella posizione in cui "il vecchio padre" si trova, viene rispettata la proprietà di heap!
        heapfy(posMax);
    }

    
}

//SPECIFICA DELLA FUNZIONE CHE VADO AD INSERIRE UN ELEMENTO ALL'INTERNO DELLA STRUTTURA DATI, IN MODO CHE ESSA, AD OGNI INSERIMENTO MANTIENE LA 
//STRUTTURA DI HEAP!
template <typename T>
void Heap<T>::insertHeap(const T& elm){
    
    if(posiz>sizeArr()){
        throw std::overflow_error("Guarda che ormai la lista è piena!");
    }
    
    else{
        //Vado ad incrementare la posizione del "segnaposto"
        posiz++; 

        //Salvo questo valore della posizione all'interno di una variabile "fantoccio" che mi serve per scorrere la serie di elementi!
        int i=posiz; 

        //Inizializzo un ciclo while, in cui verifico che la proprietà di heap viene rispettata!
        //comincio quindi l'inserimento partendo dalla poszione i dell'array (che è sempre l'ultima posizione!)
        //Devo quindi controllare se, mi trovo in una posizione che non sia il primo elemento e che il genitore del "nuovo" elemento!
        //sia maggiore lui!
        while (i>1 and arr[parent(i)]<elm){
            //Se ciò non dovesse accadere allora scambio di posizione il genitore con il nuovo elemento! (cioè porto il nuovo elemento più in risalto!)
            arr[i]=arr[parent(i)];
            //Sposto quindi il "segnaposto" alla posizione in cui ora si trova il nuovo elemento! Per verificare se si rispetta nuovamente la proprietà di heap!
            i=parent(i);
        }
        
        //Quando il ciclo termina, vado a inserire il valore alla posizione in cui sono arrivato!
        arr[i]=elm;

    }

}

//SPECIFICA DELLA FUNZIONE CHE VA A ELIMINARE L'ELEMENTO MASSIMO DALLA STRUTTURA, RESTITUENDO IL VALORE MASSIMO!!
template <typename T>
const T Heap<T>::heapMaxEstract(){
    
    //COME PRIMA COSA DEVO CONTROLLARE DI NON TROVARMI IN UNA SITUAZIONE DI UNDERFLOW, OSSIA CHE TUTTI GLI ELEMENTI SONO STATI RIMOSSI DALLA LISTA!
    
    T max;

    //Nota che, andando ad utilizzare un array, il numero di elementi è necessariamente finito, di conseguenza uso il segnaposto "fantoccio", in modo da poter
    //riutilizzare anche la funzione di inserimento!
    if(posiz<1){
        throw std::underflow_error("Guarda che è finito!");
    }

    else{
        //Essenodo che ci troviamo in un heap, il valore massimo si troverà sempre alla cima della struttura, quindi mi salv il primo elemento!
        max=arr[1];
        
        //A questo punto vado a spostare l'elemento alla fine dell'array, facendo come se esso venisse "cancellato" dall'array, mentre in realtà
        //si trova alla fine di esso!
        arr[1]=arr[posiz];

        //Per far si che esso non venga più visto vado a decrementare il segnaposto che mantiene l'ultimo elemento!
        //in modo che l'elemento che ho spostato non venga più visto!
        posiz--;
        
        //A questo punto devo però chiamare la funzione heapfy, poichè devo vedere se l'elemento che ho messo alla prima posizione rispetta
        //la proprietà di heap, in modo da mantenere ordinato l'heap!
        heapfy(1);
    }

    //NOTA BENE: Una funzione molto simile a questa molto utile quando voglio andare ad ordinare un insieme di elemenenti mediante un algoritmo
    //che sfrutta proprio alcune proprietà dell'heap, chiamato  HEAP SORT!
 
    return max;

}

template <typename T>
const T& Heap<T>::top() const{
    return arr[1];
}

template <typename T>
void Heap<T>::mostro(){
    for(int i=1; i<numElementi; i++){
        std::cout<<arr[i]<<((i!=numElementi-1) ? ", " : "\n");
    }
}
