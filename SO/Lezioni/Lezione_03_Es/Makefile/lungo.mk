#Definisco il makefile per il programma che ho creato, posso avere due tipi di makefile: 
#Uno lungo, in cui devo specificare a mano tutte le dipendenze, mente uno più corto dove posso specificare le dipendenze in
#modo più semplice


#MAKEFILE CON DIPENDENZE SPECIFICATE PER INTERO
#Nota che siccome ho specificato un nome differente, lo devo lanciare con il comando "make -f lungo.mk"


#Questa è la prima regola che devo stabilire, che poi sarebbe il mio file exec
all: start

start: libreria.o main.o
	gcc -o start libreria.o main.o

libreria.o: libreria.c libreria.h
	gcc -c libreria.c

main.o: main.c libreria.h
	gcc -c main.c


#Posso anche andare a definire degli operatori di pulizia!
#il primo rimuove tutti i file che hanno .o come estensione
#il secondo serve e rimuovere il mio eseguibile, così, in caso di aggiornamento del programma sono sicuro di aggiornare anche
#il file eseguibile
clean:
	rm -f *.o 
	rm -f ./start