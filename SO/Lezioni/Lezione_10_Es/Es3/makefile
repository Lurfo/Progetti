cc = gcc
flags = -pthread -o
obj = main.o function.o

all: main

main: $(obj)
	$(cc) $(flags) $@ $^

%.o: %.c
	$(cc) -c $<

clean: 
	rm -f main
	rm -f *.o