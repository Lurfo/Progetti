cc = gcc
flags = -pthread -o
obj = main.o function.o
dep = function.h


all: main

main: $(obj)
	$(cc) $(flags) $@ $^

%.o: %.c $(dep)
	$(cc) -c $<

clean: 
	rm -f main
	rm -f *.o