cc = g++ 
flags = -std=c++11 -pedantic
deps= cliente.h palestra.h data.h
obj= data.o cliente.o palestra.o driver.o

%.o: %.cpp $(deps)
	$(cc) -c $< $(flags)

driver: $(obj)
	$(cc) -o $@ $^ $(flags)
