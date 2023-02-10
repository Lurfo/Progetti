#include <iostream>
using std::cout;
using std:: cin; 
using std::endl;

//Voglio dichiarare anche due variabili globali!
//Noto che queste due variabili globali hanno lo stesso nome di alcune variabili che sono nella funzione main!
//Mi riferisco a queste, usando l'operatore ::!
int a{1234};
int b{3959};




//Andiamo a dichiarare la funzione tramite un template! in modo da poter usare anche differenti tipologie di operandi senza doverci preoccupare 
//di genetare differenti funzioni per ogni tpo di operando! 
//Abbiamo in questo modo generato il template che ci serve per la nostra funzio e che serve per trovare il massimo o il minitmo tra due elementi!
template <typename prova>
//In questa funzione, come argomenti, abbiamo scelto il passaggio per riferimento, lo abbiamo fatto specificando il tipo di operando e 
//inserendogli vicino il valore &, in modo che il compilatore sa che stiamo considerando l'indirizzo di memoria di quello specifico oggetto!
//è preferibile usare questa tipologia di riferimento in modo da occupare meno spazio all'interno dello stack, cosa che potrebbe accadere con un 
//passaggio di valore
//NOTA:  siccome vogliamo che la nostra funzione non vada a modificare i dati che gli stiamo passando tramite riferimento aggiungiamo "const";
//ATTENZIONE: abbiamo scritto prova& poichè la funzione va a passare al main l'indirizzo di memoria del risultato che essa genera!
const prova& max(const prova& x, const prova& y){


    //Ho scelto di usare l'operatore "?", ha un uso molto simile ad if
  
    /* Abbiamo che, l'operazione che qui è descritta, equivale a:
       
        if(x>y)
            return x
        
        else 
            return y  
    */
    return (x>y) ? x:y;

}

int main(){

    cout<<"Ti mostro il massimo tra due valori che ti chiedo\n";
    
    int a;
    int b;

    cout<<"Inserisci due numeri\n";
    cin>>a;
    cin>>b;

    cout<<"Il massimo tra: "<<a<<" e "<<b<<" è: "<<max(a,b)<<endl;

    double c;
    double d;
    cout<<"Inserisci due numeri raizonali\n";
    cin>>c;
    cin>>d;

    cout<<"Il massimo tra: "<<c<<" e "<<d<<" è: "<<max(c,d)<<endl;


    char e;
    char f;

    cout<<"Inserisci due caratteri\n";
    cin>>e;
    cin>>f;

    cout<<"Il massimo tra: "<<e<<" e "<<f<<" è: "<<max(e,f)<<endl;


    //Trovo il massimo tra i due valori delle variabili globali!
    cout<<"Ti mostro il massimo e il minimo tra le due variabili globali!\n";
     cout<<"Il massimo tra: "<<::a<<" e "<<::b<<" è: "<<max(::a,::b)<<endl;
     //Avendo inserito l'operatore :: prima del nome della variabile, il compilatore capisce che mi sto riferendo alla variabile globale e dunqe
     //in fase di compilazione, inserisce questi valori al loro posto!

    



}