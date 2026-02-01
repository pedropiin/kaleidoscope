#pragma once

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Function.h"
#include <map>
#include <string>

// Deal with circular dependency between 'ast.hpp' and 'codegen_visitor.hpp'
class ExprAST;
class NumberExprAST;
class VariableExprAST;
class BinaryExprAST;
class CallExprAST;
class FunctionAST;
class PrototypeAST;

class CodegenVisitor {
    public:
        std::unique_ptr<llvm::LLVMContext> context;
        std::unique_ptr<llvm::IRBuilder<>> builder;
        std::unique_ptr<llvm::Module> module;
        std::map<std::string, llvm::Value *> named_values;

        llvm::Value *visit_number_expr(NumberExprAST &);
        llvm::Value *visit_variable_expr(VariableExprAST &);
        llvm::Value *visit_binary_expr(BinaryExprAST &);
        llvm::Value *visit_call_expr(CallExprAST &);
        llvm::Function *visit_function(FunctionAST &);
        llvm::Function *visit_prototype(PrototypeAST &);
};