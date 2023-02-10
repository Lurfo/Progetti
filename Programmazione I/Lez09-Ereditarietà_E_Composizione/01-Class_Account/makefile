cc=g++
flags=-std=c++11
deps= account.h CheckingAccount.h SavingsAccount.h
obj= driver.o CheckingAccount.o account.o SavingsAccount.o

%.o: %.cpp $(deps)
	$(cc) -c $< $(flags)

driver: $(obj)
	$(cc) -o $@ $^