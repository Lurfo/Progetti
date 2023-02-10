cc=g++
obj= driver.o data.o
deps=data.h
flag=-std=c++11

%.o: %.cpp $(deps)
	$(cc) -c $< $(flag)

driver: $(obj)
	$(cc) -o $@ $^