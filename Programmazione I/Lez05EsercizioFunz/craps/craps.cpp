#include <iostream>
//Inseriamo due libreria che sono utili per l'uso dei numeri casuali!
#include <ctime>//Utile per usare la fuzione time che ci serve per la creazione del seed dei numeri casuali
#include <cstdlib> //Ci serve per le funzioni rand(generare i numeri casuali) e srand(per specificare il seme con cui generiamo tali numeri)

using std::cout;
using std::cin;
using std::endl;

//Vado a dichiarare la funzione che dovrò usare successivamente usando il suo prototipo, la funzione verrà poi dichiarata dopo aver scritto il main
unsigned int rollDice();

int main(){
    //Usiamo la classe status per considerare in che punto della partita ci troviamo
    //In particolare ogni costante contenuta in questa classe è un intero! In generale il primo degli elementi è contrassegnato con uno zero 
    //Mentre tutti gli altri sono incrementati di uno
    //Es:  CONTINUA=0
    //     VITT=1
    //     PERDE=2
    //Se specifichiamo differentemente il primo degli elementi può anche essere contrassegnato come un numero differente, in queste modo, 
    //ogni elemento successivo viene incrementato in base al primo valore dell'elemento di enum
    //Posso anche scefliere di che tipo devono essere le costanti presenti nella classe scrivedo, ad esempio:
    //enum class Status: int{costanti};
    enum class Status{CONTINUA, VITT, PERDE}; 


    //Usiamo in questo caso la funzione srand contenuta in cstdlib e la funzione time che è contenuta nella libreria ctime che ci permette di 
    //usare l'orario corrente all'interno del nostro programma
    //In particolare con la funzione srand stiamo assegnando un seme per generare i nostri numeri casuali, usando la funzione tempo ci assicuriamo che 
    //ogni volta che eseguiamo il nostro programma abbiamo ogni volta un seme differente, in modo che "non rischiamo" di avere dei numeri sempre uguali tra loro
    //Se infatti io dovessi porre srand(1) allora abbiamo che il seme dei nostri numeri casuali è sempre uno, quindi eseguendo ogni volta il programma
    //Avremo una ripetizione degli stessi numeri casuali!
    srand(static_cast<unsigned int>(time(0)));

    unsigned int punto{0};
    Status gameSet; //Stiamo dichiarando una variabile di tipo Status, che può assumere solo uno dei 3 valori che abbiamo definito sopra!
    unsigned int sumOfDice{rollDice()};//Dichiariamo una variabile che ha come valore quello che restituisce la funzione rollDice che abbiamo 
                                       //Abbozzato sopra!

    //Usiamo uno switch per definire i diversi casi del gioco che ci servono, in base alla romma dei nostri dadi!
    switch(sumOfDice){
        //Segno, come inizio i casi particolari del gioco per cui posso perdere o vincere!
        case 7:
        case 11:
            gameSet=Status::VITT;
            break;
        
        case 2: 
        case 3:
        case 12:
            gameSet=Status::PERDE;
            break;

        //Questo vuol dire che per tutti gli altri casi lo switch esegue sempre queste istruzioni!
        default: 
            punto=sumOfDice;
            gameSet=Status::CONTINUA;
            break;     
    }


    //A questo punto, il gioco prevede che 
    while (Status::CONTINUA==gameSet){
       unsigned int newpoint=rollDice();

        if(newpoint==punto){
            gameSet=Status::VITT;
        }

        else if(newpoint==7)
            gameSet=Status::PERDE;

    }

    if(Status::VITT==gameSet){
        cout<<"Complimenti, hai vinto il guoco dei dadi!"<<endl;
    }

    else    
        cout<<"Hai perduto!"<<endl;

}

unsigned int rollDice(){
    cout<<"Lancio i dadi!"<<endl; 
    //In questo modo andiamo a dichiarare delle nuove variabili, in modo che prendano in ingresso un valore casuale da 1 a 6
    //Simulando quindi il lancio dei dadi
    //ATTENZIONE: è scritto 1+rand()%6 poichè la funzione rand()%6 prende un numero casuale da 1 a 5!!!
     int dado1{1+rand()%6};
     int dado2{1+rand()%6};
     int sum{dado1+dado2};

    cout<<"Il giocatore ha ottenuto: "<<dado1<<", "<<dado2<<". Per un totale di: "<<sum<<endl;

    return sum;

}


