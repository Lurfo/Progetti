time: time.o timeClass.o 
	g++ time.o timeClass.o -o time

time.o: time.cpp timeClass.h
	g++ -c time.cpp -pedantic -Wall -std=c++11

timeClass.o: timeClass.cpp timeClass.h
	g++ -c timeClass.cpp -pedantic -Wall -std=c++11