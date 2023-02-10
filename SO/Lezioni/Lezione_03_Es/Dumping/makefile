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

#In questo caso ho Modificato appositamente il makefile, in modo che il flag "-g" vada ad inserire il codice C durante il dump!
%.o: %.c ${DEP}
	gcc -c -g $<

#Posso andare a definire delle opzioni di pulizia anche in questo caso
clean: 
	rm -f *.o
	rm -f ./start
