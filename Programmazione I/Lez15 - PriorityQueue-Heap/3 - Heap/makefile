cc=g++ 
deps=heap.h
obj=heap.o driver.o
flags= -std=c++11

%.o: %.cpp $(deps)
	$(cc) -c $< $(flags)

driver: $(obj)
	$(cc) -o $@ $^ $(flags)