all: MainTeatroCi

MainTeatroCi: procedure.o semafori.o MainTeatroCi.o
	gcc -o MainTeatroCi MainTeatroCi.o procedure.o semafori.o 

MainTeatroCi.o: MainTeatroCi.c
	gcc -c MainTeatroCi.c

procedure.o: procedure.h procedure.c
	gcc -c procedure.c

semafori.o: semafori.h semafori.c
	gcc -c semafori.c

clean: 
	rm -rf *.o
	rm -rf MainTeatroCi 
