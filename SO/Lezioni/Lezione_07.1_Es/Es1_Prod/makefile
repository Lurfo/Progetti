OBJ= main.o semafor.o function.o
DEPTH= semafor.h function.h

all: main

main: ${OBJ}
	gcc -o $@ $^

%.o: %.c ${DEPTH}
	gcc -c $<

clean: 
	rm -f *.o
	rm -f main