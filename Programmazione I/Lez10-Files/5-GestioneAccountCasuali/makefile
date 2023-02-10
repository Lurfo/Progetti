cc=g++ 
flag= -std=c++11
deps= accounts.h
obj= accounts.o driver.o

%.o: %.cpp $(deps)
	$(cc) -c $< $(flag)

driver: $(obj)
	$(cc) -o $@ $^ $(flag)