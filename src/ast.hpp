#pragma once

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include <memory>
#include <vector>
#include <string>

class ExprAST {
    public:
        virtual ~ExprAST() = default;
        virtual llvm::Value *codegen() { };
};

class NumberExprAST : public ExprAST {
    double val;

    public: 
        using ExprAST::codegen;

        NumberExprAST(double val);

        llvm::Value *codegen(std::unique_ptr<llvm::LLVMContext> &context);
};


class VariableExprAST : public ExprAST {
    std::string name;

    public:
        using ExprAST::codegen;
        VariableExprAST(std::string &name);
};


class BinaryExprAST : public ExprAST {
    char op;
    std::unique_ptr<ExprAST> lhs, rhs;

    public:
        using ExprAST::codegen;
        BinaryExprAST(char op, std::unique_ptr<ExprAST> lhs, std::unique_ptr<ExprAST> rhs);
};

class CallExprAST : public ExprAST {
    std::string callee;
    std::vector<std::unique_ptr<ExprAST>> args;

    public:
        CallExprAST(const std::string &callee, std::vector<std::unique_ptr<ExprAST>> args);
};

class PrototypeAST {
    std::string name;
    std::vector<std::string> args;

    public:
        PrototypeAST(const std::string &name, std::vector<std::string> args);
};

class FunctionAST {
    std::unique_ptr<PrototypeAST> proto;
    std::unique_ptr<ExprAST> body;

    public:
        FunctionAST(std::unique_ptr<PrototypeAST> proto, std::unique_ptr<ExprAST> body);
};