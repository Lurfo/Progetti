#Andiamo a creare del nostro programma 

#Per generare il file veicolo abbiamo bisogno dei due gile oggetto
#Che derivano, uno dal driver, l'altro dal fie di specifica delle funzioni
veicolo: veicolo.o veicoloc.o
	g++ -o veicolo veicolo.o veicoloc.o

#Per generare il file ogetto del nostro programma abbiamo bisogno di 
#Del driver cpp e del file Header
voicolo.o: veicolo.cpp veicoloc.h
	g++ -c veicolo.cpp -pedantic -Wall -std=c++11

#Devo generare il file oggetto del file che specifica le funzioni dell'header
veicoloc.o: veicoloc.cpp veicoloc.h
	g++ -c veicoloc.cpp -pedantic -Wall -std=c++11