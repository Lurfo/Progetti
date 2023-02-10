OBJ= semafor.o main.o
DEP=semafor.h

all: main

main: ${OBJ}
	gcc -o $@ $^

%.o: %.c ${DEP}
	gcc -c $<

clean:
	rm -f *.o
	rm -f main