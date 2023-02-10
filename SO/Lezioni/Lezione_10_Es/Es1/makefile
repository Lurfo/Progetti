CC=gcc

flags= -pthread -o

#Nota, nelle versioni precedenti della libreria, il flag era "lpthread"

all: main

main: main.c
	$(CC) $(flags) $@ $^


clean: 
	rm -f main