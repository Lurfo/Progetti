OBJ= main.o function.o
DEP=function.h

all: main

main: ${OBJ}
	gcc -o $@ $^

%.o: %.c ${DEP}
	gcc -c $<

clean: 
	rm -f *.o 
	rm -f main