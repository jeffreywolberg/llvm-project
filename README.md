## How to Get Started with the Forked Repo (Edited 03/12/2023)
The best instructions are [here](https://llvm.org/docs/CMake.html) and [here](https://llvm.org/docs/GettingStarted.html). I will summarize the steps to build LLVM below:

At the root directory, 
1. ```mkdir build && cd build```
2. ```cmake ../```
3. ```sudo make -j$(NPROC)```. This should take a decent amount of time (~20-40 min).
4. ```cmake --build . --target install```
As a test, ensure that `build/bin/opt` has been created.

## How to Run An LLVM IR Function Pass (Edited 03/12/2023)
Navigate to `llvm/lib/Transforms/FuncArgParser`, which is the folder where our [LLVM IR Pass](https://llvm.org/docs/WritingAnLLVMPass.html) is written.

`FuncArgParser.cpp` is the .cpp file which implements our FuncArgParser LLVM IR pass.
Running `make pass` will compile `example/hello.c` into a `.bc` file and run a command that passes it through the FuncArgParser LLVM IR pass. It should output in stdout the functions' arg types in the canonical form `funcName$argNo:arg_LLVM_IR_Type`. See the Makefile for the actual commands being run.

To recompile the pass, run ```make LLVMFuncArgParser.so```
To generate a `.bc` file from a `.c` file, run ```make $(TARGET).bc```, though make sure to edit the `TARGET_DIR` and `TARGET_FILE` variables in the Makefile.

Other specifics about writing and configuring a pass can be found [here](https://llvm.org/docs/WritingAnLLVMPass.html)

# The LLVM Compiler Infrastructure

Welcome to the LLVM project!

This repository contains the source code for LLVM, a toolkit for the
construction of highly optimized compilers, optimizers, and run-time
environments.

The LLVM project has multiple components. The core of the project is
itself called "LLVM". This contains all of the tools, libraries, and header
files needed to process intermediate representations and convert them into
object files. Tools include an assembler, disassembler, bitcode analyzer, and
bitcode optimizer.

C-like languages use the [Clang](http://clang.llvm.org/) frontend. This
component compiles C, C++, Objective-C, and Objective-C++ code into LLVM bitcode
-- and from there into object files, using LLVM.

Other components include:
the [libc++ C++ standard library](https://libcxx.llvm.org),
the [LLD linker](https://lld.llvm.org), and more.

## Getting the Source Code and Building LLVM

Consult the
[Getting Started with LLVM](https://llvm.org/docs/GettingStarted.html#getting-the-source-code-and-building-llvm)
page for information on building and running LLVM.

For information on how to contribute to the LLVM project, please take a look at
the [Contributing to LLVM](https://llvm.org/docs/Contributing.html) guide.

## Getting in touch

Join the [LLVM Discourse forums](https://discourse.llvm.org/), [Discord
chat](https://discord.gg/xS7Z362), or #llvm IRC channel on
[OFTC](https://oftc.net/).

The LLVM project has adopted a [code of conduct](https://llvm.org/docs/CodeOfConduct.html) for
participants to all modes of communication within the project.
