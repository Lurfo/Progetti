/*ALCUNE DELLE FUNZIONI CHE VENGONO USATE CON LE LISTE: 
1) Verifica di appartenenza alla lista; 
2) Accodamento di due liste


*/


%REGOLA CHE VERIFICA SE UN ELEMENTO APPARTIENE ALLA LISTA 

/*--PASSO BASE: Controllo che l'elemento sia uguale alla testa della lista*/
membro(A,[A|B]).
/*--PASSO RICOSIVO: Se non è uguale alla testa, allora controllo che sia un membro della coda*/
membro(X,[A|B]):- membro(X,B). 


%FUNZIONE PER IL CALCOLO DELLA LUNGHEZZA DELLA LISTA
/* --PASSO BASE: La lunghezza della lista vuota è nulla*/
lunghezza([], 0).

/*--PASSO RICORSIVO: La lunghezza della lista è uguale alla testa+la lunghezza della coda*/
lunghezza([A|B], N):-lunghezza(B, NUM1), plus(1,NUM1,N).
/*NOTA BENE: la funzione plus, esegue la somma 1+NUM1 e salva il risultato in N!!!*/



%FUNZIONE DI ACCODAMENTO DI UNA LISTA!!!!
/*--PASSO BASE: Aggiungo alla lista, una lista vuota, ottendo così la medesima lista
il passo base può essere formulato in due modi, aggiungendo una lista vuota sia a destra che a sinistra*/
appendi(L,[],L). 
appendi([],L,L).

/*--PASSO RICORSIVO: vado ad accodare la seconda lista, alla coda della prima, OTTENGO: Una nuova coda!*/
appendi([T|C1], L2, [T|C3]):- appendi(C1, L2, C3).