cc = g++
obj = tris.o driver.o
deps=tris.h
flags=-std=c++11

%.o: %.cpp $(deps)
	$(cc) -c $< $(flags)

driver: $(obj)
	$(cc) -o $@ $^ $(flags)