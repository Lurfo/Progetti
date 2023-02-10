Implementazione di un problema Lettori/Scrittori, usando i pthread, regolando la competizione usando il monitor messo a disposizione dalla struttura. 
È importante sempre andare a definire che il problema specifica sempre che: 
	-Lettori e Scrittori si escludono tra loro dall'accesso alla risorsa
	
	-Gli scrittori, a loro volta, si escludono tra loro all'accesso della risolrsa
	
	-I lettori, possono accedere contemporaneamente alla risorsa
	
Di conseguenza, questo problema, implica sempre la necessità di introdurre due variabili condition, una per i lettori e una per gli scrittori
inoltre, si ha la necessità di inserire due variabili di controllo per gestire lettori e scrittori!
(Una indica il numero di scrittori presenti, l'altra indica il numero di lettori presenti) In base poi al valore che queste assumono allora posso andare ad effettuare una signal o una wait sulle variabili condition!
