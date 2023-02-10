obj  = function.o monitor_hoare.o main.o
dep = function.h monitor_hoare.h

all: main

main: ${obj}
	gcc -o $@ $^

%.o: %.c ${dep}
	gcc -c $<

clean: 
	rm -f *.o
	rm -f main