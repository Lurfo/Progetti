#In questo caso, il makefile è uguale a
CURR=$(PWD)/

all: main

#Per essere generato, il file main ha buisogno  della libreria e del file oggetto main
#Quando lancio la direttiva di compilazione per il main, devo sempre andare a specificare anche il path dove si trova la
#libreria dinamica che ho definito!
#Oltre all'inclusione di vari flag!
main: calc.so main.o
	gcc -o main main.o -L$(CURR) -lcalc -Wl,-rpath,$(CURR)

main.o: 
	gcc -c main.c 

#Con questa direttiva ho la possibilità di andare a generare la libreria dinamica, ovviamente usando come forma dell'istruzione
#quella definita in "diamico.txt"
calc.so: libreria.o
	gcc -shared -Wl,-soname,libcalc.so -o libcalc.so libreria.o

#I file che compongono la libreria dinamica devono essere compilati usando il flag -fpic, che permette idi generare codice rilocabile
libreria.o: libreria.h
	gcc -c -fpic libreria.c 

clean: 
	rm -f *.o
	rm -f ./main
	rm -f libcalc.so