//Specifica delle varie funzioni!
template <typename T>
PriorityQueue<T>::PriorityQueue(): alb{}{}

template <typename T>
int PriorityQueue<T>::size() const{
    return alb.size();
}

template <typename T>
bool PriorityQueue<T>::empty() const{
    return alb.empty();
}

template <typename T>
void PriorityQueue<T>::Enqueue(const T& elm){
    alb.insertHeap(elm);
    }

template <typename T>
const T PriorityQueue<T>::Dequeue(){
    return alb.exctratMax();
}

template <typename T>
const T& PriorityQueue<T>::top(){
    return alb.top();
}

template <typename T>
void PriorityQueue<T>::vedo(){
    for(int i=1; i<=size(); i++){
        std::cout<<alb.vet[i]<<((i!=size()) ? ", ":"\n");
    }
}