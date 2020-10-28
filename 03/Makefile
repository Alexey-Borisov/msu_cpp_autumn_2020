
CC=g++
FLAGS=-std=c++17 -Wall -Wextra -Werror -Wno-unused-variable 

all: matrix_class

matrix_class: test.o
	$(CC) $(FLAGS) -o matrix_class test.o 

test.o: test.cpp Matrix.h Series.h
	$(CC) $(FLAGS) -c test.cpp 

test: all
	./matrix_class

clean:
	rm -rf *.o matrix_class
