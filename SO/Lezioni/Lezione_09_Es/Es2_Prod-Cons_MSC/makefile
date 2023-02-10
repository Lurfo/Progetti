obj = main.o function.o monitor_signal_continue.o
dep = function.h monitor_signal_continue.h

all: main

main: ${obj}
	gcc -o $@ $^

%.o: %.c ${dep}
	gcc -c $<

clean: 
	rm -f *.o
	rm -f main