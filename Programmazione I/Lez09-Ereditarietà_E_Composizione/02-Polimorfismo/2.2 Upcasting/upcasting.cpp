#include <iostream>

using std::cout;
using std::endl;
using std::cin; 

enum class play1{SI, DO, RE, MI};


//Vado a fare un esempio del fenomeno dell'upcasitng

//Definizione della classe base

class Instrument{
	
    public:

	void play(play1){cout<<"Instrument::Play\n";}

};

//Definizione della classe derivata, abbiamo usato il polimorfismo per definire la funzione play!
class Wind : public Instrument{

    public:

	void play(play1){cout<<"Wind::Play\n";}

};

//Definizione della funzione che va ad eseguire il suono!

void tune(Instrument& i){
    i.play(play1::SI);
    
    return;
}

int main(){


	Wind flauto; 

    //Anche se la funzione che abbiamo definito come tune prende in ingresso un riferimento alla classe base, noi possiamo tranquillamente passargli 
    //per riferimento anche una classe derivata
    //Questo NON GENERA ERRORE  in quanto la funzione accetta tutti gli elementi che sono derivati anche dalla classe base!
    //Abbiamo quello che viene definito come "UPCASTING" in quanto un elemento della classe derivata "diventa" un elemento 
    //della classe base!
    //Dunque il fenomeno dell'upcasting può purtroppo andare a limitare l'interfaccia della funzione derivata e andare a ridurla solo a quella della 
    //classe base!
    tune(flauto);

    //Abbiamo però un altro problema, riferito al polimorfismo della funzione e dovuto al binding con cui viene eseguito il legame tra 
    //la chiamata della funzione e il corpo della funzione chiamante (in questo caso il legame tra la riga 34 e quella 18)!

    //Se infatti noi andiamo ad eseguire questo programma vediamo che il valore restituito dalla funzione non è quello che ci aspettiamo, 
    //riceviamo in out il valore della funzione della classe base e non quello della classe derivata!
    //Questo è causato proprio dal binding con cui viene effettuato il legame tra la chiamata e la funzione chiamante e quindi dal binding
    //In questo caso, il problema di tale proframma avviene proprio a causa del binding!





}

