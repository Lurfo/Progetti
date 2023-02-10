//Vado quindi a specificare tutti gli elementi che sono preseti all'interno della classe bst!
//Funzione che permette di vedere tutti gli elementi che sono in ordine!
template <typename T>
void BST<T>::inOrder(Node<T>* x){
    //in questo caso andiamo a vedere se il puntatore non è un puntatore nullo!
    if(x){
        //Ci postiamo direttamente tutto a sinistra in modo da prendere il puntatore più piccolo!
        inOrder(x->left);
        //Quando siamo giunti all'elemento più piccolo, posso andare a mostrare un elemento!
        std::cout<<x->elm<<"\n";
        //Finito l'ultimo elemento dobbiamo constrollare se questi ha qualche elemento maggiore, altrimenti proseguiamo a retroso fino alla radice!
        //per poi trovare gli elementi maggiori di tutti!
        inOrder(x->right);
    }
}


//Funzione di ricerda di un elmeto partendo da un nodo!
template <typename T> 
Node<T>* BST<T>::search(Node<T>* x, T& e){

    //Anche qui andiamo ad eseguire il ciclo fino a che il puntatore non è differente dal puntatore nullo!
    while(x){
        //Controllo che l'elemento non è direttamente puntato dall'elemento che ho!
        if(x->elm==e){
            break; 
        }
        //Verifico quindi se esso è maggiore o minore dell'elemento che ho puntato, mi sposto quindi o a sinistra o a destra!
        else if(x->elm<e){
            x=x->right;
        }

        else{
            x=x->left;
        }
    }

    //Restituisco il valore dell'elemento che ho puntato!
    return x;

}

template <typename T> 
Node<T>* BST<T>::search(T& k){
    return search(root, k);
}

//Specifica delle funzioni di ricerca del massimo e del minimo partendo da un nodo!
template <typename T>
Node<T>* BST<T>::minimum(Node<T>* punt){
    //Definisco un puntatore che parte dallo stesso punto del nodo che gli ho inviato!
    Node<T>* x=punt; 
    //Fino a quando il puntatore non è nullo!
    if(x){
        //Controllo fino a quando il puntatore di sinistra è differente dal puntatore nullo!
        while(x->left){
            //Mi sposto sempre a sinistra!
            x=x->left;
        }
    }

    return x;
}

//Allo stesso modo di come è fatto per il minimo posso andarlo ad implementare il massimo!
//La differenza è che mi devo spostare a destra e non a sinistra!
template <typename T> 
Node<T>* BST<T>::max(Node<T>* punt){
  
    Node<T>* x=punt;

    if(x){
        while(x->right){
            x=x->right;
        }
    }

    return x;

}

template <typename T> 
Node<T>* BST<T>::predecessor(Node<T>* x){
    //Mi definisco un puntatore segnaposto!
    Node<T>* segno=nullptr; 
    //Inizializzato a null, in questo modo posso gestirlo come preferisco!

    //Devo, come prima cosa vedere il valore più grande che si trova alla sinistra del nodo!
    if(x->left){
        //Vado quindi a trovare il massimo a sinistra!
        segno=max(x->left);
    }

    //A questo punto se l'elemento non ha un figlio sinistro, devo andare a trovare il genitore che ha quell'elemento nel
    //sottoalbero di destra!
    else{
        //Nel segnaposto mi tengo il valore del genitore della x
        segno=x->parent; 
        //Fino a quando il valore del puntatore non è nullo e il figlio sinistro è sempre il valore che ho inviato alla funzione, continuo a spostarmi!
        while(segno && segno->left==x){
            x=segno; 
            segno=x->parent;
        }
    }

    return segno;
}

template <typename T> 
Node<T>* BST<T>::successor(Node<T>* x){
    Node<T>* succ=nullptr; 
    //Se il nodo ha un figlio destro, devo andare a considerare il valore più piccolo del sottoalbero di destra!
    if(x->right){
        succ=minimum(x->right);
    }

    //Altrimenti, se non ho un figlio destro, devo considerare il primo elmento che contiene il nodo x nel suo sottoalbero di sinistra!
    else{
        //Considero il valore che genitore del nodo!
        succ=x->parent; 

        //Fino a che il valore del puntatore è differente dal nullo, continuo a spostarmi in alto nell'albero!
        while(succ && succ->right==x){
            x=succ; 
            succ=x->parent;
        }

    }

    return succ;
}

//Specifica della funzione di inserimento che va ad inserire un elemeneto all'interno dell'albero!
template <typename T> 
Node<T>* BST<T>::insert(T& e){
    //Come prima cosa devo andare a controllare che l'elemento che devo inserire non sia già inserito all'interno dell'albero
    if(search(e)){
       
        return nullptr; //Se l'elemento è presente facciamo in modo che restituisca un puntatore nullo!
    }

   

    //Altrimenti andiamo ad inserire l'elemento!
    //x ed y ci servono per determinare la posizione in cui andare ad inserire il nodo, mentre z è il nuovo nodo che devo inserire!
    Node<T>* x=root;
    Node<T>* y=nullptr;
    Node<T>* z=new Node<T>(e);



    //Con questo ciclo devo sempre andare a constrollare se l'elemento che ho inserito nel nodo è minore del nodo "radice", o maggiore
    //In base all'esito del confronto mi sposto o a sinistra o a destra!
    while(x){

        y=x; 
        if(z->elm < x->elm){
            x=x->left;
        }

        else{
            x=x->right;
        }
    }


    //Quando il ciclo esce dal while, abbiamo trovato un nodo, che ha uno dei due figli nullo, quindi quello sarà il genitore del nuovo nodo
    z->parent=y; 
  
    //A questo punto devo vedere se z è figlio destro o sinistro
    if(y==nullptr){
        
        root=z; //In questo caso abbiamo che poichè y è nullo, il ciclo di sopra non è stato eseguito, quindi l'elemento nuovo
        //è necessariamente il primo elemento dell'albero!
    }

    //Controllo se l'elemento contenuto in z è minore dell'elemento che è contenuto in y!
    //In questo caso z è figlio sinistro di y
    else if(z->elm<y->elm){
        y->left=z;
    }

    //altrimenti z è figlio destro!
    else{
        y->right=z;
    }

    std::cout<<"Restituisco z\n";
    return z;
}