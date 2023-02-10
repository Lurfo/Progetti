//Andiamo a impostare il driver che serve per definire utilizzare le proprietà della classe
#include <iostream>
#include "data.h"
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;

//Specifica dell'operatore <<
std::ostream& operator<<(std::ostream&, const Data&);
Data operator+(const Data&, int);
Data operator+(int, const Data&);

int main(){

    Data d1;
    Data d2;

    cout<<"Vediamo se la data d1 è minore della data d2\n";

    if(d1<d2){
        cout<<"é vero!\n";
    }

    else{
        cout<<"Non è verifitato!\n";
        cout<<"Infatti vediamo che d1= "<<d1.getData();
        cout<<"\nMentre d2 è uguale a: "<<d2.getData()<<"\n";
    }
    
    cout<<"-------------------------------------------"<<endl;
    
    cout<<"Spostiamo d1 un anno avanti, con il pre-incremento\n";

    int i=0;

    while(i<365){
       // cout<<d1.getData()<<endl;
        ++d1;
        i++;
    }

    cout<<"Ecco il valore di d1: "<<d1.getData()<<endl;
    cout<<"Ecco il valore di d2: "<<d2.getData()<<endl;

    cout<<"------------------------------------------"<<endl;

    cout<<"Sommo alla data d2 30 giorni, con l'operatore +=: \n";

    d2+=30;

    cout<<"La data d2 è ora uguale a: "<<d2.getData()<<"\n";

    ++d2;
    
    cout<<"Uso il pre-incremento per arrivare a febbraio: "<<d2.getData();


    cout<<"\n------------------------------------------"<<endl;

    cout<<"uso il nuovo operatore << per andare a mostrarti la data \n";

    //Aver effettuato l'overload dell'operatore << ci permette di poter esprimere direttamente la data senza andare a mostrare la data senza dover
    //Usare la funzione getData() che è stata definita nella classe!
    cout<<"La data d1 è uguale a: "<<d1<<"\n";
    cout<<"La data d2 è uguale a: "<<d2<<"\n";

    cout<<"--------------------------------------------"<<endl;

    cout<<"Uso il nuovo operatore per mostrare anche cosa accade con il pre e il post incremento!\n";
    cout<<"Aver ridefinito l'operatore << ci permette di usare anche il post incremento: \n";
    cout<<"Ti mostro d2, usando il post-incremento: "<<d1++<<"\nIl valore dopo aver incrementato è: "<<d1<<"\n";

    //Per verificare che tale operaizone non può essere fatta con l'operatore getData come è stato definito possiamo andare a vedere che
    //cout<<d1++.getData()<<"\n";
    //Se non commentato genera errore!

    cout<<"NOTA subito sopra il messaggio del distruttore, questo perchè, per il post incremento usiamo due date differenti!\n";

    cout<<"Voglio quindi usare il pre-incremento, cosa succede?\n";
    cout<<"Ti mostro d2 con il pre-incremento: "<<++d2<<"\nIl valore di d2 dopo l'incremento è uguale a: "<<d2<<"\n";

    cout<<"---------------------------------------------"<<endl;

    cout<<"Uso l'operazione di somma per definire una nuova data d3!\n";
    cout<<"Verifica che d3 = d1 + 10 giorni!\n";

    Data d3=d1+10;

    cout<<"La data d3 è uguale a: "<<d3<<"\n";
    cout<<"Mentre abbiamo che d1: "<<d1<<"\n";

    cout<<"---------------------------------------------"<<endl;

    Data d4{5,5,2019};

    cout<<"Ti mostro d4: "<<d4<<"\n";
    cout<<"Faccio il pre-decrmento: "<<--d4<<"\nDopo il pre-decremento d4= "<<d4<<"\n";
    d4++;
    cout<<"d4 è tornato ad essere: "<<d4<<"\n";
    cout<<"Faccio il post-decremento: "<<d4--<<"\nDopo il post-decremento è uguale a: "<<d4<<"\n";

    cout<<"-----------------------------------------------"<<endl;

    Data d5{12,6,1789};

    cout<<"Considero la data d5: "<<d5<<"\n";

    cout<<"Vado a sottrarle 10 giorni\n";

    d5-=30;

    cout<<"d5 ora è uguale a: "<<d5<<"\n";

}




//SPECIFICA DELLE FUNZIONI FRIEND

//Specifica dell'operatore <<
std::ostream& operator<<(std::ostream& output, const Data& d){

    output<<std::setfill('0')<<std::setw(2)<<d.day<<"/"<<std::setw(2)<<d.month<<"/"<<d.year;

    return output;

}


//Specifica della funzione somma
//Come si vede andiamo a definire una funzione che sfrutta, effettua una copia dei dati della data che gli viene inviata
//Infine usa un operatore che è già stato definito e cioè l'operatore +=!
//Così da andare a facilitare di molto il lavoro!
Data operator+(const Data& d, int g){

    Data nuovo=d;

    nuovo+=g;

    return nuovo;


}

//Andiamo quindi a definire la seconda operazione somma allo stesso modo di come abbiamo definito quella precedente!
//ATTENIONE questa andava comunque specificata in modo che la somma potesse essere invertita!
Data operator+(int g, const Data& d){

    Data nuovo; 

    nuovo+=g;

    return nuovo;

}