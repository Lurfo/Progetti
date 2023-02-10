CC=g++
CFLAGS=-std=c++11
DEPS= Queue.h CircleList.h Node.h Container.h Box.h Box_giacenza.h
OBJ= driver.o 

%.o: %.cpp $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

driver: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)