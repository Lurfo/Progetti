#Vediamo che il Makefile, in questo caso è un po' particolare!
#Qui abbiamo tutte le parole chiave che possiamo sfruttare!
cc=g++
obj= date.o employee.o driver.o
flag=-std=c++11 -pedantic -Wall
dep= date.h employee.h

#Ovviamente, abbiamo che l'ultimo elemento che ci occorre è il programma driver!
#esso, dipende dai valori che abbiamo deifnito nella parola chiave obj!
driver: $(obj)

#Abbiamo due comandi particolari: 
# $@ fa riferimento a quello che è scritto subito prima di ":"
# $^ fa riferimento agli elementi che sono a destra di ":"

	$(cc) -o $@ $^ 

# %.o -> Fa riferimento a tutti i file che hanno estensione .o
# %.cpp -> Fa riferimento a tutti i file che hanno come estensione .cpp
%.o: %.cpp $(dep)

# $< -> Fa riferimento al primo valore della lista della dipendenze, definita nella parola chiave "flag"
	$(cc) -c $< $(flag)


#Usando quindi questi comandi si è scritto un makefile molto più semplice e leggibile!


