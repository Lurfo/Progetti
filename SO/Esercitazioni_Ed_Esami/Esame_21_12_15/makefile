dep = header.h 
obj = main.o function.o
cc = cc

all: main

main: $(obj)

	$(cc) -o $@ $^

%.o: %.c $(dep)

	$(cc) -c $<

clean: 
	rm -f main
	rm -f *.o