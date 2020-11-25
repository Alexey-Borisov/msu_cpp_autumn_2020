
CC=g++
FLAGS=-std=c++17  -Wall -Werror -Wextra -Wno-unused-variable

all: my_vector

my_vector: test.o
	$(CC) $(FLAGS) -o my_vector test.o 

test.o: test.cpp Vector.h Allocator.h Iterator.h
	$(CC) $(FLAGS) -c test.cpp 

test: all
	./my_vector

clean:
	rm -rf *.o my_vector
