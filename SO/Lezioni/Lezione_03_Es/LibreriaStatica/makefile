#definsco dunque il makefile 
CURR=${PWD}


all: start
#Il file eseguibile ha bisogno come dipendenza solo della libreria che contiene le funzioni di calcolo!
start: static.a
	gcc -o start main.c -L$(CURR) -lstatic

#Definisco il comando per creare la libreria
static.a: libreria.o
	ar rcs libstatic.a libreria.o

libreria.o: libreria.h
	gcc -c libreria.c

clean: 
	rm -f *.o
	rm -f libstatic.a
	rm -f ./start