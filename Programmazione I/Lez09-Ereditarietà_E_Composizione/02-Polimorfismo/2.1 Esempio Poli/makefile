cc=g++
flags=-std=c++11
deps= account.h CheckingAccount.h 
obj= driver.o CheckingAccount.o account.o

%.o: %.cpp $(deps)
	$(cc) -c $< $(flags)

driver: $(obj)
	$(cc) -o $@ $^