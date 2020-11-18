
CC=g++
FLAGS=-std=c++17  -Wall -Werror -Wextra -Wno-unused-variable

all: format

format: test.o
	$(CC) $(FLAGS) -o format test.o 

test.o: test.cpp format.h
	$(CC) $(FLAGS) -c test.cpp 

test: all
	./format

clean:
	rm -rf *.o format
