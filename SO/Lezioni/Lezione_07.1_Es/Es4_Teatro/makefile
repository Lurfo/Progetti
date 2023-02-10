OBJ= semafor.o function.o main.o
OBJ1=vedo.o semafor.o
DEPTH = semafor.h function.h

all: vedo main

vedo: ${OBJ1}
	gcc -o $@ $^

main: ${OBJ}
	gcc -o $@ $^

%.o: %.c ${DEPTH}
	gcc -c $<

clean: 
	rm -f *.o
	rm -f main
	rm -f vedo