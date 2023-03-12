//===- FuncArgParser.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file implements two versions of the LLVM "FuncArgParser World" pass described
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

#define DEBUG_TYPE "funcArgParser"

STATISTIC(FuncArgParserCounter, "Counts number of functions greeted");

int get_type_str(Type *type, char *buf) {
  if (!type) return -1;
  
  std::string str;
  raw_string_ostream os(str);
  type->print(os);
  
  strncpy(buf, str.c_str(), 100); // limit to 100 characters
  return strlen(buf);
}

namespace {

  // FuncArgParser - Implementation with getAnalysisUsage implemented.
  struct FuncArgParser : public FunctionPass {
    
    void pr(int i, std::string argName, const char *title, long content) {
      std::stringstream ss;
      ss << "\t" << "Arg num: " << i << ", " << "Arg name: " << argName << ", " << title << ": " << content << "\n";
      outs() << ss.str();
      // outs().write();
    }

    void pr_type(int i, std::string argName, llvm::Type *type) {
      std::stringstream ss;
      ss << "\t" << "Arg num: " << i << ", " << "Arg name: " << argName << "Type: " << type << '\n';
      if (type) {
        // outs() << "\t" << argName << ": ";
        char buf[100];
        get_type_str(type, buf);
        // if (n > 0) outs() << "\tType is " << n << " chars long: " << buf << "\n";
        PointerType *pointerTypeCast = dyn_cast<PointerType>(type);
        ArrayType *arrayTypeCast = dyn_cast<ArrayType>(type);
        VectorType *vectorTypeCast = dyn_cast<VectorType>(type);
        StructType *structTypeCast = dyn_cast<StructType>(type);
        // outs() << ((pointerTypeCast) ? "\tpointerTypeCast is valid!\n" : "\tpointerTypeCast is not valid\n");
        // outs() << ((arrayTypeCast) ? "\tarrayTypeCast is valid!\n" : "\tarrayTypeCast is not valid\n");
        // outs() << ((vectorTypeCast) ? "\tvectorTypeCast is valid!\n" : "\tvectorTypeCast is not valid\n");
        // outs() << ((structTypeCast) ? "\tstructTypeCast is valid!\n" : "\tstructTypeCast is not valid\n");
        
        Type *elType;
        int numElementsInStruct;
        if (arrayTypeCast) elType = arrayTypeCast->getElementType();
        else if (vectorTypeCast) elType = vectorTypeCast->getElementType();
        else if (structTypeCast && (numElementsInStruct = structTypeCast->getNumElements())) {
          // outs() << "Num elements in struct: " << numElementsInStruct << "\n";
          elType = structTypeCast->getElementType(0);
        }
        // else outs() << "\tCould not cast type using getElementType!!\n";
       
        // outs() << "\tThe type is " << type << ", " << type->getTypeID();
        // outs() << elType->getTypeID() << "\n";
        if (elType) {
          // outs() << "\tElement type: " << elType;
          // if (elType->getTypeID() != NULL) outs() << "elementType is " << elType->getTypeID() << '\n';
        }
       
      }
      else {
        // outs() << "\t" << (!argName.empty() ? argName : "Type") << " is not available\n";
      }
      // outs() << ss.str();
    }

    static char ID; // Pass identification, replacement for typeid
    FuncArgParser() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      ++FuncArgParserCounter;
      // outs() << "FuncArgParser: ";
      // outs().write_escaped(F.getName()) << '\n';
      char funcName[70];
      strcpy(funcName, F.getName().str().c_str());
      // char *funcName = const_cast<char*>(F.getName().str().c_str());
      // const char *funcName = F.getName().str().c_str();
      // printf("%s\n", F.getName().str());

      // pr(-1, "_", "Instruction count", F.getInstructionCount());
      // pr_type(-1, "Return Type", F.getReturnType());
      // pr(-1, "_", "Num Params", F.getFunctionType()->getNumParams());

      for (const Argument &arg : F.args()) {
        int argNo = arg.getArgNo();
        char type[80] = {0};
        outs() << "arg.getType: " << arg.getType() << "\n";
        get_type_str(arg.getType(), type);
        if (funcName) printf("funcName: %s\n", funcName);
        if (argNo) printf("argNo: %02d\n", argNo);
        if (type) printf("type: %s\n", type);
        // printf("%s$%02d:%s\n", funcName, argNo, type);
        // std::string argName = arg.getName().str();
        // pr(argNo, argName, "Has nonNullAttr", arg.hasNonNullAttr());
        // pr(argNo, argName, "Has by val attr", arg.hasByValAttr());
        // pr(argNo, argName, "Has by ref attr", arg.hasByRefAttr());
        // pr(argNo, argName, "hasPassPointeeByValueCopyAttr", arg.hasPassPointeeByValueCopyAttr());
        // pr(argNo, argName, "getPassPointeeByValueCopySize", arg.getPassPointeeByValueCopySize());
        // pr(argNo, argName, "hasPointeeInMemoryValueAttr", arg.hasPointeeInMemoryValueAttr());
        // pr(argNo, argName, "getDereferenceableBytes", arg.getDereferenceableBytes());
        // pr(argNo, argName, "hasPointeeInMemoryValueAttr", arg.hasPointeeInMemoryValueAttr());
        // pr(argNo, argName, "hasPointeeInMemoryValueAttr", arg.hasPointeeInMemoryValueAttr());

        // pr(argNo, argName, "getParamAlignment", arg.getParamAlignment());
        // pr_type(argNo, argName, arg.getType());
        // pr_type(argNo,  argName, arg.getParamByValType());
        // pr_type(argNo, argName, arg.getParamStructRetType());
        // pr_type(argNo, argName, arg.getParamByRefType());
        // pr(argNo, argName, "Has by val attr", arg.hasByValAttr());
        // pr(argNo, argName, "Has by val attr", arg.hasByValAttr());

        // outs().write_escaped("Test") << '\n';
      }

      return false;
    }

    // We don't modify the program, so we preserve all analyses.
    void getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.setPreservesAll();
      AU.addRequired<DominatorTreeWrapperPass>();
      AU.addRequired<LoopInfoWrapperPass>();
      // AU.addRequired<VerifyPass>();
    }
  };
}

char FuncArgParser::ID = 0;
static RegisterPass<FuncArgParser>
Y("funcArgParser", "FuncArgParser Pass (with getAnalysisUsage implemented)");
//
