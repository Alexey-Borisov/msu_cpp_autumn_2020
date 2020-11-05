
CC=g++
FLAGS=-std=c++17  -Wall -Werror -Wextra -Wno-unused-variable

all: bigint_class

bigint_class: test.o
	$(CC) $(FLAGS) -o bigint_class test.o 

test.o: test.cpp BigInt.h
	$(CC) $(FLAGS) -c test.cpp 

test: all
	./bigint_class

clean:
	rm -rf *.o bigint_class