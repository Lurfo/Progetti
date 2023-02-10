Attenzione, il file che è stato qui inserito, contiene un errore: 
    L'INGRESSO AL MONITOR DA PATTE DEI PROCESSI PRODUTTORI E CONSUMATORI ED ANCHE L'USO DELLE VARIABILI CONDITION

In particolare, si ha che, per come ho impostato io il monitor, il produttore e consumatore, si alternano ongni volta sulla medesima
locazione di memoria, dunque non vado a sfruttare la caratteristica principale del mio buffer che è composto come una 
coda circolare perchè è come se lavorassi su una sequenza di singoli piccoli buffer, per questa ragione, devo andare a "Migliorare"
questo aspetto. 

Devo fare in mdodo che il processo produttore e quello consumatore, non debbano susseguirsi nello scrivere
e nel leggere quella locazione di memoria
Inoltre, siccome ho implementato il programma con strategia produttore consumatore, devo fare in modo che tutta la produzione
e anche tutta la consumazione avvenga all'interno del monitor, senza uscire e rientrare ogni volta