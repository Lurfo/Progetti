cc=g++
flags=-std=c++11
obj=matrix.o driver.o
dep=matrix.h

%.o: %.c $(dep)
	$(cc) -c $< $(flags)

driver: $(obj)
	$(cc) -o $@ $^ $(flags)