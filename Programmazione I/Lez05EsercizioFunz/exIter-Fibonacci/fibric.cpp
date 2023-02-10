//Andiamo a creare la funzione iterativa di Fibonacci!!!
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main(){
    cout<<"Ti mostro la sequenza di fibonacci!!\n";

    //Abbiamo bisogno di queste 3 variabili che sono importanti
    //Abbiamo:
    //Temp indica un valore temporaneo, che ci serve per salvare il valore della variabile current
    //current indica il calore della sequenza uguale a F(n-1)
    //last indica il valore della sequenza che viene in posizione F(n-2)
    int tmp, current=0, last=0;

    //Andiamo a creare un ciclo for il cui compito è quello di mostrare i numeri della squenza di fibonacci
    for(int n=0; n<=11; n++){
        
        //Abbiamo il caso base, in questo caso, vediamo i primi due numeri della sequenza di fibonacci, che sono uguali ed entrambi uguali ad uno!
         if(n==0 or n==1){
            cout<<n<<", ";
            current=n;
        }

        //In questo caso abbiamo il valore iterativo!!!
        else{

            //Salviamo la variabile current(indica F(n-1)) all'interno di tmp
            tmp=current;

            //modifichiamo il valore di current andandolo a sommare al valore di last(indica F(n-2))
            //dopo questo passaggio dobbiamo aggiornare il valore di last, usando il valore che abbiamo lasciato in tmp
            //che, in questo caso, indica il valore di n-2
            current+=last;

            //Andiamo quindi ad aggiornare il valore di Fn-2 con tmp!
            last=tmp;

            //Alla fine ottiamo sempre che:
            /* Current =F(n-1);
               last=F(n-2)*/

            cout<<current<<", ";

        }

    }
    cout<<endl;
    


}