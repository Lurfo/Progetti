cc = gcc 

dep = header.h semafor.h

all: main client server

main: main.o 
	
	gcc -o main main.o

client: client.o

	gcc -o client client.o

server: server.o semafor.o
	
	gcc -o server server.o semafor.o

%.o: %.c $(dep)

	$(cc) -c $<


clean: 
	rm -f main
	rm -f client 
	rm -f server

	rm -f *.o