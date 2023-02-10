cc=g++
deps= point.h rettangolo.h 
obs= point.o rettangolo.o driver.o
flag= -std=c++11

%.o: %.cpp $(deps)
	$(cc) -c $< $(flag)

driver: $(obs)
	$(cc) -o $@ $^ $(flag)