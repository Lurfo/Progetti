all: main_ex

main_ex: main.o generatore.o filtro.o checksum.o visualizzatore.o monitor_signal_continue.o
	gcc -o main_ex main.o generatore.o filtro.o checksum.o visualizzatore.o monitor_signal_continue.o

main.o: main.c header.h
	gcc -c main.c

generatore.o: generatore.c header.h
	gcc -c generatore.c

filtro.o: filtro.c header.h
	gcc -c filtro.c

checksum.o: checksum.c header.h
	gcc -c checksum.c

visualizzatore.o: visualizzatore.c header.h
	gcc -c visualizzatore.c

monitor_signal_continue.o: monitor_signal_continue.c monitor_signal_continue.h
	gcc -c monitor_signal_continue.c

clean:
	ipcs -s | awk '$$4=="644" {print $$2}' | while read id; do ipcrm sem $$id; done
	ipcs -m | awk '$$4=="644" {print $$2}' | while read id; do ipcrm shm $$id; done
	ipcs -q | awk '$$4=="644" {print $$2}' | while read id; do ipcrm msg $$id; done
	rm -rf main_ex
	rm -rf *.o
