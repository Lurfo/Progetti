CC=g++
CFLAGS=-std=c++11
DEPS= array.h array.cpp 
OBJ= main.o 

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)