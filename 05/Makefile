
CC=g++
FLAGS=-std=c++17  -Wall -Werror -Wextra -Wno-unused-variable

all: serializer_class

serializer_class: test.o
	$(CC) $(FLAGS) -o serializer_class test.o 

test.o: test.cpp Serializer.h
	$(CC) $(FLAGS) -c test.cpp 

test: all
	./serializer_class

clean:
	rm -rf *.o serializer_class