CC = gcc
CFLAGS = -pedantic -Wall -pthread -lrt
DEPS = rt-lib.h parameters.h
CLR = *.o plant controller reference activeBackup diag diagWCET

all: plant controller reference activeBackup diag diagWCET

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
activeBackup: activeBackup.o rt-lib.o
	$(CC) -o $@ $^ $(CFLAGS)
plant: plant.o rt-lib.o 
	$(CC) -o $@ $^ $(CFLAGS)
controller: controller.o rt-lib.o 
	$(CC) -o $@ $^ $(CFLAGS)
reference: reference.o
	$(CC) -o $@ $^ $(CFLAGS)
diag: diag.o
	$(CC) -o $@ $^ $(CFLAGS)
diagWCET: diagWCET.o
	$(CC) -o $@ $^ $(CFLAGS)
clean:
	rm -f $(CLR)