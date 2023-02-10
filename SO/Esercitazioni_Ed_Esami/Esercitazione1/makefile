OBJ= semafor.o  main.o
OBJ1= semafor.o gen.o
OBJ2= semafor.o elabor.o
OBJ3= semafor.o analizz.o
DEPTH = semafor.h 

all: gen elabor analizz main

gen: ${OBJ1}
	gcc -o $@ $^

elabor: ${OBJ2}
	gcc -o $@ $^

analizz: ${OBJ3}
	gcc -o $@ $^

main: ${OBJ}
	gcc -o $@ $^

%.o: %.c ${DEPTH}
	gcc -c $<

clean: 
	rm -f *.o
	rm -f main
	rm -f gen
	rm -f elabor
	rm -f analizz