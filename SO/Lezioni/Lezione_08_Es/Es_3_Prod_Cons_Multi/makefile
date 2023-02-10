all: main p1 p2 p3

main: main.o
	gcc -o $@ $^

p1: p1.o function.o
	gcc -o $@ $^

p2: p2.o function.o
	gcc -o $@ $^

p3: p3.o 
	gcc -o $@ $^

%.o: %.c function.h
	gcc -c $<

clean: 
	rm -f *.o
	rm -f main
	rm -f p1
	rm -f p2
	rm -f p3

