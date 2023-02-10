cc=g++ 
flags= -std=c++11 -pedantic -Wall
deps=accounts.h
obj=accounts.o driver.o

%.o: %.cpp $(deps)
	$(cc) -c $< $(flags)

driver: $(obj)
	$(cc) -o $@ $^ $(flags)