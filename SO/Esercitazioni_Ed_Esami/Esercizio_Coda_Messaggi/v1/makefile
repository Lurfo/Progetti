obj = main.o function.o 
dep = header.h

all: main

main: ${obj}
	gcc -o $@ $^

%.o: %.c ${dep}
	gcc -c $<

clean: 
	rm -f *.o
	rm -f main