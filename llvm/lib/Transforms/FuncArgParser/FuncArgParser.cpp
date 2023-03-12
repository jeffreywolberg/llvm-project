//===- FuncArgParser.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
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

#define DEBUG_TYPE "funcArgParser"

// convert llvm::Type* to char*, returns length of str
int get_type_str(Type *type, char *buf, int max_len) {
  if (!type) return -1;
  
  std::string str;
  raw_string_ostream os(str);
  type->print(os);
  
  strncpy(buf, str.c_str(), max_len);
  return strlen(buf);
}


// Dump to stdout the function arg type as follows: funcName$argNo:llvmIRType
void dumpFuncArgType(char *funcName, int argNo, Type *type) {
  char typeBuf[50] = {0}; // TODO: hardcoded for now, fix
  char outBuf[200] = {0};  // TODO: hardcoded for now, fix

  get_type_str(type, typeBuf, sizeof(typeBuf));
  sprintf(outBuf, "%s$%02d:%s\n", funcName, argNo, typeBuf);
  outs() << outBuf;
}

namespace {

// Implementation with getAnalysisUsage implemented.
  struct FuncArgParser : public FunctionPass {
    
    static char ID; // Pass identification, replacement for typeid
    FuncArgParser() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      char funcName[100] = {0}; // TODO: hardcoded size for now, fix
      strcpy(funcName, F.getName().str().c_str());
      
      for (const Argument &arg : F.args()) {
        int argNo = arg.getArgNo();
        dumpFuncArgType(funcName, argNo, arg.getType());
      }

      dumpFuncArgType(funcName, -1, F.getReturnType());

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

char FuncArgParser::ID = 0;
static RegisterPass<FuncArgParser>
Y("funcArgParser", "FuncArgParser Pass (with getAnalysisUsage implemented)");