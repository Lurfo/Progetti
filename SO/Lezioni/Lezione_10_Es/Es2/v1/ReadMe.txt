In questo caso, creo un programma che deve calcolare un prodotto scalare tra due vettori, considerando che i vettori
possano essere condivisi tra più thread
In particolare ogni thread deve calcolare una porzione del prodotto scalare e deve poi andare ad aggiornare un apposita
variabile condivisa (contenuta nella medesima struttura) che contiene i risultato!