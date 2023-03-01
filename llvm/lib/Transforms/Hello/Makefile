PLUGIN = Hello

LLVM_DIR = /home/jeffrey/Research/llvm-project
LLVM_BUILD_DIR = $(LLVM_DIR)/build
CLANG_DIR = $(LLVM_DIR)/clang
CLANG = $(LLVM_BUILD_DIR)/bin/clang
FORCE_USE_ABI=0


CXX = g++
CC = gcc 
INCLUDES=-I$(LLVM_DIR)/llvm/include
CFLAGS = -g -Wall $(INCLUDES)
LDLIBS = 

CXXFLAGS  = -I$(LLVM_DIR)/include -I$(CLANG_DIR)/include -I$(LLVM_DIR)/llvm/include
CXXFLAGS += -I$(LLVM_BUILD_DIR)/include -I$(LLVM_BUILD_DIR)/tools/clang/include
CXXFLAGS += ${EXTRA_FLAGS}
CXXFLAGS += -D__STDC_LIMIT_MACROS -D__STDC_CONSTANT_MACROS -Wno-long-long
CXXFLAGS += -fPIC -fvisibility-inlines-hidden
CXXFLAGS += -fno-exceptions -fno-rtti -std=c++11
CXXFLAGS += -Wall -D_GLIBCXX_USE_CXX11_ABI=${FORCE_USE_ABI}

LDFLAGS = -g -shared -Wl,-undefined,dynamic_lookup

.PHONY: default
default: hello

$(PLUGIN): $(PLUGIN).o
	$(CXX) $(LDFLAGS) $^ -o $@

$(PLUGIN).o: $(PLUGIN).cpp
	$(CXX) -c $(CXXFLAGS) $^ -o $@

hello: hello.o hello.ll hello.bc
	$(CC) $< -o $@
hello.o: hello.c hello.h
	$(CC) -c $< -o $@

.PHONY: hello.ll
hello.ll: hello.c
	clang -O3 -emit-llvm $^ -S -o hello.ll

.PHONY: hello.bc
hello.bc: hello.c
	clang -O3 -emit-llvm $^ -c -o hello.bc

.PHONY: LLVM$(PLUGIN).so
LLVM$(PLUGIN).so:
	cd ../../../../build && gmake

.PHONY: clean
clean:
	rm -rf $(PLUGIN) *.o a.out core

.PHONY: all 
all: clean $(PLUGIN)

.PHONY: run_pass
run_pass:
	opt -enable-new-pm=0 --debug-pass=Structure -load ../../../../build/lib/LLVM$(PLUGIN).so -hello2 < hello.bc > /dev/null

.PHONY: pass_c
pass_c: hello LLVM$(PLUGIN).so run_pass

.PHONY: pass
pass: hello run_pass
