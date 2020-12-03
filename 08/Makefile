CC=g++
FLAGS=-std=c++17 -pthread -Wall -Werror -Wextra -Wno-unused-variable

all: thread_pool

thread_pool: test.o
	$(CC) $(FLAGS) -o thread_pool test.o

test.o: test.cpp ThreadPool.h
	$(CC) $(FLAGS) -c test.cpp

test: all
	./thread_pool

clean:
	rm -rf *.o thread_pool
