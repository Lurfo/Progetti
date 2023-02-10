cc=g++ 
flags= -std=c++11 -pedantic
deps= classes.h data.h
obj= driver.o classes.o data.o

%.o: %.cpp $(deps)
	$(cc) -c $< $(flags)

driver: $(obj)
	$(cc) -o $@ $^ $(flags)