cc =g++
flags= -std=c++11 -pedantic 
deps= container.h box.h box_giacenza.h
obj= container.o box.o box_giacenza.o driver.o

%.o: %.cpp $(deps)
	$(cc) -c $< $(flags)
driver: $(obj)
	$(cc) -o $@ $^ $(flags)