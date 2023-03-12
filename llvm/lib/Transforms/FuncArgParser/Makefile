PLUGIN = FuncArgParser
LLVM_IR_PASS_NAME = funcArgParser

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

TARGET_DIR = example
TARGET=$(TARGET_DIR)/hello

.PHONY: default
default: $(TARGET)

$(TARGET): $(TARGET).o $(TARGET).ll $(TARGET).bc
	$(CC) $< -o $@
$(TARGET).o: $(TARGET).c $(TARGET).h
	$(CC) -c $< -o $@

.PHONY: $(TARGET).ll
$(TARGET).ll: $(TARGET).c
	clang -O3 -emit-llvm $^ -S -o $(TARGET).ll

.PHONY: $(TARGET).bc
$(TARGET).bc: $(TARGET).c
	clang -O3 -emit-llvm $^ -c -o $(TARGET).bc

.PHONY: LLVM$(PLUGIN).so
LLVM$(PLUGIN).so:
	cd $(LLVM_DIR)/build && gmake

.PHONY: clean
clean:
	rm -rf $(PLUGIN) $(TARGET) $(TARGET_DIR)/*.ll $(TARGET_DIR)/*.bc $(TARGET_DIR)/*.o a.out core

.PHONY: run_pass
run_pass:
	opt -enable-new-pm=0 -opaque-pointers=0 -load $(LLVM_DIR)/build/lib/LLVM$(PLUGIN).so -$(LLVM_IR_PASS_NAME) < $(TARGET).bc

.PHONY: pass_c # compile the llvm IR pass and run it with the $(TARGET) file
pass_c: $(TARGET) LLVM$(PLUGIN).so run_pass

.PHONY: pass # run the llvm IR pass with the $(TARGET) file
pass: $(TARGET) run_pass
