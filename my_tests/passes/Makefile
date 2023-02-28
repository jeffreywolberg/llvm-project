CC = gcc
CXX = g++
# INCLUDES=-I/Users/jeffrey/Coding/frameworks/llvm-project/llvm/include
INCLUDES=-I/opt/homebrew/opt/llvm/include
CFLAGS = -g -Wall $(INCLUDES)
LDFLAGS = -g
LDLIBS = 

hello_world: hello_world.o
	$(CC) $(LDFLAGS) $^ -o $@

hello_world.o: hello_world.cpp
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -rf hello_world *.o a.out core

.PHONY: all
all: clean hello_world

.PHONY: run
run: all
	hello_world
