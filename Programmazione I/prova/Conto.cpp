#include <iostream>
#include <string>
#include "Conto.h"
using namespace std;
int main() {
	Conto primoConto{"Fabio Chiacchio", 0};
	cout << "Il saldo di" << primoConto.daiNome() << " � " << primoConto.daiSaldo() << endl;
	cout << "Quanto vuoi prelevare? ";
	cin >> prelievo;
	primoConto.faiPrelievo(prelievo);
	cout << "Il saldo di" << primoConto.daiNome() << " � " << secondoConto.daiSaldo() << endl;	
}
