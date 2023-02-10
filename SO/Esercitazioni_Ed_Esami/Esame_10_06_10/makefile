cc = gcc

obj = main.o function.o monitor_signal_continue.o

dep = header.h monitor_signal_continue.h

all: main

main: $(obj)

	$(cc) -o $@ $^

%.o: %.c $(dep)

	$(cc) -c $<

clean: 

	rm -f *.o 
	rm -f main