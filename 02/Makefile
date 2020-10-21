
CC=g++
FLAGS=-std=c++17 -Wall -Werror -Wextra -Wno-unused-variable

all: parser

parser: test.o
	$(CC) $(FLAGS) -o parser test.o 

test.o: test.cpp Parser.h
	$(CC) $(FLAGS) -c test.cpp 

test: all
	./parser

clean:
	rm -rf *.o parser
