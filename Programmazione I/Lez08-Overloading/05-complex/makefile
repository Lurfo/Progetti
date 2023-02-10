driver: driver.o complex.o
	g++ -o driver driver.o complex.o -std=c++11
driver.o: driver.cpp complex.h
	g++ -c driver.cpp -std=c++11
complex.o: complex.cpp complex.h
	g++ -c complex.cpp -std=c++11 