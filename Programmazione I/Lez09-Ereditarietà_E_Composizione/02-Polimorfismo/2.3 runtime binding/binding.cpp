//Andiamo a riscrivere la funzione definita in 2.2, usando il runtime binding così da poter sfruttare il polimorfismo!
#include <iostream>

using std::cout;
using std::cin; 
using std::endl;

enum class nota{DO, RE, MI, FA};

class Instrument{
    public: 
    
        //Per specificare la funzione con il late binding dobbiamo andare a definirla come "virtual"!
        //NOTA: Ovviamente si ha che il late binding avviene solo per la funzione per cui è specifica, non per tutte le altre della classe base 
        //Inolte, tale late binding funziona solo se passiamo il valore di una classe derivata come riferimento della classe base,
        //effetuando cioè un upcastig!
      virtual  void play(nota){cout<<"Instrument::Play\n";}
};

class Wind: public Instrument{
    public: 

    //Ovviamente nella classe che derivata, possiamo andare tranquillamente ad eseguire l'overload della funzione della classe base, 
    //NON BISOGNA SPECIFICARE NUOVAMENTE LA FUNZIONE COME VIRTUAL
    //Infatti, una volta che è stata definita come virtual nella classe base "automaticamente" essa sarà virtual anche all'interno di tutte
    //le classi derivate!
    void play(nota){cout<<"Wind::Play\n";}


};

//Dobbiamo sempre usare il riferimento alla classe base per poter usare il late binding!
//(Ovviamete, passare il valore di Wind, come riferimento alla classe base non genererà mai un errore!)
void tune(Instrument& i){
    i.play(nota::DO);
}

int main(){
    Wind flauto; 

    tune(flauto);

    //Con il late binding il valore della restituito dalla funzione, eseguendo il programma è quello corretto!
}

