//===- Hello.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements two versions of the LLVM "Hello World" pass described
// in docs/WritingAnLLVMPass.html
//
//===----------------------------------------------------------------------===//

#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Argument.h"
#include "llvm/IR/Type.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include <string>
#include <sstream>
using namespace llvm;

#define DEBUG_TYPE "hello"

STATISTIC(HelloCounter, "Counts number of functions greeted");

namespace {
  // Hello - The first implementation, without getAnalysisUsage.
  struct Hello : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    Hello() : FunctionPass(ID) {}

    void pr(int i, std::string argName, const char *title, long content) {
      std::stringstream ss;
      ss << "\t" << "Arg num: " << i << ", " << "Arg name: " << argName << ", " << title << ": " << content << "\n";
      errs() << ss.str();
      // errs().write();
    }

    void pr_type(int i, std::string argName, llvm::Type *type) {
      std::stringstream ss;
      ss << "\t" << "Arg num: " << i << ", " << "Arg name: " << argName << "Type: " << type << '\n';
      errs() << ss.str();
    }

    bool runOnFunction(Function &F) override {
      ++HelloCounter;
      errs() << "Hello: ";
      errs().write_escaped(F.getName()) << '\n';

      // std::cout << "Test" << '\n';
      for (const Argument &arg : F.args()) {
        // arg.dump();
        int argNo = arg.getArgNo();
        std::string argName = arg.getName().str();
        pr(argNo, argName, "Has by val attr", arg.hasByValAttr());
        pr(argNo, argName, "Has by ref attr", arg.hasByRefAttr());
        pr(argNo, argName, "hasPassPointeeByValueCopyAttr", arg.hasPassPointeeByValueCopyAttr());
        // pr(argNo, argName, "getPassPointeeByValueCopySize", arg.getPassPointeeByValueCopySize());
        pr(argNo, argName, "hasPointeeInMemoryValueAttr", arg.hasPointeeInMemoryValueAttr());
        pr(argNo, argName, "getDereferenceableBytes", arg.getDereferenceableBytes());
        // pr(argNo, argName, "hasPointeeInMemoryValueAttr", arg.hasPointeeInMemoryValueAttr());
        // pr(argNo, argName, "hasPointeeInMemoryValueAttr", arg.hasPointeeInMemoryValueAttr());

        // pr(argNo, argName, "getParamAlignment", arg.getParamAlignment());
        pr_type(argNo,  argName, arg.getParamByValType());
        pr_type(argNo, argName, arg.getParamStructRetType());
        pr_type(argNo, argName, arg.getParamByRefType());
        // pr(argNo, argName, "Has by val attr", arg.hasByValAttr());
        // pr(argNo, argName, "Has by val attr", arg.hasByValAttr());

        // errs().write_escaped("Test") << '\n';
      }
      return false;
    }
  };
}

char Hello::ID = 0;
static RegisterPass<Hello> X("hello", "Hello World Pass");



namespace {

  // Hello2 - The second implementation with getAnalysisUsage implemented.
  struct Hello2 : public FunctionPass {
    
    void pr(int i, std::string argName, const char *title, long content) {
      std::stringstream ss;
      ss << "\t" << "Arg num: " << i << ", " << "Arg name: " << argName << ", " << title << ": " << content << "\n";
      errs() << ss.str();
      // errs().write();
    }

    void pr_type(int i, std::string argName, llvm::Type *type) {
      std::stringstream ss;
      ss << "\t" << "Arg num: " << i << ", " << "Arg name: " << argName << "Type: " << type << '\n';
      errs() << ss.str();
      // type->dump();
      // type->print(outs());

      // std::string type_str;
      // llvm::raw_string_ostream rso(type_str);
      // type->print(rso);
      // errs() << rso.str();

      // errs() << "\n";
    }

    static char ID; // Pass identification, replacement for typeid
    Hello2() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      ++HelloCounter;
      errs() << "Hello: ";
      errs().write_escaped(F.getName()) << '\n';

      // std::cout << "Test" << '\n';
      for (const Argument &arg : F.args()) {
        // arg.dump();
        int argNo = arg.getArgNo();
        std::string argName = arg.getName().str();
        pr(argNo, argName, "Has by val attr", arg.hasByValAttr());
        pr(argNo, argName, "Has by ref attr", arg.hasByRefAttr());
        pr(argNo, argName, "hasPassPointeeByValueCopyAttr", arg.hasPassPointeeByValueCopyAttr());
        // pr(argNo, argName, "getPassPointeeByValueCopySize", arg.getPassPointeeByValueCopySize());
        pr(argNo, argName, "hasPointeeInMemoryValueAttr", arg.hasPointeeInMemoryValueAttr());
        pr(argNo, argName, "getDereferenceableBytes", arg.getDereferenceableBytes());
        // pr(argNo, argName, "hasPointeeInMemoryValueAttr", arg.hasPointeeInMemoryValueAttr());
        // pr(argNo, argName, "hasPointeeInMemoryValueAttr", arg.hasPointeeInMemoryValueAttr());

        // pr(argNo, argName, "getParamAlignment", arg.getParamAlignment());
        pr_type(argNo,  argName, arg.getParamByValType());
        pr_type(argNo, argName, arg.getParamStructRetType());
        pr_type(argNo, argName, arg.getParamByRefType());
        // pr(argNo, argName, "Has by val attr", arg.hasByValAttr());
        // pr(argNo, argName, "Has by val attr", arg.hasByValAttr());

        // errs().write_escaped("Test") << '\n';
      }

      return false;
    }

    // We don't modify the program, so we preserve all analyses.
    void getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.setPreservesAll();
    }
  };
}

char Hello2::ID = 0;
static RegisterPass<Hello2>
Y("hello2", "Hello World Pass (with getAnalysisUsage implemented)");
//