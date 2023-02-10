CC = g++

CFLAGS = -std=c++11 -pedantic -Wall

DEPS = container.h Box.h 

OBJS =containerprova.o

%.o: %.cpp ${DEPS}
	${CC} -c -o $@ $< ${CFLAGS}

containerprova: ${OBJS}
	${CC} -o $@ $^ ${CFLAGS}