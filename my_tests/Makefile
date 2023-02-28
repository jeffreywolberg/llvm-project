CXX = g++
CC = gcc 
INCLUDES=-I/home/jeffrey/Research/llvm-project/llvm/include
CFLAGS = -g -Wall $(INCLUDES)
LDFLAGS = -g
LDLIBS = 

.PHONY: default
default: hello

Hello: Hello.o
        $(CXX) $(CFLAGS) $^ -o $@
Hello.o: Hello.cpp

hello: hello.o hello.ll hello.bc
        $(CC) $< -o $@
hello.o: hello.c
        $(CC) -c $^ -o $@

.PHONY: hello.ll
hello.ll: hello.c
        clang -O3 -emit-llvm $^ -S -o hello.ll

.PHONY: hello.bc
hello.bc: hello.c
        clang -O3 -emit-llvm $^ -c -o hello.bc



.PHONY: clean
clean:
	rm -rf Hello *.o a.out core

.PHONY: all 
all: clean Hello

.PHONY: pass
pass: hello
        opt -enable-new-pm=0 -load ../../../../build/lib/LLVMHello.so -hello2 < hello.bc > /dev/null
