# Specify compiler
CC=gcc

# Specify linker
LINK=gcc

# Build all target
.PHONY : all
all : atm

# Link the object files and dependent libraries into a binary
atm : atm.o
	$(LINK) -o atm atm.o -lpthread -lstdc++

# Compile the source files into object files
atm.o : atm.cpp atm.h account.h machine.h
	$(CC) -c atm.cpp -pthread -o atm.o

# Clean target
.PHONY : clean
clean :
	rm atm.o atm
