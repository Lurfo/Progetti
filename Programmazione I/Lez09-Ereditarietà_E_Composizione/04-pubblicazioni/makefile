cc=g++
flags= -std=c++11 -pedantic -Wall 
obj= publication.o book.o riviste.o convegno.o driver.o
deps= publication.h booh.h riviste.h convegno.h quickSort.h

%.o: %.cpp $(deps)
	$(cc) -o $< $(flags)

driver: $(obj)
	$(cc) -o $@ $^ $(flags)