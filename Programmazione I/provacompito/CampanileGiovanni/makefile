cc =g++
flag=-std=c++11 -pedantic
obj= driver.o book.o prestiti.o data.o
deps= data.h book.h prestiti.h list.h node.h

%.o: %.cpp $(deps)
	$(cc) -c $< $(flag)

driver: $(obj)
	$(cc) -o $@ $^ $(flag)