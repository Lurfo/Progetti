obj = chat.o function.o
dep = function.h

all: chat

chat: ${obj}
	gcc -o $@ $^

%.o: %.c ${dep}
	gcc -c $<


clean: 
	rm -f *.o
	rm -f chat