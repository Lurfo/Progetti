cc=g++
flags=-std=c++11
deps= employees.h commission.h baseecomm.h base.h
obj= employees.o commission.o baseecomm.o base.o driver.o 

%.o: %.cpp $(deps)
	$(cc) -c $< $(flags)

driver: $(obj)
	$(cc) -o $@ $^ $(flags)