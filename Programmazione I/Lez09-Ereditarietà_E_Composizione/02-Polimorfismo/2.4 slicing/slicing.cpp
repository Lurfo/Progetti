//Importante è il fenomeno dello slicing, che si contrappone al fenomeno dell'upcasting, questo consiste proprio nel tagliere
//Dall'oggetto derivato tutti gli elementi della classe base

//Tale fenomeno avviene quando abbiamo a che fare con un passaggio per valore!!!!

#include <iostream>

enum class nota{SI, DO, RE, MI, FA};

using std::cout;
using std::cin;
using std::endl;

class Instrument{

    public:

    virtual void play(nota){cout<<"Insturment::Play\n";}


};

class Wind : public Instrument{

    public: 
    
    void  play(nota){cout<<"Wind::Play\n";}


};

void tune(Instrument i){
    i.play(nota::SI);
}

int main(){
    
    Wind flauto;

    //Ho quindi passato per valore un oggetto wind, mentre nella funzione ho definito come argomento un oggetto di tipo instrument
    //In questo caso si ha il fenomeno dello slicing, la funzione play che vediamo nella funzione che abbiam specificato, sarà quella dell'oggetto 
    //Instrument e non può non essere così!
    tune(flauto);

    //Motivo per cui è sempre conveniente passare degli elementi per riferimento e mai per valore, in questo caso infatti si evitano due problemi: 
    //1) Non andiamo a ricopiare tutto l'oggetto in una nuova zone di memoria, provedimento che nel caso di oggetti molto complessi richiede un 
    //   grande uso di memoria
    //2) Evitiamo di generare errori di slicing quando usiamo degli oggetti derivati, potendo quindi sfruttare il polimorfismo degli oggetti!
}