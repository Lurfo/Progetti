cc=g++ 
flags= -std=c++11 -pedantic -Wall
dep= StringNode.h StringList.h
obj= driver.o StringList.o 

%.o: %.cpp $(dep)
	$(cc) -c $< $(flags)

driver: $(obj)
	$(cc) -o $@ $^ $(flags)