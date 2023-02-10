CC = g++

CFLAGS = -std=c++11 -pedantic

DEPS = Geeks.h 

OBJS = Fantaware.o

%.o: %.cpp ${DEPS}
	${CC} -c -o $@ $< ${CFLAGS}

Fantaware: ${OBJS}
	${CC} -o $@ $^ ${CFLAGS}