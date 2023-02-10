cc=g++
flag=-std=c++11
deps= poli.h
obj= driver.o poli.o

%.o: %.cpp $(deps)
	$(cc) -c $< $(flag)

driver: $(obj)
	$(cc) -o $@ $^ $(flag)