
CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -Wno-unused-variable

all: alloc_class

alloc_class: test.o
	$(CC) $(FLAGS) -o alloc_class test.o 

test.o: test.cpp Allocator.h
	$(CC) $(FLAGS) -c test.cpp 

test: all
	./alloc_class

clean:
	rm -rf *.o alloc_class
