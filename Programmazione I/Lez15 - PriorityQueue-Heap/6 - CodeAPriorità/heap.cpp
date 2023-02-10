//Specifica delle varie funzioni!
template <typename T> 
void Heap<T>::heapfy(int i){
    int l=left(i);
    int r=right(i);

    int posMax{0};

    if(l<=size() and vet[l]>vet[i]){
        posMax=l;
    }

    else{
        posMax=i;
    }

    if(r<=size() and vet[r]>vet[posMax]){
        posMax=r;
    }

    if(posMax!=i){
        int salvo=vet[i];
        vet[i]=vet[posMax];
        vet[posMax]=i;

        heapfy(posMax);
    }

}

template <typename T>
Heap<T>::Heap(): siz{0}{
    vet.push_back(0);
}


template <typename T>
int Heap<T>::size() const{
    return vet.size()-1;
}

template <typename T>
bool Heap<T>::empty() const{
    return siz==0;
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

template <typename T>
void Heap<T>::insertHeap(const T& elm){

    vet.push_back(0);
    siz++;
    int i=siz;
    
    while(i>1 and vet[parent(i)]<elm){
      
        vet[i]=vet[parent(i)];

        i=parent(i);
    }

    vet[i]=elm;

}

template <typename T>
const T Heap<T>::exctratMax(){
    T max;

    if(size()<1){
        throw std::underflow_error("Guarda che ormai è finito l'array");
    }

    else{

        max=vet[1];

        vet[1]=vet[size()];
        vet.pop_back(); 
        --siz;        
        heapfy(1);
    }

    return max;

}

template <typename T>
const T& Heap<T>::top() const{
    return vet[1];
}