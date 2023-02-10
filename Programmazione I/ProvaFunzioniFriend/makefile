cc = g++
flags = -std=c++11 -pedantic 
obj = driver.o list.o
deps = list.h 

%.o: %.cpp $(deps)
	$(cc) -c $@ $< $(flags)

driver: $(obj)
	$(cc) -o $@ $^ $(flags)