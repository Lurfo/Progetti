GCC=gcc
OBJ= main.o semafor.o
DEPH=semafor.h

all: main

#RICORDA: L'eseguibile ha solo bisogno dei file oggetto!
main:${OBJ}
	${GCC} -o $@ $^

#Per definire i file oggetto devo sempre specificare le dipendenze!
%.o: %.c ${DEPH}
	${GCC} -c $<

#Definizione delle funzioni di pulizia!
clean: 
	rm -f *.o
	rm -f main