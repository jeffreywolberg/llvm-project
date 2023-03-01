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

#include "llvm/IR/Dominators.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Support/Casting.h"
#include "llvm-c/Core.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Argument.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include <string>
#include <sstream>
using namespace llvm;

#define DEBUG_TYPE "hello2"

STATISTIC(HelloCounter, "Counts number of functions greeted");

// convert llvm::Type* to char*, returns length of str
int get_type_str(Type *type, char *buf, int max_len) {
  if (!type) return -1;
  
  std::string str;
  raw_string_ostream os(str);
  type->print(os);
  
  strncpy(buf, str.c_str(), max_len); // limit to 100 characters
  return strlen(buf);
}

namespace {

  // Hello2 - The second implementation with getAnalysisUsage implemented.
  struct Hello2 : public FunctionPass {
    
    static char ID; // Pass identification, replacement for typeid
    Hello2() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      char funcName[70] = {0};
      char outBuf[200] = {0};
       char type[50] = {0};

      strcpy(funcName, F.getName().str().c_str());
      
      for (const Argument &arg : F.args()) {
        int argNo = arg.getArgNo();
        get_type_str(arg.getType(), type, sizeof(type));

        sprintf(outBuf, "%s$%02d:%s\n", funcName, argNo, type);
        outs() << outBuf;
      }

      Type *retType = F.getReturnType();
      get_type_str(retType, type, sizeof(type));
      sprintf(outBuf, "%s$%02d:%s\n", funcName, -1, type);
      outs() << outBuf;

      return false;
    }

    // We don't modify the program, so we preserve all analyses.
    void getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.setPreservesAll();
      // AU.addRequired<DominatorTreeWrapperPass>();
      // AU.addRequired<LoopInfoWrapperPass>();
      // AU.addRequired<VerifyPass>();
    }
  };
}

char Hello2::ID = 0;
static RegisterPass<Hello2>
Y("hello2", "Hello World Pass (with getAnalysisUsage implemented)");
//