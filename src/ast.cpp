#include "ast.hpp"

// NumberExprAST methods
NumberExprAST::NumberExprAST(double val) : val(val) {}

llvm::Value *NumberExprAST::codegen(std::unique_ptr<llvm::LLVMContext> &context) {
	return llvm::ConstantFP::get(*context, llvm::APFloat(val));
}

// VariableExprAST methods
VariableExprAST::VariableExprAST(std::string &name) : name(name) {}

// BinaryExprAST methods
BinaryExprAST::BinaryExprAST(char op, std::unique_ptr<ExprAST> lhs, std::unique_ptr<ExprAST> rhs) 
			: op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

// CallExprAST methods
CallExprAST::CallExprAST(const std::string &callee, std::vector<std::unique_ptr<ExprAST>> args) 
			: callee(callee), args(std::move(args)) {}

// PrototypeAST methods
PrototypeAST::PrototypeAST(const std::string &name, std::vector<std::string> args) 
			: name(name), args(std::move(args)) {}

// FunctionAST methods
FunctionAST::FunctionAST(std::unique_ptr<PrototypeAST> proto, std::unique_ptr<ExprAST> body)
			: proto(std::move(proto)), body(std::move(body)) {}


