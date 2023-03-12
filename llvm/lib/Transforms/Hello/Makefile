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

$(PLUGIN): $(PLUGIN).o
	$(CXX) $(LDFLAGS) $^ -o $@

$(PLUGIN).o: $(PLUGIN).cpp
	$(CXX) -c $(CXXFLAGS) $^ -o $@

.PHONY: LLVM$(PLUGIN).so
LLVM$(PLUGIN).so:
	cd $(LLVM_DIR)/build && gmake

.PHONY: clean
clean:
	rm -rf $(PLUGIN) *.o a.out core

.PHONY: all 
all: clean $(PLUGIN)
