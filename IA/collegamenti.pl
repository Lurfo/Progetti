/*Vado ad impostare delle regole e dei fatti che vanno ad impostare un collegamento tra le varie città*/

%Devo sempre impostare i fatti che mi occorronoù
coll(na,ro).
coll(na,rc).
coll(ro,ba).
coll(ba,rc).

%Imposto una regola di simmetria per verificare i collegamenti bidirezionali

%Nota, viene commentato per non generare errori
%coll(X,Y):-coll(Y,X).

%ATTENZIONE: questa regola di simmetria, può causar un problema di loop, per via della conoscenza aggiunta che il motore inferenzialeù
%introduce quando risolve una regola, quindi vado ad impostare una regola tramite OR, che mi fa ad interrompere un loop
coll1(X,Y):-coll(Y,X). 
coll1(X,Y):-coll(X,Y). %Questa regola risulta inutile, ma mi permette di prevenire il loop
/*INOLTRE: Vado anche a cambiare il nome del predicato, in questo modo, vado semplicemente ad evitare il loop*/


%LE DISTANZE: Vado a introdurre una nuova nuova variabile, che mi specifica la distanza tra le due città
coll(na, ro, 220).
coll(ro, fi, 200).
coll(fi, bo, 100).
coll(na, sa, 60).
coll(sa, ro, 280).


%IN PARTICOLA MODO: Anche in questo caso devo andare ad usare una regola di simmetria in modo da andare comunque a rispettare il
%collegamento bidirezionale tra le due città

%Nota, viene commentato in modo da non generare errori
%coll(X,Y,C):-coll(Y,X,C).

%ATTENZIONE: Anche in questo caso, posso comunqe avere un problema di Loop, per gli stessi motivi di cui sopra, quindi devo adoperare
%il medesimo meccanismo che ho usato sopra per andare a risolvere questo Loop
coll1(X,Y,C):-coll(Y,X,C). 
coll1(X,Y,C):-coll(X,Y,C).
/*ANCHE QUI: Il nome del predicato è differente, questo mi consente di andare ad evitare i loop*/

%L'ALGORITMO DEL COMMESSO VIAGGIATORE: Come anticipato nella teoria, dobbiamo sempre andare a considerare un passo bae ed uno ricorsivo
%-PASSO BASE:Immagino che ci sia un COLLEGAMENTO diretto tra le due città
collegamento(Ci, Cf, Lp, [Ci,Cf], C):-
coll1(Ci, Cf, C),
not(member(Ci, Lp)),
not(member(Cf, Lp)).

%-PASSO RICORSIVO: Vado a scomporre il problema in un problema più piccolo, andando a considerare una città intermedia, direttamenteù
%collegata alla citàà iniziale e spostando il problema su questa
collegamento(Ci, Cf, Lp, [Ci|L1c], C):-
coll1(Ci, Cint, C1),
not(member(Ci, Lp)),
not(member(Cint, Lp)),
collegamento(Cint, Cf, [Ci|Lp], L1c, C2),
C is C1+C2.
