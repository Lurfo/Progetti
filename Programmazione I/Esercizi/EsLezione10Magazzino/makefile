cc = g++ 
flags = -std=c++11 -pedantic 
deps = box.h
obj = driver.o box.o

%.o : %.cpp $(deps)
	$(cc) -c $< $(flags)

driver: $(obj)
	$(cc) -o $@ $^ $(flags)