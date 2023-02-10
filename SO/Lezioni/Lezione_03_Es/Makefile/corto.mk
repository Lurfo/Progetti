#Nel makefile corto vado a specificare delle dipendenze!
DEP=libreria.h
OBJ=libreria.o main.o

all: start
#in questo caso ho che: 
# $@ indica l'elemento che si trova a sinistra dei :
# $^ indica la lista delle dipendenze
# $< indica il primo elemento della lista delle dipendenze

start: ${OBJ}
	gcc -o $@ $^

%.o: %.c ${DEP}
	gcc -c $<

#Posso andare a definire delle opzioni di pulizia anche in questo caso
clean: 
	rm -f *.o
	rm -f ./start
