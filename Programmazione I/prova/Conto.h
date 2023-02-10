/* Modificare la classe Conto fornendo una funzione
membro chiamata prelievo, assicurandosi che
l'ammontare prelevato non ecceda il saldo del 
conto; in tal caso, il saldo dovrebbe essere
lasciato inalterato e la funzione membro dovrebbe
mostrare un messaggio indicando "...". Modificare
la classe TestConto per testare tale funzione creata.*/

// Questo file è: Conto.h

/*Di che si tratta? è la classe Conto che contiene
le variabili membro nome e saldo e le funzioni membro
per impostare e ottenere loro valori*/

//creiamo la classe

#include <string>
using namespace std;
class Conto {
	
	private:
		std::string nome;
		int saldo{0};
	public:
		
		// Costruttore ----------------------------------------------
		
		Conto(std::string nomeConto, int saldoConto)
			: nome{nomeConto} {
			if(saldo > 0)
				saldo = saldoConto;
		}
		
		
		//funzioni membro -------------------------------------------
		
		std::string daiNome() const {
			return nome;
		}
		int daiSaldo() const {
			return saldo;
		}
		int faiPrelievo(int prelievoConto) {
			if (prelievoConto <= saldo)
				saldo = saldo - prelievoConto;
		}
		int deposito(int depositoConto) {
			saldo = saldo + depositoConto;
		}
};
